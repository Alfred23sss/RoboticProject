/**
 * Transmission.h
 * Définition de la classe Transmission pour la transmission de données
 *
 * Cette classe permet de contrôler la transmission de données en utilisant
 * une led infrarouge connecte sur le Port D5.
 *
 *  Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise
 *  Mbay Mansang Date: 16 avril 2024
 */

#pragma once
#define F_CPU 8000000UL
#include "Timer/Timer.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
class Transmission {
public:
  Transmission();
  void setOn();
  void setOff();
  void logicalZero();
  void logicalOne();
  void start();
  void stop();

private:
  static constexpr uint8_t PRESCALER_VALUE = 104;
  static constexpr double DELAY_LOGICAL_ONE = 1200;
  static constexpr double DELAY_INTERVAL = 600;
  static constexpr double DELAY_LOGICAL_ZERO = 600;
  static constexpr double DELAY_START = 2400;
  static constexpr long MAX_UINT8 = 255;

private:
  Timer timer = Timer(0);
};