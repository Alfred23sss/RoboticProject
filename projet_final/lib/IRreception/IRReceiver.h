/**
 * IRReceiver.h
 * Définition de la classe IRReceiver pour la réception infrarouge
 *
 * Cette classe permet de recevoir des signaux infrarouges à l'aide d'un capteur
 * infrarouge connecté a la PIND3.
 *
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang
 * Date: 16 avril 2024
 */

#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include <avr/io.h>

class IRReceiver {
public:
  IRReceiver(uint8_t receiverPin);

  void initialize();

private:
  uint8_t receiverPin_;
};

#endif