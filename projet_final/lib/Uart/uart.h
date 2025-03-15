// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise
// mbay

// Description du programme: UART.h décrit la classe UART, utilisée pour la
// communication série sur le microcontrôleur . Cette classe comprend un
// constructeur UART() et un destructeur ~UART() par défaut. Elle propose une
// méthode transmission(uint8_t donnees) pour envoyer des données via le port
// série.

// Identification matérielle: x

#ifndef UART_H
#define UART_H

#ifdef DEBUG
#define DEBUG_PRINT(...) UART::print(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)                                                       \
  do {                                                                         \
  } while (0)
#endif

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

class UART {
public:
  UART();
  static void transmission(uint16_t donnees);
  static unsigned char reception();
  static void print(char *str);
  static void print(int value);
  static void print(char *str, uint8_t longueur);
  static void print1(const char *str);

private:
  static const uint8_t COMPARE_VALUE = 8;
};

#endif