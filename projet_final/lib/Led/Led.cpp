#include "Led.h"

Led::Led(volatile uint8_t *mode, volatile uint8_t *port, uint8_t pinGreen,
         uint8_t pinRed)
    : _mode(mode), pinGreenPosition(pinGreen), pinRedPosition(pinRed) {
  *port |= (1 << pinGreen) | (1 << pinRed);
}

void Led::setLedGreen() {

  *_mode |= (1 << pinGreenPosition);
  *_mode &= ~(1 << pinRedPosition);
}

void Led::setLedRed() {

  *_mode |= (1 << pinRedPosition);
  *_mode &= ~(1 << pinGreenPosition);
}

void Led::setLedAmber() {
  setLedGreen();
  _delay_ms(DELAY_AMBER_GREEN);
  setLedRed();
  _delay_ms(DELAY_AMBER_RED);
}

void Led::setLedOff() {
  *_mode &= ~((1 << pinRedPosition) | (1 << pinGreenPosition));
}