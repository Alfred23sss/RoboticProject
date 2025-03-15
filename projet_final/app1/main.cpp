/**
 * app1 - main.cpp
 * Contrôle du robot dans une boîte pour trouver la sortie et recevoir des
 * informations
 *
 * Ce programme contrôle un robot situé dans une boîte, chargé de trouver la
 * sortie. Le robot utilise des capteurs infrarouges pour détecter les parois de
 * la boîte et se déplacer vers le centre. Une fois au centre, le robot attend
 * des données envoyées par un autre robot pour déterminer sa prochaine action.
 *
 * Le contrôle des moteurs du robot, la détection des obstacles et la
 * communication avec l'autre robot sont gérés par différentes fonctions et
 * modules.
 *
 * Materiel: Capteur infrarouge, capteur de distance infrarouge, piezo
 * electrique, bouton PD2,
 *
 * Auteur: Salma Ben Daly, Alfred Galibois-Bouchard, Magalie Noel et Praise Mbay
 * Mansang Date: 16 avril 2024
 */

/**
 * Tableau d'états pour le contrôle du robot dans une boîte
 *
 * État               | Description
 * -------------------|---------------------------------------------------------------
 * WAITRED            | Attente de l'appui sur le bouton d'interruption avec la
 * LED rouge allumée SOUND              | Émission d'un son aigu, puis
 * transition vers la réception RECEPTION          | Désactivation de la LED
 * principale avant de démarrer la réception START_RECEPTION    | Vérification
 * du début de la réception IR VERIFICATION_START | Vérification de la réception
 * IR après un certain nombre de boucles ATTENTE_LECTURE    | Attente d'une
 * séquence de bits à lire LECTURE            | Lecture des bits reçus et
 * stockage dans un tableau FIN_RECEPTION      | Traitement des données reçues
 * et vérification de leur validité SOUND2             | Émission d'un son grave
 * en cas d'échec de la réception RECEPTION_REUSSI   | Confirmation de la
 * réception réussie et traitement des données
 */

#define F_CPU 8000000UL
#include "Button/Button.h"
#include "Can/can.h"
#include "DrawCircuit/robotdessin.h"
#include "IRreception/IRReceiver.h"
#include "Memory/memory_24C.h"
#include "Obstacle/ObstacleDetector.h"
#include "Sound/sound.h"
#include "Timer/Timer.h"
#include "Uart/uart.h"
#include "Wheel/Wheel.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

volatile bool isHigh = false;

ISR(INT1_vect) {
  _delay_us(10);
  isHigh = !isHigh;
}

const uint8_t PERCENTAGE_PWM_MAX = 100;
const uint8_t PERCENTAGE_PWM_RIGHT = 48;
const uint8_t PERCENTAGE_PWM_LEFT = 44;
const uint8_t MAX_VALUE_ACCEPTED = 19;
const uint8_t MAX_SEGMENT = 6;
const uint16_t MAX_BINARY_VALUE_ACCEPTED = 142;
const uint8_t NUMBER_OF_READS = 10;
const uint8_t VALUE_AFTER_RED_DOT = 55;
const uint8_t VALUE_BEFORE_RED_DOT = 50;
const uint8_t START_TIME_WHEEL = 10;
const uint16_t STOP_TIME_WHEEL = 500;
const uint8_t START_TIME_WHEEL_LEFT = 21;
const uint8_t VALUE_GAP_MAX = 25;
const uint8_t VALUE_GAP_MIN = 7;
const uint16_t DELAY_BETWEEN_TURN = 250;
const uint8_t PERCENTAGE_PWM_LEFT_TURN_LEFT = 57;
const uint8_t PERCENTAGE_PWM_RIGHT_TURN_LEFT = 66;
const uint8_t HIGH_PITCH_SOUND = 80;
const uint8_t DELAY_BETWEEN_SOUND = 50;
const uint16_t SAFETY_DELAY = 500;
const uint8_t START_COUNTER_LOOP = 24;
const uint8_t DELAY_BETWEEN_RECEPTION = 100;
const uint8_t ACCEPTABLE_VALUE_TO_START = 18;
const uint16_t COUNTER_VALUE_TO_STOP = 500;
const uint8_t COUNTER_VALUE_FOR_ONE = 10;
const uint8_t COUNTER_VALUE_FOR_ZERO = 9;
const uint8_t SEVEN_BITS_LENGTH = 7;
const uint8_t VALUE_PER_SEGMENT_OBJECT = 3;
const uint8_t LOW_PITCH_SOUND = 52;
const uint16_t LOW_PITCH_SOUND_DELAY = 1000;
const uint8_t NUMBER_OF_TURNS = 11;
const uint8_t TOP_BACKWARD_ROBOT_ONE_POSITION = 1;
const uint8_t TOP_ROBOT_ONE_POSITION = 2;
const uint8_t DOWN_ROBOT_ONE_POSITION = 3;
const uint8_t DOWN_BACKWARD_ROBOT_ONE_POSITION = 4;
const uint8_t VALUE_TO_CENTER = 0;
const uint8_t VALUE_FAR_OF_WALL = 1;
const uint8_t VALUE_CLOSE_TO_WALL = 2;

