/*
 * CPPFile1.cpp
 *
 * Created: 01/08/2020 11:39:20
 *  Author: Simon
 */ 
#include "RotaryEnc.h"

//-----------------------------------------------------------------
RotaryEncoderImpl::RotaryEncoderImpl(int8_t ph1, int8_t ph2, int8_t sw, bool upState, int debounceMs)
: 
    ph1_(ph1, debounceMs), 
    ph2_(ph2, debounceMs), 
    sw_(sw, debounceMs), 
    upState_(upState)
{
    pinMode(ph1, INPUT_PULLUP);
    pinMode(ph2, INPUT_PULLUP);
    pinMode(sw, INPUT_PULLUP);
    last_ph1_ = digitalRead(ph1);
    last_sw_ = digitalRead(sw);
}
//-----------------------------------------------------------------
uint8_t RotaryEncoderImpl::pollEncoder()
{
    int8_t ret = 0;
    auto v = ph1_.read();
    auto v2 = ph2_.read();
    
    if(!v && last_ph1_)
    {
        ret = (v2==upState_) ? LEFT : RIGHT;
    }        
    last_ph1_ = v;
    return ret;
}
//-----------------------------------------------------------------
uint8_t RotaryEncoderImpl::pollSwitch()
{
    auto v = sw_.read();
    
    if(v==last_sw_)
        return 0;

    last_sw_ = v;
    return (v==upState_) ? UP : DOWN;
}
//-----------------------------------------------------------------

