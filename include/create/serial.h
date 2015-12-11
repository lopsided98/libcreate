/**
Software License Agreement (BSD)

\file      serial.h
\authors   Jacob Perron <jperron@sfu.ca>
\copyright Copyright (c) 2015, Autonomy Lab (Simon Fraser University), All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of Autonomy Lab nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

// Based on example from:
//   https://github.com/labust/labust-ros-pkg/wiki/Create-a-Serial-Port-application

#ifndef CREATE_SERIAL_H
#define CREATE_SERIAL_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "create/data.h"
#include "create/types.h"
#include "create/util.h"

namespace create {
  class Serial {
    private:
      enum ReadState {
        READ_HEADER,
        READ_NBYTES,
        READ_PACKET_ID,
        READ_PACKET_BYTES,
        READ_CHECKSUM
      };

      boost::shared_ptr<Data> data;
      boost::asio::io_service io;
      boost::asio::serial_port port;
      boost::thread ioThread;
      boost::condition_variable dataReadyCond;
      boost::mutex dataReadyMut;
      ReadState readState;
      bool dataReady;
      bool isReading;
      bool firstRead;

      // These are just for diagnostics, maybe not necessary
      // TODO: Investigate
      uint64_t corruptPackets;
      uint64_t totalPackets;
      // State machine variables
      uint8_t headerByte;
      uint8_t packetID;
      uint8_t expectedNumBytes;
      uint8_t byteRead;
      uint16_t packetBytes;
      uint8_t numBytesRead;
      uint32_t byteSum;
      uint8_t numDataBytesRead;
      uint8_t expectedNumDataBytes;

      // Callback executed when data arrives from Create
      // TODO: Should size be const?
      // Not sure, this was from example
      void onData(const boost::system::error_code& e, const std::size_t& size);
      // Callback to execute once data arrives
      boost::function<void()> callback;
      // Start and stop reading data from Create
      bool startReading();
      void stopReading();

    public:
      Serial(boost::shared_ptr<Data> data, const uint8_t& header = create::util::CREATE_2_HEADER);
      ~Serial();
      bool connect(const std::string& port, const int& baud = 115200, boost::function<void()> cb = 0);
      void disconnect();
      inline bool connected() const { return port.is_open(); };
      bool send(const uint8_t* bytes, const uint32_t numBytes);
      bool sendOpcode(const Opcode& code);
  };
}  // namespace create

#endif // CREATE_SERIAL_H
