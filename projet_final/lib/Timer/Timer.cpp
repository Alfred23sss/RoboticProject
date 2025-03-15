#include "Timer.h"

Timer::Timer(uint16_t timerStart) {
  timerStartValue = timerStart;
  TCNT1 = timerStartValue;
}

void Timer::startRobotTimer() {
  TCNT1 = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10);
}

void Timer::startIRTimer() {
  TCNT1 = 0;
  TCCR1B |= (1 << CS10);
}

void Timer::stopIRTimer() { TCCR1B &= ~(1 << CS10); }

void Timer::stopTimer() {
  TCCR1B &= ~(1 << CS12);
  TCCR1B &= ~(1 << CS10);
}

int Timer::getAndResetTimer() {
  int timerEnd = TCNT1;
  TCNT1 = 0;
  return timerEnd;
}

void Timer::timerCTC(uint8_t prescalerConfig, uint16_t ocrValue) {
  OCR1A = ocrValue;

  TCCR1A |= (1 << COM1A0);
  TCCR1B |= prescalerConfig | (1 << WGM12);
}

void Timer::stopTimerCTCRobotTwo() {
  TCCR1B &= ~((1 << CS12) | (1 << CS10));
  TCNT1 = 0;
}

void Timer::startTimerCTCRobotTwo() {
  TCNT1 = 0;
  OCR1A = 1953;
  TCCR1A = 0;
  TCCR1B |= (1 << CS12) | (1 << CS10) | (1 << WGM12);
  TCCR1C = 0;
  TIMSK1 |= (1 << OCIE1A);
}

void ::Timer::stopCTC() { TCCR1B &= ~(1 << CS10); }

Timer::~Timer() = default;

void Timer::timerTwoMatch(uint8_t prescalerConfig, uint16_t ocrValueA,
                          uint16_t ocrValueB) {
  OCR1A = ocrValueA;
  OCR1B = ocrValueB;

  TCCR1A = 0;
  TCCR1B = prescalerConfig;
}

void Timer::toggleInterrupts(bool enableInterrupts) {
  if (enableInterrupts) {
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
  } else {
    TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));
  }
}

void Timer::setUpTimerReception() {
  OCR1A = 100;
  TCCR1A |= (1 << COM1A0);
  TCCR1B |= (1 << CS10) | (1 << WGM12);
}

void Timer::timerReset() {
  TCNT1 = 0;
  TCCR1B &= ~((1 << CS12) | (1 << CS10));
  TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));
}