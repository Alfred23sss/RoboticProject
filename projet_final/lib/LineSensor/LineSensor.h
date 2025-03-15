/**
 * LineSensor.h
 * Définition de la classe LineSensor pour le contrôle des capteurs de ligne
 *
 * Cette classe permet de contrôler les capteurs de ligne d'un robot.
 * Elle fournit des méthodes pour détecter l'état des capteurs et recentrer
 * le robot en fonction de ces informations.
 *
 * Materiel: Utilisation du pont H pour le controle des roues sur les ports B5
 * B6 B3 et B4. Le capteur de ligne est connecte sur la PinA1 a A5.
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang
 * Date: 16 avril 2024
 */

#define F_CPU 8000000UL
#include "Wheel2/Wheel2.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

class LineSensor {
public:
  LineSensor();
  void recenter();
  void recenterBack();
  void recenterBackLeft();
  void recenterBackRight();
  void recenterSegment();
  uint8_t getNumbersSensors();
  bool isS1On();
  bool isS2On();
  bool isS3On();
  bool isS4On();
  bool isS5On();
  bool areAllOn();
  bool areAllOff();

private:
  Wheel2 wheel;
  const uint8_t MASK_S1 = (1 << PORTA1);
  const uint8_t MASK_S3 = (1 << PORTA3);
  const uint8_t MASK_S5 = (1 << PORTA5);
  const uint8_t MASK_S2 = (1 << PORTA2);
  const uint8_t MASK_S4 = (1 << PORTA4);
  const uint8_t MASK_S = (MASK_S1 | MASK_S2 | MASK_S3 | MASK_S4 | MASK_S5);
  const uint16_t ONE_SEC_DELAY = 1000;
};