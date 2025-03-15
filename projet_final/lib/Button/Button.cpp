// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise mbay

// Description du programme: Ce code définit les fonctions de la classe Button pour gérer un bouton avec une interruption externe 
// sur le microcontrôleur. Le constructeur Button::Button(uint8_t pinNumber) initialise la broche du bouton en tant qu'entrée. 
// La méthode bool Button::isPressed() vérifie si le bouton est enfoncé en lisant l'état de la broche. La méthode Button::enableInterrupt() 
// active l'interruption externe INT0 pour détecter les changements d'état du bouton. La méthode Button::disableInterrupt() désactive cette 
// interruption.

// Identification matérielle: Bouton --> pinNumber avec pinNumber configure en mode entree.

#include "Button.h"
#include <avr/interrupt.h>

Button::Button(uint8_t pinNumber) : pinNumber_(pinNumber) {
    initialize();
}

Button::~Button() {
}

bool Button::isPressed() {
    return PIND & (1 << pinNumber_);
}

void Button::enableInterrupt() {
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);
    sei(); 
}

void Button::disableInterrupt() {
    EIMSK &= ~(1 << INT0);
    cli();
}

void Button::initialize() {
    DDRD &= ~(1 << pinNumber_);
    sei();
}