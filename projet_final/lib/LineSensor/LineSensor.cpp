#include "LineSensor.h"

LineSensor::LineSensor() {
  DDRA &=
      ~(1 << PORTA1 | 1 << PORTA2 | 1 << PORTA3 | 1 << PORTA4 | 1 << PORTA5);
  wheel = Wheel2();
}

uint8_t LineSensor::getNumbersSensors() {
  uint8_t counter = 0;
  if (isS1On()) {
    counter++;
  }
  if (isS2On()) {
    counter++;
  }
  if (isS3On()) {
    counter++;
  }
  if (isS4On()) {
    counter++;
  }
  if (isS5On()) {
    counter++;
  }
  return counter;
}

bool LineSensor::isS1On() { return (MASK_S1 & PINA); }

bool LineSensor::isS2On() { return (MASK_S2 & PINA); }

bool LineSensor::isS3On() { return (MASK_S3 & PINA); }

bool LineSensor::isS4On() { return (MASK_S4 & PINA); }

bool LineSensor::isS5On() { return (MASK_S5 & PINA); }

bool LineSensor::areAllOn() { return (MASK_S & PINA) == 0b111110; }

bool LineSensor::areAllOff() { return (MASK_S & PINA) == 0b000000; }

void LineSensor::recenter() {
  if (isS5On()) {
    wheel.turnSlightlyMoreRight();
    if (isS4On()) {
      wheel.turnSlightlyRight();
    }
  }
  if (isS4On()) {
    wheel.turnSlightlyRight();
  }
  if (isS3On()) {
    wheel.setWheelForward();
  }
  if (isS2On()) {
    wheel.turnSlightlyLeft();
  }
  if (isS1On()) {
    wheel.turnSlightlyMoreLeft();
    if (isS2On()) {
      wheel.turnSlightlyLeft();
    }
  }
}

void LineSensor::recenterSegment() {
  while (true) {
    if (isS5On()) {
      wheel.turnSlightlyMoreRight();
      if (isS4On()) {
        wheel.turnSlightlyRight();
      }
    }
    if (isS4On()) {
      wheel.turnSlightlyRight();
    }
    if (isS3On()) {
      wheel.stopWheel();
      break;
    }
    if (isS2On()) {
      wheel.turnSlightlyLeft();
    }
    if (isS1On()) {
      wheel.turnSlightlyMoreLeft();
      if (isS2On()) {
        wheel.turnSlightlyLeft();
      }
    }
  }
}

void LineSensor::recenterBackLeft() {
  if (isS1On()) {
    wheel.turnSlightlyRightBackward();
    while (!(isS3On())) {
    }
  }
}

void LineSensor::recenterBackRight() {
  if (isS5On()) {
    wheel.turnSlightlyLeftBackward();
    while (!(isS3On())) {
    }
  }
}

void LineSensor::recenterBack() {
  if (isS5On()) {
    wheel.turnRight();
  }
  if (isS1On()) {
    wheel.turnLeft();
  }
  wheel.setWheelBackward();
}