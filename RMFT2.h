/*
 *  © 2020, Chris Harlow. All rights reserved.
 *  
 *  This file is part of CommandStation-EX
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CommandStation.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef RMFT2_H
#define RMFT2_H
#include "RMFTMacros.h"
 
  // Flag bits for status of hardware and TPL
  static const short SECTION_FLAG = 0x01;
  static const short SENSOR_FLAG = 0x02;
 
#if (defined(ARDUINO_AVR_MEGA) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_SAMD_ZERO))
   static const short MAX_FLAGS=256;
   #define FLAGOVERFLOW(x) false
#else
  static const short MAX_FLAGS=64;
  #define FLAGOVERFLOW(x) x>=MAX_FLAGS
#endif

 class RMFT2 {
   public:
    static void begin();
    static void loop();
    RMFT2(byte route);
    ~RMFT2();
    static void readLocoCallback(int cv);
  private: 
    static void ComandFilter(Print * stream, byte & opcode, byte & paramCount, int p[]);
    static bool parseSlash(Print * stream, byte & paramCount, int p[]) ;
    static void streamFlags(Print* stream);
    static void setFlag(byte id,byte onMask, byte OffMask=0);
    static byte getFlag(byte id,byte mask);    

    static int locateRouteStart(short _route);
    static int progtrackLocoId;
    static RMFT2 * loopTask;
    static RMFT2 * pausingTask;
    void delayMe(int millisecs);
    void driveLoco(byte speedo);
    bool readSensor(short id);
    void skipIfBlock();
    bool readLoco();
    void showManual();
    void showProg(bool progOn);
    bool doManual();
    void loop2();          
    
   static bool diag;
   static const  PROGMEM  byte RouteCode[];
   static byte flags[MAX_FLAGS];
 
 // Local variables
    int progCounter;    // Byte offset of next route opcode in ROUTES table
    unsigned long delayStart; // Used by opcodes that must be recalled before completing
    unsigned long waitAfter; // Used by OPCODE_AFTER
    unsigned int  delayTime;
    int loco;
    bool forward;
    bool invert;
    int speedo;
    RMFT2 *next;   // loop chain 
};
#endif