uint8_t bits[SEVEN_BITS_LENGTH];
uint16_t receptionValueChart[MAX_VALUE_ACCEPTED];
uint8_t receivedData[MAX_BINARY_VALUE_ACCEPTED];
Segment segmentChart[MAX_SEGMENT];
uint16_t counter = 0;
uint8_t memoryAdress = 0;
uint8_t indexSegmentChart = 0;
uint8_t receptionValueChartIndex = 0;
uint16_t totalValue = 0;
uint8_t receivedIndex = 0;
int cmp = 0;
int soundCount = 0;
int positionRobot1 = 0;

uint8_t numberOfSegment;
uint8_t verificationSegment;
uint8_t dec;
int pos;
RobotAffichage displayRobot;
UART uart;
Memoire24CXXX memory;
Wheel motor;
Sound sound;
ObstacleDetector obstacleDetector;
can can;
Button interruptButton(PD2);
Timer timer(0);
IRReceiver reception(PD3);
Led ledMain(&PORTB, &DDRB, PB0, PB1);

void initialisationISR() {
  EIMSK |= (1 << INT1);
  EICRA |= (1 << ISC10);
  EIFR |= (1 << INTF1);
  sei();
}

int binaireVersDecimal(uint8_t bits[]) {
  int poids = 1;
  int decimal = 0;
  for (int i = 0; i < SEVEN_BITS_LENGTH; ++i) {
    decimal += bits[i] * poids;
    poids *= 2;
  }
  return decimal;
}

enum class State {
  WAITRED,
  SOUND,
  RECEPTION,
  START_RECEPTION,
  VERIFICATION_START,
  ATTENTE_LECTURE,
  LECTURE,
  FIN_RECEPTION,
  RECEPTION_REUSSI,
  SOUND2
};

State state = State::WAITRED;

