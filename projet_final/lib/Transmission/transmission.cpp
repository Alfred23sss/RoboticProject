#include "transmission.h"
Transmission::Transmission() {
  DDRD |= (1 << PORTD5) | (1 << PD4);
  timer = Timer(0);
}
void Transmission::setOn() { timer.timerCTC((1 << CS10), PRESCALER_VALUE); }
void Transmission::setOff() {
  timer.stopCTC();
  PORTD = (1 << PD5);
}

void Transmission::stop() {
  setOn();
  _delay_ms(2000);
  setOff();
}
void Transmission::logicalZero() {
  setOn();
  _delay_us(DELAY_LOGICAL_ZERO);
  setOff();
  _delay_us(DELAY_INTERVAL);
}
void Transmission::logicalOne() {
  setOn();
  _delay_us(DELAY_LOGICAL_ONE);
  setOff();
  _delay_us(DELAY_INTERVAL);
}
void Transmission::start() {
  setOn();
  _delay_us(DELAY_START);
  setOff();
  _delay_us(DELAY_INTERVAL);
}