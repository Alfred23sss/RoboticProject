#include "ObstacleDetector.h"

ObstacleDetector::ObstacleDetector() {}

uint16_t ObstacleDetector::getDistance() {
  DDRA &= ~(1 << PORTA1);
  uint16_t distanceSum = 0;
  for (uint8_t i = 0; i < N_READ; ++i) {
    distanceSum += can_.lecture(DETECTOR_OUTPUT) >> PRECISION_BIT_SHIFT;
    _delay_ms(5);
  }
  return distanceSum / N_READ;
}

bool ObstacleDetector::isSpotDetected() {
  uint16_t distance = getDistance();
  return distance >= MIN_DISTANCE_TO_DETECT &&
         distance <= MAX_DISTANCE_TO_DETECT;
}