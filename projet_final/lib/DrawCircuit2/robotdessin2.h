/**
 * robotdessin.h
 * Définition de la classe RobotAffichage pour le dessin de circuits
 *
 * Cette classe permet de gérer l'affichage des circuits dessinés par le
 * robot 1. Elle utilise des modules pour contrôler les LED et les segments du
 * circuit.
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang Date: 16 avril 2024
 */

#define F_CPU 8000000UL
#include "Led/Led.h"
#include "Uart/uart.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#ifndef ROBOT_DESSIN_H
#define ROBOT_DESSIN_H

#include "Segment/segment.h"

class RobotAffichage2 {
public:
  void printCircuit(Segment segmentChart[], uint8_t sizeChart);
};

#endif