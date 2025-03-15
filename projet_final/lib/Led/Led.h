// Auteur: Salma Ben Daly Hassen, Alfred Galibois-Bouchard, Magalie Noel, praise
// mbay

// Description du programme: Led.h décrit la classe Led pour contrôler une LED
// bicolor (verte et rouge). Le constructeur Led(volatile uint8_t* mode,
// volatile uint8_t* port, uint8_t pinGreen, uint8_t pinRed) prend en charge les
// pointeurs vers les registres de mode et de port, ainsi que les positions des
// broches vertes et rouges. Les méthodes publiques setGreen(), setRed(),
// setAmber() et setLedOff() sont fournies pour définir la couleur de la LED ou
// l'éteindre.

// Identification matérielle: DEL +/- , DEL+ --> pinGreen et DEL- --> pinRed.
// Avec les broches A0 et A1 configure en mode sortie et toutes les autres
// broches sont des entrees.

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

class Led {
public:
  Led(volatile uint8_t *mode, volatile uint8_t *port, uint8_t pinGreen,
      uint8_t pinRed);

  void setLedGreen();
  void setLedRed();
  void setLedAmber();
  void setLedOff();

private:
  volatile uint8_t *_mode;
  uint8_t pinGreenPosition;
  uint8_t pinRedPosition;
  static constexpr uint8_t DELAY_AMBER = 5;
  static constexpr uint8_t DELAY_AMBER_RED = 5;
  static constexpr uint8_t DELAY_AMBER_GREEN = 10;
};