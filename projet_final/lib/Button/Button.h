// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise mbay

// Description du programme: Ce fichier d'en-tête (Button.h) définit la classe Button
//, qui offre plusieurs méthodes pour gérer un bouton sur un microcontrôleur AVR. 
//La classe comprend un constructeur Button(uint8_t pinNumber) pour configurer la broche du bouton, 
//ainsi que le destructeur ~Button(), bool isPressed() pour vérifier si le bouton est enfoncé, 
//et void enableInterrupt() et void disableInterrupt() pour activer et désactiver l'interruption externe INT0.

// Identification matérielle: Bouton --> pinNumber avec pinNumber configure en mode entree.


#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

class Button {
public:
    Button(uint8_t pinNumber);
    ~Button();
    bool isPressed();
    void enableInterrupt();
    void disableInterrupt();
    void initialize(); 
private:
    uint8_t pinNumber_;
};

#endif