int main() {
  reception.initialize();
  initialisationISR();

  uint16_t dis = obstacleDetector.getDistance();
  for (int i = 0; i < NUMBER_OF_READS; i++) {
    dis += obstacleDetector.getDistance();
  }
  dis /= NUMBER_OF_READS;
  if (dis > VALUE_AFTER_RED_DOT) {
    pos = VALUE_CLOSE_TO_WALL;
  } else if (dis > VALUE_BEFORE_RED_DOT && dis < VALUE_AFTER_RED_DOT) {
    pos = VALUE_TO_CENTER;
  } else {
    pos = VALUE_FAR_OF_WALL;
  }

  while (true) {
    uint16_t distance = obstacleDetector.getDistance();
    if (distance > VALUE_BEFORE_RED_DOT && distance < VALUE_AFTER_RED_DOT) {
      motor.stopWheel();
      break;

    } else if (distance > VALUE_AFTER_RED_DOT) {
      motor.setWheelBackward(PERCENTAGE_PWM_MAX, PERCENTAGE_PWM_MAX);
      _delay_ms(START_TIME_WHEEL);
      motor.setWheelBackward(PERCENTAGE_PWM_RIGHT, PERCENTAGE_PWM_LEFT);
    } else {
      motor.setWheelForward(PERCENTAGE_PWM_MAX, PERCENTAGE_PWM_MAX);
      _delay_ms(START_TIME_WHEEL);
      motor.setWheelForward(PERCENTAGE_PWM_RIGHT, PERCENTAGE_PWM_LEFT);
    }
  }

  while (true) {
    _delay_ms(STOP_TIME_WHEEL);
    uint16_t distance1 = obstacleDetector.getDistance();
    if (distance1 > VALUE_GAP_MAX) {
      cmp++;
      motor.turnLeft(PERCENTAGE_PWM_MAX, PERCENTAGE_PWM_MAX);
      _delay_ms(START_TIME_WHEEL_LEFT);
      motor.turnLeft(PERCENTAGE_PWM_RIGHT_TURN_LEFT,
                     PERCENTAGE_PWM_LEFT_TURN_LEFT);
      _delay_ms(DELAY_BETWEEN_TURN);
      motor.stopWheel();
      distance1 = obstacleDetector.getDistance();
    } else if (VALUE_GAP_MIN <= distance1 && distance1 <= VALUE_GAP_MAX) {
      motor.stopWheel();
      break;
    }
  }

  while (true) {
    switch (state) {
    case State::WAITRED:
      ledMain.setLedRed();
      if (interruptButton.isPressed()) {
        state = State::SOUND;
      }
      break;
    case State::SOUND:
      sound.playSound(HIGH_PITCH_SOUND);
      _delay_ms(DELAY_BETWEEN_SOUND);
      sound.stopSound();
      _delay_ms(DELAY_BETWEEN_SOUND);
      soundCount++;
      if (soundCount == 3) {
        soundCount = 0;
        state = State::RECEPTION;
      }
      break;
    case State::RECEPTION:
      ledMain.setLedOff();
      _delay_ms(SAFETY_DELAY);
      state = State::START_RECEPTION;
      break;
    case State::START_RECEPTION:
      if (isHigh) {
        state = State::VERIFICATION_START;
      }
      break;
    case State::VERIFICATION_START:
      for (int i = 0; i < START_COUNTER_LOOP; i++) {
        _delay_us(DELAY_BETWEEN_RECEPTION);
        if (isHigh) {
          counter++;
        }
      }
      if (counter >= ACCEPTABLE_VALUE_TO_START) {
        counter = 0;
        state = State::ATTENTE_LECTURE;
        break;
      }
      counter = 0;
      state = State::START_RECEPTION;
      break;
    case State::ATTENTE_LECTURE:
      counter = 0;
      while (isHigh) {
        _delay_us(DELAY_BETWEEN_RECEPTION);
        counter++;
      }
      if (counter >= 3 && counter <= COUNTER_VALUE_TO_STOP) {
        state = State::LECTURE;
      } else if (counter > COUNTER_VALUE_TO_STOP) {
        state = State::FIN_RECEPTION;
        break;
      }
      break;
    case State::LECTURE:
      if (counter > COUNTER_VALUE_FOR_ONE) {
        receivedData[receivedIndex] = 1;
      }
      if (counter <= COUNTER_VALUE_FOR_ZERO) {
        receivedData[receivedIndex] = 0;
      }
      receivedIndex++;
      state = State::ATTENTE_LECTURE;
      break;
    case State::FIN_RECEPTION:
      for (int i = 0; i < receivedIndex; i += SEVEN_BITS_LENGTH) {
        for (int j = 0; j < SEVEN_BITS_LENGTH; j++) {
          bits[j] = receivedData[i + j];
        }
        dec = binaireVersDecimal(bits);
        receptionValueChart[receptionValueChartIndex] = dec;
        receptionValueChartIndex++;
      }
      verificationSegment =
          (receptionValueChartIndex - 1) / VALUE_PER_SEGMENT_OBJECT;
      if (verificationSegment ==
          receptionValueChart[receptionValueChartIndex - 1]) {
        state = State::RECEPTION_REUSSI;
        break;
      }
      state = State::SOUND2;
      break;
    case State::SOUND2:
      sound.playSound(LOW_PITCH_SOUND);
      _delay_ms(LOW_PITCH_SOUND_DELAY);
      sound.stopSound();
      state = State::WAITRED;
      break;
    case State::RECEPTION_REUSSI:
      ledMain.setLedGreen();
      while (!interruptButton.isPressed()) {
      }
      numberOfSegment =
          ((receivedIndex - SEVEN_BITS_LENGTH) / VALUE_PER_SEGMENT_OBJECT) /
          SEVEN_BITS_LENGTH;
      for (int i = 0; i < numberOfSegment; i++) {
        segmentChart[i].startLine = receptionValueChart[indexSegmentChart];
        indexSegmentChart++;
        segmentChart[i].endLine = receptionValueChart[indexSegmentChart];
        indexSegmentChart++;
        segmentChart[i].column = receptionValueChart[indexSegmentChart];
        indexSegmentChart++;
      }
      if (pos == VALUE_FAR_OF_WALL) {
        if (cmp > NUMBER_OF_TURNS) {
          positionRobot1 = DOWN_ROBOT_ONE_POSITION;
        } else {
          positionRobot1 = TOP_ROBOT_ONE_POSITION;
        }
      } else if (pos == VALUE_CLOSE_TO_WALL) {
        if (cmp > NUMBER_OF_TURNS) {
          positionRobot1 = TOP_BACKWARD_ROBOT_ONE_POSITION;
        } else {
          positionRobot1 = DOWN_BACKWARD_ROBOT_ONE_POSITION;
        }
      }

      displayRobot.printCircuit(positionRobot1, segmentChart, numberOfSegment);
      state = State::RECEPTION_REUSSI;
      break;
    }
  }
}