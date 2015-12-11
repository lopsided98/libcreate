/**
Software License Agreement (BSD)

\file      util.h
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

#ifndef CREATE_UTIL_H
#define CREATE_UTIL_H

#define COUT(prefix,msg) (std::cout<<prefix<<msg<<std::endl)
#define CERR(prefix,msg) (std::cerr<<prefix<<msg<<std::endl)

namespace create {
  namespace util {

    static const uint8_t CREATE_2_HEADER = 19;
    static const float CREATE_2_AXLE_LENGTH = 0.235;
    static const float CREATE_2_TICKS_PER_REV = 508.8;
    static const uint32_t CREATE_2_MAX_ENCODER_TICKS = 65535;
    static const float CREATE_2_WHEEL_DIAMETER = 0.078;
    static const float CREATE_2_MAX_VEL = 0.5;
    static const float PI = 3.14159;
    static const float TWO_PI = 6.28318;
    static const float EPS = 0.001;
  
    inline float normalizeAngle(const float& angle) {
      float a = angle;
      while (a < -PI) a += TWO_PI;
      while (a > PI) a -= TWO_PI;
      return a;
    };

  }  // namespace util
} // namespace create

#endif // CREATE_UTIL_H
