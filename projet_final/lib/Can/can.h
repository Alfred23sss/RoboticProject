/*
 * Classe permettant l'acces au convertisseur analogique/numerique
 * du microcontroleur ATMega16 de Atmel.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Code qui n'est sous aucune license.
 *
 */

// Description du programme: can.h décrit la classe CAN pour utiliser le
// Convertisseur Analogique-Numérique (CAN) Cette classe inclut un constructeur
// et un destructeur par défaut, ainsi que la méthode lecture(uint8_t pos) pour
// lire une valeur analogique à partir d'une position spécifiée.

// Identification matérielle: registres du microcontroleur ATmega32.

#ifndef CAN_H
#define CAN_H

#include <avr/io.h>

class can {
public:
  can();
  ~can();

  uint16_t lecture(uint8_t pos);

private:
};

#endif