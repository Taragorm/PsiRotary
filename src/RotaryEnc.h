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



/*!
    basic encoder implementation
 */
class RotaryEncoderImpl
{
    psiiot::Debounce ph1_;
    psiiot::Debounce ph2_;
    psiiot::Debounce sw_;
    bool last_ph1_;
    bool last_sw_;
    const bool upState_;

public:
    static const char LEFT = 'L';
    static const char RIGHT = 'R';
    static const char DOWN = 'D';
    static const char UP = 'U';

    static const bool IMPLEMENTED = true;

    RotaryEncoderImpl(int8_t ph1, int8_t ph2, int8_t sw, bool upState, int debounceMs=5);
    //-----------------------------------------------------------------
    uint8_t pollEncoder();
    //-----------------------------------------------------------------
    uint8_t pollSwitch();

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
    bool UPSTATE
>
class RotaryEncoder : public RotaryEncoderImpl
{
public:

    RotaryEncoder(int debounceMs=5 )
    : RotaryEncoderImpl(PH1,PH2,SW,UPSTATE, debounceMs)
    {
    }
    //-----------------------------------------------------------------
};

//========================================


#endif /* ROTARYENC_H_ */