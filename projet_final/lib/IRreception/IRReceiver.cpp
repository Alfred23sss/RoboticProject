#include "IRReceiver.h"
#include "Uart/uart.h"

IRReceiver::IRReceiver(uint8_t receiverPin) : receiverPin_(receiverPin) {}

void IRReceiver::initialize() { DDRD &= ~(1 << receiverPin_); }
