/*
 Copyright (c) 2012, Tuomo Eljas Kaikkonen
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met: 

 1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer. 
 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution. 

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies, 
 either expressed or implied, of the FreeBSD Project.
*/
#ifndef ARDUINO_JTAG
#define ARDUINO_JTAG
#include "Arduino.h"
#include "io.h"

    const  IOPin TMS = {bC, P0};
    const  IOPin TDI = {bC, P4};
    const  IOPin TDO = {bC, P7};
    const  IOPin TCK = {bC, P9};
    const  IOPin MCLR = {bC, P13};
class ArduinoJTAG 
{
private:
    bool tdo_;

protected:    


    ArduinoJTAG()
    {
        pinMode( TMS,  OUTPUT );
        pinMode( TDI,  OUTPUT );
        pinMode( TDO,  INPUT  );
        pinMode( TCK,  OUTPUT );
        pinMode( MCLR, OUTPUT );
        ClearTMS();
        ClearTDI();
        ClearTCK();
        SetMCLR ();

    }

    inline bool ClockPulse(void)
    {
        ClearTCK();
//        asm( "  NOP" );
        delayMicroseconds(1);
//        tdo_ = digitalRead( PIN_TDO );
        tdo_ = getIn(TDO);//PINB & BIT_TDO;
        SetTCK();
        return tdo_;
    }

    bool GetTDO() 
    {
        return tdo_;
    }

    inline void SetTMS()
    {
//        digitalWrite( PIN_TMS, HIGH );
        setOutDirect(TMS, 1);
    }

    inline void ClearTMS()
    {
//        digitalWrite( PIN_TMS, LOW );
        setOutDirect(TMS, 0);
    }

    inline void SetTCK()
    {
//        digitalWrite( PIN_TCK, HIGH );
        //PORTB |= BIT_TCK;
        setOutDirect(TCK, 1);
    }

    inline void ClearTCK()
    {
//        digitalWrite( PIN_TCK, LOW );
        //PORTB &= ~BIT_TCK;
        setOutDirect(TCK, 0);
    }

    inline void SetMCLR()
    {
//        digitalWrite( PIN_MCLR, HIGH );
        //PORTB |= BIT_MCLR;
        setOutDirect(MCLR, 1);
    }

    inline void ClearMCLR()
    {
//        digitalWrite( PIN_MCLR, LOW );
        setOutDirect(MCLR, 0);
    }

    inline void SetTDI()
    {
//        digitalWrite( PIN_TDI, HIGH );
        setOutDirect(TDI, 1);
    }

    inline void ClearTDI()
    {
//        digitalWrite( PIN_TDI, LOW );
        setOutDirect(TDI, 0);
    }

};



#endif
