/*
 * RotaryEnc.h
 *
 * Created: 30/07/2020 17:16:19
 *  Author: Simon
 */


#ifndef ROTARYENC_H_
#define ROTARYENC_H_
#include <Arduino.h>
#include <stdint.h>
#include <debounce.h>
//========================================
/*!
    Duck-typed null implementation of a
    rotary encoder
 */
class NoRotaryEncoder
{
public:
        static const bool IMPLEMENTED = false;

        uint8_t pollEncoder() { return 0; }
        uint8_t pollSwitch() { return 0; }
};


//====================================================================
class RotaryEncoderActions
{
protected:    
    RotaryEncoderActions() {}

public:    
    static const char LEFT = 'L';
    static const char RIGHT = 'R';
    static const char DOWN = 'D';
    static const char UP = 'U';
};
//====================================================================
/*!
    basic encoder implementation
 */
template<typename TMR = MilliTimer>
class RotaryEncoderImpl : RotaryEncoderActions
{
    psiiot::Debounce<TMR> ph1_;
    psiiot::Debounce<TMR> ph2_;
    psiiot::Debounce<TMR> sw_;

    bool last_ph1_;
    bool last_sw_;
    const bool upState_;

public:

    static const bool IMPLEMENTED = true;

    RotaryEncoderImpl(int8_t ph1, int8_t ph2, int8_t sw, bool upState, int debounceMs)
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
    uint8_t pollEncoder()
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
    uint8_t pollSwitch()
    {
        auto v = sw_.read();
        
        if(v==last_sw_)
            return 0;

        last_sw_ = v;
        return (v==upState_) ? UP : DOWN;
    }

};

//========================================
/*!
    templated basic encoder implementation
    with default c'tor
 */
template <
    pin_size_t PH1,
    pin_size_t PH2,
    pin_size_t SW,
    bool UPSTATE,
    typename TMR = MilliTimer
>
class RotaryEncoder : public RotaryEncoderImpl<TMR>
{
public:

    RotaryEncoder(int debounceMs=5 )
    : RotaryEncoderImpl<TMR>(PH1,PH2,SW,UPSTATE, debounceMs)
    {
    }
    //-----------------------------------------------------------------
};

//========================================


#endif /* ROTARYENC_H_ */