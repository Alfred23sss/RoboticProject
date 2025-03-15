// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise
// mbay

// Description du programme: Wheel.h définit la classe Wheel pour contrôler un
// moteur à travers un signal PWM

// Elle comprend un constructeur, un destructeur par défaut, et des méthodes
// pour ajuster le signal PWM,

// faire avancer, tourner à gauche ou à droite, et reculer le moteur.

// Identification matérielle: On utilise le pont H du robot brache aux pin PB3
// PB4 PB6 et PB5 du microcontroleur qui sont en mode sortie.

#define F_CPU 8000000UL

#include <avr/interrupt.h>

#include <avr/io.h>

#include <stdint.h>

#include <util/delay.h>

#ifndef WHEEL_H

#define WHEEL_H

class Wheel2

{

public:
  Wheel2();

  ~Wheel2();

  void adjustPWM(uint8_t rapport_a, uint8_t rapport_b);

  void setWheelForward();

  void turnLeft();

  void turnRight();

  void setWheelBackward();

  void stopWheel(); // met le pwm a 0 ce qui arrete les moteurs

  void turnLeftNinetyDegrees();

  void turnRightNinetyDegrees();

  void turnSlightlyLeft();

  void turnSlightlyRight();

  void turnSlightlyMoreLeft();

  void turnSlightlyMoreRight();

  void turnOneEightyDegrees();

  void turnRightFourtyFiveDegrees();

  void turnSlightlyLeftBackward();

  void turnSlightlyRightBackward();

private:
  static const uint8_t VALEUR_8_BITS = 255;

  static const uint8_t POURCENTAGE_100 = 100;
};

#endif
