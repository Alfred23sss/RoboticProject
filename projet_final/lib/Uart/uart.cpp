#include "uart.h"
#include "stdio.h"
#include "string.h"

UART::UART() {
  UBRR0H = 0;

  UBRR0L = 0xCF;

  UCSR0A |= (1 << UDRE0);

  UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void UART::transmission(uint16_t donnees) {
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = donnees;
}

unsigned char UART::reception() {
  while (!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void UART::print(int value) {
  char buffer[COMPARE_VALUE];
  snprintf(buffer, COMPARE_VALUE, "%d\n", value);
  print(buffer, COMPARE_VALUE);
}

void UART::print(char *str, uint8_t longueur) {
  for (int j = 0; j < longueur; j++) {
    transmission(str[j]);
  }
}
void UART::print(char *str) {
  for (uint8_t j = 0; j < strlen(str); j++) {
    transmission(str[j]);
    _delay_ms(5);
  }
}

void UART::print1(const char *str) {
  for (uint8_t j = 0; j < strlen(str); j++) {
    transmission(str[j]);
    _delay_ms(5);
  }
}