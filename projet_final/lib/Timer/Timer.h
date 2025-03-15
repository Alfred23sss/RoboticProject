// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise
// mbay

// Description du programme: Timer.h définit une classe Timer pour configurer et
// contrôler un timer sur ld microcontrôleur. Le constructeur initialise le
// timer avec une valeur de départ, et la classe comprend des méthodes pour
// configurer le timer en mode CTC (Clear Timer on Compare Match) ou Two Match,
// activer ou désactiver les interruptions du timer, et réinitialiser le timer.
// On a decide d'utiliser le timer1 parceque c'est le timer le plus grand et
// donc celui qui peut compter le plus logtemps

// Identification matérielle: On utilise les registres du ATmega32.

#pragma once

#define TIMER_H

#include <avr/io.h>

class Timer {
public:
  Timer(uint16_t timerStart);
  ~Timer();
  void timerCTC(uint8_t prescalerConfig, uint16_t ocrValue);
  void timerTwoMatch(uint8_t prescalerConfig, uint16_t ocrValueA,
                     uint16_t ocrValueB);
  void startRobotTimer();
  void stopTimer();
  void stopCTC();
  int getAndResetTimer();
  void toggleInterrupts(bool enableInterrupts);
  void timerReset();
  void stopTimerCTCRobotTwo();
  void startTimerCTCRobotTwo();
  void startIRTimer();
  void stopIRTimer();
  void setUpTimerReception();

private:
  uint16_t timerStartValue;
};
