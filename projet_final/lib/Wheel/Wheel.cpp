#include "Wheel.h"

Wheel::Wheel() {
  cli();
  DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB5) | (1 << PB6);
  TCCR0A |= (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
  TCCR0B |= (1 << CS01);
  sei();
}

Wheel::~Wheel() = default;

void Wheel::adjustPWM(uint8_t rapport_a, uint8_t rapport_b) {
  OCR0A = (rapport_a * UINT8_MAX) / POURCENTAGE_100;
  OCR0B = (rapport_b * UINT8_MAX) / POURCENTAGE_100;
}

void Wheel::setWheelForward(uint8_t droite, uint8_t gauche) {
  PORTB &= ~((1 << PB5) | (1 << PB6));
  adjustPWM(droite, gauche);
}

void Wheel::turnRight(uint8_t droite, uint8_t gauche) {
  PORTB |= (1 << PB5);
  PORTB &= ~(1 << PB6);
  adjustPWM(droite, gauche);
}

void Wheel::turnLeft(uint8_t droite, uint8_t gauche) {
  PORTB &= ~(1 << PB5);
  PORTB |= (1 << PB6);
  adjustPWM(droite, gauche);
}

void Wheel::setWheelBackward(uint8_t droite, uint8_t gauche) {
  PORTB |= ((1 << PB5) | (1 << PB6));
  adjustPWM(droite, gauche);
}

void Wheel::stopWheel() { adjustPWM(0, 0); }

void Wheel::turnLeftNinetyDegrees(uint8_t droite, uint8_t gauche) {
  turnLeft(droite, gauche);
  _delay_ms(800);
  stopWheel();
}

void Wheel::turnRightNinetyDegrees(uint8_t droite, uint8_t gauche) {
  turnRight(droite, gauche);
  _delay_ms(800);
  stopWheel();
}

void Wheel::turn180Degrees(uint8_t droite, uint8_t gauche) {
  turnRight(droite, gauche);
  _delay_ms(800);
  stopWheel();
}
