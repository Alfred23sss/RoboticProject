#include "Wheel2.h"

Wheel2::Wheel2() {

  cli();

  DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB5) | (1 << PB6);

  TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);

  TCCR0B |= (1 << CS01);

  sei();
}

Wheel2::~Wheel2() = default;

void Wheel2::adjustPWM(uint8_t rapport_a, uint8_t rapport_b) {

  OCR0A = (rapport_a * UINT8_MAX) / POURCENTAGE_100;

  OCR0B = (rapport_b * UINT8_MAX) / POURCENTAGE_100;
}

void Wheel2::setWheelForward() {

  PORTB &= ~((1 << PB5) | (1 << PB6));

  adjustPWM(64, 68);
}

void Wheel2::turnSlightlyLeft() { adjustPWM(64, 50); }

void Wheel2::turnSlightlyRight() { adjustPWM(50, 62); }

void Wheel2::turnSlightlyMoreRight() { adjustPWM(40, 68); }

void Wheel2::turnSlightlyMoreLeft() { adjustPWM(65, 40); }

void Wheel2::turnRight() {

  PORTB |= (1 << PB5);

  PORTB &= ~(1 << PB6);

  adjustPWM(60, 60);
}

void Wheel2::turnLeft() {

  PORTB &= ~(1 << PB5);

  PORTB |= (1 << PB6);

  adjustPWM(60, 60);
}

void Wheel2::setWheelBackward() {

  PORTB |= ((1 << PB5) | (1 << PB6));

  adjustPWM(64, 70);
}

void Wheel2::stopWheel() { adjustPWM(0, 0); }

void Wheel2::turnLeftNinetyDegrees() {

  turnLeft();

  _delay_ms(1250);

  stopWheel();
}

void Wheel2::turnRightFourtyFiveDegrees()

{

  turnRight();

  _delay_ms(750);

  stopWheel();
}

void Wheel2::turnRightNinetyDegrees() {

  turnRight();

  _delay_ms(1450);

  stopWheel();
}

void Wheel2::turnOneEightyDegrees() {

  turnRightNinetyDegrees();

  turnRightNinetyDegrees();
}

void Wheel2::turnSlightlyLeftBackward() {

  setWheelBackward();

  adjustPWM(64, 64);
}

void Wheel2::turnSlightlyRightBackward() {

  setWheelBackward();

  adjustPWM(59, 70);
}
