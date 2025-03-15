/*
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

// Description du programme: CAN.cpp met en œuvre les méthodes de la classe can
// pour utiliser le Convertisseur
// Analogique-Numérique. Le constructeur initialise les registres ADMUX et
// ADCSRA pour configurer le CAN. Le destructeur désactive le CAN. La méthode
// lecture(uint8_t pos) lit une valeur analogique à partir de la position
//spécifiée en configurant le multiplexeur analogique.

// Identification matérielle: registres du microcontroleur ATmega32.

#include "can.h"

can::can() {

  ADMUX = (0 << REFS1) | (0 << REFS0) | (0 << ADLAR) | (0 << MUX4) |
          (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);

  ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) |
           (0 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
}

can::~can() { ADCSRA = 0 << ADEN; }

uint16_t can::lecture(uint8_t pos) {
  uint16_t adcVal;
  ADMUX &=
      ~((1 << MUX4) | (1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));

  ADMUX |= ((pos & 0x07) << MUX0);

  ADCSRA |= (1 << ADSC);

  while (!(ADCSRA & (1 << ADIF)))
    ;

  ADCSRA |= (1 << ADIF);

  adcVal = ADCL;
  adcVal += ADCH << 8;

  return adcVal;
}
