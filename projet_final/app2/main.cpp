/**
 * PROJET FINAL INF1900
 * Auteurs: Magalie Noel, Praise Mbay, Alfred Galibois-Bouchard, Salma Ben Daly
 * Hassen Fichier: main.cpp Description : Programme principal du contrôle d'un
 * robot avec gestion des segments et transmission de données. Ce programme
 * contrôle le mouvement d'un robot en fonction des données des capteurs de
 * ligne, détecte les segments traversés et transmet les données collectées via
 * un module de transmission. Il utilise des interruptions pour la gestion du
 * temps et des boutons, ainsi que une librairie pour la communication série, la
 * gestion des capteurs et le contrôle des moteurs du robot.
 */

/*  TABLEAU D'ETATS:
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| ÉTAT                    | DESCRIPTION | ENTRÉES | SORTIES |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| WAITING                 | En attente d'une action de l'utilisateur. | Bouton
C3 pressé, interruption bouton        | LED rouge allumée               |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| START                   | Démarrage du robot. | Capteur de ligne tout éteint
| Mouvement du robot vers l'avant|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| START_FORWARD           | Démarrage de la marche avant du robot. | Timer
CT/Robot2 terminé, compteur de tours    | Mouvement du robot vers l'avant|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| FORWARD                 | Avancement du robot. | Capteurs S3 et S5 activés,
capteurs S1 et S3  | Mouvement du robot vers l'avant| | | | désactivés | |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| TURN                    | Virage du robot. | Tous les capteurs activés |
Mouvement de virage du robot   |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| SMALL_SEGMENT           | Traversée d'un segment court par le robot. | Capteur
S1 activé                             | Mouvement du robot vers l'avant|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| CROSSING_SEGMENT_DETECTED | Détection du croisement d'un segment. | Capteurs
tout éteints, puis S1 activé         | Mouvement de virage du robot m|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| START_READING           | Début de la lecture du segment par le robot. |
Capteurs tout éteints                        | Mouvement du robot vers l'avant |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| END                     | Fin du parcours du robot. | Capteur S1 activé |
Mouvement du robot vers l'arrière|
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| CALCULATION             | Calcul des données du segment. | Capteurs tout
éteints                        | Données des segments calculées  |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| SOUND                   | Émission d'un son par le robot. | Bouton
d'interruption pressé                 | Son émis par le robot           |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| TRANSMISSION            | Transmission des données par le robot. | Fin de la
lecture des segments               | Transmission des données RS232  |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| SENDING_RS232           | Envoi des données via RS232 par le robot. | Bouton
C3 pressé                             | Données envoyées via RS232      |
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#define F_CPU 8000000UL
#include "Button/Button.h"
#include "DrawCircuit2/robotdessin2.h"
#include "LineSensor/LineSensor.h"
#include "Memory/memory_24C.h"
#include "Segment/segment.h"
#include "Sound/sound.h"
#include "Timer/Timer.h"
#include "Transmission/transmission.h"
#include "Uart/uart.h"
#include "Wheel2/Wheel2.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

volatile int gQuarterOfSecondPass = 0;
volatile bool gButtonPressed = false;

const int DELAY_DEBOUNCE = 30;
const int MAX_NUMBER_SEGMENT = 6;
const int TWO = 2;
const int MAX_LENGTH_CHART = 7;
const int MAX_BINARY_NUMBER = 142;
uint8_t binaryChart[MAX_BINARY_NUMBER];

ISR(TIMER1_COMPA_vect) { gQuarterOfSecondPass += 1; }

void timerTrailToTimerTransmission() {
  TCCR1B &= ~(1 << CS12);
  TCCR1B &= ~(1 << CS10);
  TIMSK1 &= ~(1 << OCIE1A);
}

void addBinaryNumber(uint8_t binaryChart[], int binaryNumber, int index) {
  for (int i = 0; i < MAX_NUMBER_SEGMENT; i++) {
    binaryChart[index++] = (binaryNumber >> i) & 1;
  }
}

void decToBinary(uint8_t n, uint8_t binaryChart[], int &index) {
  int i = 0;
  while (n > 0) {
    binaryChart[index++] = n % TWO;
    n = n / TWO;
    i++;
  }

  while (i < MAX_LENGTH_CHART) {
    binaryChart[index++] = 0;
    i++;
  }
}

void resetBinaryChart(uint8_t binaryChart[]) {
  for (int i = 0; i < MAX_BINARY_NUMBER; i++) {
    binaryChart[i] = 0;
  }
}

bool isC3Pressed() {
  if (!(PINC & (1 << PC0))) {
    _delay_ms(DELAY_DEBOUNCE);
    if (!(PINC & (1 << PC0))) {
      return true;
    }
  }
  return false;
}

enum class State {
  START,
  START_FORWARD,
  FORWARD,
  SMALL_SEGMENT,
  TURN,
  START_READING,
  CROSSING_SEGMENT_DETECTED,
  END,
  CALCULATION,
  WAITING,
  SOUND,
  TRANSMISSION,
  SENDING_RS232
};

State state = State::START;

int main() {
  const uint16_t DELAY_START_WHEELS_FORWARD = 1500;
  const uint8_t FORWARD_COUNT = 2;
  const uint8_t CHARACTER_START_POSITION = 44;
  const uint8_t CHARACTER_END_POSITION = 93;
  const uint16_t DELAY_FIVE_HUNDRED = 500;
  const uint16_t DELAY_THOUSAND = 1000;
  const uint16_t DELAY_THOUSAND_FIVE_HUNDRED = 1500;
  const uint16_t DELAY_TWO_THOUSAND = 2000;
  const uint16_t DELAY_SIX_HUNDRED = 600;
  const uint16_t DELAY_SIX_HUNDRED_FIFTY = 650;
  const uint16_t DELAY_NINE_HUNDRED = 900;
  const uint8_t DELAY_SOUND = 50;
  const uint8_t DELAY_DEBOUNCE = 30;
  const uint8_t HIGH_PITCH_SOUND = 80;
  const uint8_t SMALL_SEGMENT_HIGH = 7;
  const uint8_t MEDIUM_SEGMENT_HIGH = 8;
  const uint8_t BIG_SEGMENT_HIGH = 11;
  const uint8_t SMALL_SEGMENT_LOW = 19;
  const uint8_t MEDIUM_SEGMENT_LOW = 17;
  const uint8_t BIG_SEGMENT_LOW = 15;
  const uint8_t UP_LINE_VALUE = 5;
  const uint8_t DOWN_LINE_VALUE = 21;
  const uint8_t DELAY_FIVE = 5;
  const uint8_t ITERATION_FOR_ONE_TWENTY_DEGREES = 200;
  const uint8_t SOUD_COUNT = 3;
  float totalSpaceUpSegment = 0;
  const float NUMBER_OF_CHARACTER = 49;
  int index = 0;
  float segmentProportion;
  uint8_t memoryPosition;
  uint8_t isUp = true;
  int sixSegments = 6;
  int threeSegments = 3;
  int tenSpaceSegments = 10;
  uint8_t upSegmentChart[threeSegments] = {0, 0, 0};
  uint8_t downSegmentChart[threeSegments] = {0, 0, 0};
  uint8_t timeSpaceSegmentChart[tenSpaceSegments];
  uint8_t spaceUpSegmentChart[threeSegments];
  uint8_t spaceDownSegmentChart[threeSegments];
  uint8_t counterTimeSpaceSegment = 0;
  uint8_t counterDownSegment = 0;
  uint8_t counterUpSegment = 0;
  uint8_t turnCounter = 0;
  uint8_t soundCount = 0;

  Wheel2 wheel;
  LineSensor sensor;
  Timer timer(0);
  UART uart;
  Transmission transmission;
  Sound sound;
  Button interruptButton(PD2);
  RobotAffichage2 robotDisplay;
  Led ledMain(&PORTB, &DDRB, PB0, PB1);
  Segment segmentChart[sixSegments];

  DDRC &= ~(1 << PC0); //=========================================  revoir

  while (true) {
    switch (state) {
    case State::START:
      sensor.recenter();
      if (sensor.areAllOff()) {
        wheel.setWheelForward();
        _delay_ms(DELAY_START_WHEELS_FORWARD);
        wheel.stopWheel();
        _delay_ms(DELAY_FIVE_HUNDRED);
        while (!sensor.isS5On()) {
          wheel.turnRight();
        }
        wheel.stopWheel();
        _delay_ms(DELAY_THOUSAND);
        state = State::START_FORWARD;
      }
      break;
    case State::START_FORWARD:
      timer.startTimerCTCRobotTwo();
      sei();
      turnCounter++;
      if (turnCounter == FORWARD_COUNT) {
        isUp = false;
      }
      state = State::FORWARD;
      break;
    case State::FORWARD:
      sensor.recenter();
      if (sensor.isS5On() && sensor.isS3On()) {
        timer.stopTimerCTCRobotTwo();
        cli();
        DEBUG_PRINT(gQuarterOfSecondPass);
        timeSpaceSegmentChart[counterTimeSpaceSegment] = gQuarterOfSecondPass;
        counterTimeSpaceSegment++;
        gQuarterOfSecondPass = 0;
        state = State::TURN;
        break;
      }
      if ((sensor.isS1On() && sensor.isS3On()) && (!sensor.isS5On())) {
        state = State::END;
      }
      break;
    case State::TURN:
      wheel.setWheelForward();
      _delay_ms(DELAY_SIX_HUNDRED);
      if (!(sensor.areAllOff())) {
        turnCounter = 0;
        state = State::CROSSING_SEGMENT_DETECTED;
        break;
      }
      _delay_ms(DELAY_NINE_HUNDRED);
      wheel.stopWheel();
      _delay_ms(DELAY_THOUSAND);
      while (!sensor.isS5On()) {
        wheel.turnRight();
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      state = State::START_FORWARD;
      break;
    case State::SMALL_SEGMENT:
      if (isUp) {
        upSegmentChart[counterUpSegment] = SMALL_SEGMENT_HIGH;
        counterUpSegment++;
      }
      if (!isUp) {
        downSegmentChart[counterDownSegment] = SMALL_SEGMENT_LOW;
        counterDownSegment++;
      }
      gQuarterOfSecondPass = 0;
      while (!sensor.isS1On()) {
        wheel.turnLeft();
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      state = State::START_FORWARD;
      break;
    case State::CROSSING_SEGMENT_DETECTED:
      _delay_ms(DELAY_NINE_HUNDRED);
      wheel.stopWheel();
      _delay_ms(DELAY_THOUSAND);
      wheel.turnRight();
      _delay_ms(DELAY_SIX_HUNDRED);
      for (int i = 0; i < ITERATION_FOR_ONE_TWENTY_DEGREES; i++) {
        wheel.turnRight();
        _delay_ms(DELAY_FIVE);
        if (sensor.isS5On()) {
          break;
        }
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      if (sensor.areAllOff()) {
        state = State::SMALL_SEGMENT;
        break;
      }
      sensor.recenterSegment();
      while (!(sensor.areAllOff())) {
        sensor.recenter();
      }
      wheel.setWheelForward();
      _delay_ms(DELAY_TWO_THOUSAND);
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      wheel.turnRight();
      _delay_ms(DELAY_SIX_HUNDRED_FIFTY);
      while (sensor.areAllOff()) {
        wheel.turnRight();
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      sensor.recenterSegment();
      state = State::START_READING;
      break;
    case State::START_READING:
      timer.startTimerCTCRobotTwo();
      sei();
      while (!(sensor.areAllOff())) {
        sensor.recenter();
      }
      timer.stopTimerCTCRobotTwo();
      cli();
      if (gQuarterOfSecondPass >= MEDIUM_SEGMENT_HIGH) {
        if (isUp) {
          upSegmentChart[counterUpSegment] = BIG_SEGMENT_HIGH;
          counterUpSegment++;
        }
        if (!isUp) {
          downSegmentChart[counterDownSegment] = BIG_SEGMENT_LOW;
          counterDownSegment++;
        }
      } else if (gQuarterOfSecondPass < MEDIUM_SEGMENT_HIGH) {
        if (isUp) {
          upSegmentChart[counterUpSegment] = MEDIUM_SEGMENT_HIGH;
          counterUpSegment++;
        }
        if (!isUp) {
          downSegmentChart[counterDownSegment] = MEDIUM_SEGMENT_LOW;
          counterDownSegment++;
        }
      }
      gQuarterOfSecondPass = 0;
      wheel.setWheelForward();
      _delay_ms(DELAY_THOUSAND_FIVE_HUNDRED);
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      while (!sensor.isS5On()) {
        wheel.turnRight();
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      state = State::START_FORWARD;
      break;
    case State::END:
      wheel.setWheelForward();
      _delay_ms(DELAY_THOUSAND_FIVE_HUNDRED);
      wheel.stopWheel();
      _delay_ms(DELAY_THOUSAND);
      wheel.turnLeft();
      _delay_ms(DELAY_SIX_HUNDRED);
      while (!sensor.isS1On()) {
        wheel.turnLeft();
      }
      wheel.stopWheel();
      _delay_ms(DELAY_FIVE_HUNDRED);
      sensor.recenter();
      while (!sensor.areAllOff()) {
      }
      wheel.stopWheel();
      state = State::CALCULATION;
      break;
    case State::CALCULATION:
      wheel.stopWheel();
      for (int i = 0; i < counterUpSegment + 1; i++) {
        totalSpaceUpSegment += timeSpaceSegmentChart[i];
      }
      segmentProportion = NUMBER_OF_CHARACTER / totalSpaceUpSegment;
      for (int i = 0; i < counterUpSegment; i++) {
        if (i == 0) {
          spaceUpSegmentChart[i] =
              static_cast<int>(segmentProportion * timeSpaceSegmentChart[i]) +
              CHARACTER_START_POSITION;
        }
        if (i != 0) {
          spaceUpSegmentChart[i] =
              memoryPosition +
              static_cast<int>(segmentProportion * timeSpaceSegmentChart[i]);
        }
        memoryPosition = spaceUpSegmentChart[i];
      }
      memoryPosition = 0;
      for (int i = counterUpSegment + FORWARD_COUNT;
           i < counterUpSegment + FORWARD_COUNT + counterDownSegment; i++) {
        if (i == counterUpSegment + FORWARD_COUNT) {
          spaceDownSegmentChart[i - counterUpSegment - FORWARD_COUNT] =
              CHARACTER_END_POSITION -
              static_cast<int>(segmentProportion * timeSpaceSegmentChart[i]);
        }
        if (i != counterUpSegment + FORWARD_COUNT) {
          spaceDownSegmentChart[i - counterUpSegment - FORWARD_COUNT] =
              memoryPosition -
              static_cast<int>(segmentProportion * timeSpaceSegmentChart[i]);
        }
        memoryPosition =
            spaceDownSegmentChart[i - counterUpSegment - FORWARD_COUNT];
      }
      for (int i = 0; i < counterUpSegment; i++) {
        segmentChart[i].startLine = UP_LINE_VALUE;
        segmentChart[i].column = spaceUpSegmentChart[i]; // fonctionne pas
        segmentChart[i].endLine = upSegmentChart[i];
      }
      for (int i = 0; i < counterDownSegment; i++) {
        segmentChart[i + counterUpSegment].startLine = DOWN_LINE_VALUE;
        segmentChart[i + counterUpSegment].column =
            spaceDownSegmentChart[i]; // fonctionne pas
        segmentChart[i + counterUpSegment].endLine = downSegmentChart[i];
      }
      resetBinaryChart(binaryChart);
      for (int i = 0; i < counterDownSegment + counterUpSegment; i++) {
        decToBinary(segmentChart[i].startLine, binaryChart, index);
        decToBinary(segmentChart[i].endLine, binaryChart, index);
        decToBinary(segmentChart[i].column, binaryChart, index);
      }
      decToBinary(counterDownSegment + counterUpSegment, binaryChart, index);

      state = State::WAITING;
      break;
    case State::WAITING:
      wheel.stopWheel();
      ledMain.setLedRed();
      if (isC3Pressed()) {
        _delay_ms(DELAY_DEBOUNCE);
        if (isC3Pressed()) {
          state = State::SENDING_RS232;
          break;
        }
      }
      if (interruptButton.isPressed()) {
        _delay_ms(DELAY_DEBOUNCE);
        if (interruptButton.isPressed()) {
          state = State::SOUND;
        }
      }
      break;
    case State::SOUND:
      ledMain.setLedOff();
      timerTrailToTimerTransmission();
      sound.playSound(HIGH_PITCH_SOUND);
      _delay_ms(DELAY_SOUND);
      sound.stopSound();
      _delay_ms(DELAY_SOUND);
      soundCount++;
      if (soundCount == SOUD_COUNT) {
        soundCount = 0;
        state = State::TRANSMISSION;
      }
      break;
    case State::TRANSMISSION:
      _delay_ms(DELAY_TWO_THOUSAND);
      transmission.start();
      for (int i = 0;
           i < ((counterDownSegment + counterUpSegment) * SOUD_COUNT) *
                       SMALL_SEGMENT_HIGH +
                   SMALL_SEGMENT_HIGH;
           i++) {
        if (binaryChart[i] == 1) {
          transmission.logicalOne();
        }
        if (binaryChart[i] == 0) {
          transmission.logicalZero();
        }
      }
      transmission.stop();
      gButtonPressed = false;
      state = State::WAITING;
      break;
    case State::SENDING_RS232:
      ledMain.setLedGreen();
      robotDisplay.printCircuit(segmentChart,
                                counterDownSegment + counterUpSegment);
      ledMain.setLedOff();
      state = State::WAITING;
      gButtonPressed = false;
      break;
    }
  }
}
