/**
 * Sound.h
 * Définition de la classe Sound pour la génération de sons
 *
 * Cette classe permet de générer des sons sur un périphérique de sortie audio.
 * Elle utilise le timer2 en mode CTC pour générer des signaux PWM à différentes
 * fréquences.
 *
 * Materiel: Le pwm est genere sur le PORT D7 et D6. Nous utilisons aussi le
 * piezo electrique pour emettre differents sons
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang
 * Date: 16 avril 2024
 */

#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

class Sound {
public:
  Sound();
  ~Sound();
  void playSound(uint16_t note);
  void stopSound();

private:
  void initialisationTimer2Ctc();
  double PWM_FREQUENCY = 0;
  const uint16_t DEFAULT_FREQUENCY = 440;
  const double SIXTY_NINE = 69.0;
  const uint8_t TWELVE = 12;
  const uint8_t TWO = 2;
  const uint16_t PRESCALER = 256;
};