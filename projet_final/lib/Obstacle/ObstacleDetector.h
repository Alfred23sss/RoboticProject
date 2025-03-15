/**
 * ObstacleDetector.h
 * Définition de la classe ObstacleDetector pour la détection des obstacles
 *
 * Cette classe permet de détecter les obstacles en mesurant la distance entre
 * le robot et un obstacle à l'aide d'un capteur.
 *
 * Elle utilise le module CAN pour la communication avec le capteur.
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang
 * Date: 16 avril 2024
 */

#define F_CPU 8000000UL
#include "Can/can.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#ifndef OBSTACLE_DECTECTOR_H
#define OBSTACLE_DECTECTOR_H

class ObstacleDetector {
public:
  ObstacleDetector();
  uint16_t getDistance();
  bool isSpotDetected();

private:
  can can_;
  const uint8_t PRECISION_BIT_SHIFT = 2;
  const uint8_t DETECTOR_OUTPUT = PA1;
  const uint8_t N_READ = 5;
  const uint16_t DELAY_BETWEEN_READ = 5;
  const uint16_t MIN_DISTANCE_TO_DETECT = 60;
  const uint16_t MAX_DISTANCE_TO_DETECT = 260;
  const uint16_t DISTANCE_TO_STOP_CM = 60;
};

#endif