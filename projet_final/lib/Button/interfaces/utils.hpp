#pragma once

#ifndef UTILS_H
#define UTILS_H
#include <avr/io.h>

typedef volatile uint8_t *Register;

inline void setRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister |= _BV(bit);
}

inline void clearRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister &= ~_BV(bit);
}

#endif