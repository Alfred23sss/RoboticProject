#include "robotdessin2.h"
#include "Segment/segment.h"

Led led(&PORTB, &DDRB, PB0, PB1);

void RobotAffichage2::printCircuit(Segment segmentChart[], uint8_t sizeChart) {
  UART uart;
  _delay_ms(1000);
  for (uint8_t i = 0; i < 28; i++) {
    led.setLedGreen();
    _delay_ms(100);
    led.setLedOff();
    for (uint8_t j = 0; j < 101; j++) {
      if (i == 0) {
        if (j == 0) {
          uart.print1("\u250C");
        } else if (j == 100) {
          uart.print1("\u2510");
        } else {
          uart.print1("\u2500");
        }
      } else if ((i == 1) || (i == 2) || (i == 24) || (i == 25)) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else {
          uart.print1(" ");
        }
      } else if (i == 3) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6) {
          uart.print1("\u250F");
        } else if (j == 32) {
          uart.print1("\u2513");
        } else if (j > 6 && j < 32) {
          uart.print1("\u2501");
        } else {
          uart.print1(" ");
        }
      } else if ((i > 3 && i < 5) || (i > 21 && i < 23)) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6 || j == 32) {
          uart.print1("\u2503");
        } else {
          uart.print1(" ");
        }
      } else if (i == 5) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6 || j == 32) {
          uart.print1("\u2503");
        } else if (j == 43) {
          uart.print1("\u2554");
        } else if (j == 94) {
          uart.print1("\u2557");
        } else if (j > 43 && j < 94) {
          bool isAdded = false;
          for (uint8_t k = 0; k < sizeChart && !isAdded; k++) {
            if (segmentChart[k].startLine == i) {
              if (segmentChart[k].column == j) {
                uart.print1("\u2566");
                isAdded = true;
              }
            }
          }
          if (!isAdded) {
            uart.print1("\u2550");
          }
        } else {
          uart.print1(" ");
        }
      } else if (i > 5 && i < 12) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6 || j == 32) {
          uart.print1("\u2503");
        } else if (j == 43 || j == 94) {
          uart.print1("\u2551");
        } else if (j > 43 && j < 94) {
          bool isAdded = false;
          for (uint8_t k = 0; k < sizeChart && !isAdded; k++) {
            if (i > segmentChart[k].startLine && i <= segmentChart[k].endLine) {
              if (segmentChart[k].column == j) {
                uart.print1("\u2551");
                isAdded = true;
              }
            }
          }
          if (!isAdded) {
            uart.print1(" ");
          }
        } else if (j > 16 && j < 22) {

          uart.print1(" ");

        } else {
          uart.print1(" ");
        }
      } else if (i == 12) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6) {
          uart.print1("\u2503");
        } else if (j == 43 || j == 94) {
          uart.print1("\u2551");
        } else if (j > 43 && j < 94) {
          uart.print1(" ");
        } else {
          uart.print1(" ");
        }
      } else if (i == 13) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6) {
          uart.print1("\u2503");
        } else if (j == 43) {
          uart.print1("\u2563");
        } else if (j > 37 && j < 43) {
          uart.print1("\u2550");
        } else if (j == 94) {
          uart.print1("\u2551");
        } else if (j > 43 && j < 94) {
          uart.print1(" ");
        } else {
          uart.print1(" ");
        }

      } else if (i == 14) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6) {
          uart.print1("\u2503");
        } else if (j == 43 || j == 94) {
          uart.print1("\u2551");
        } else if (j > 43 && j < 94) {
          uart.print1(" ");
        } else {
          uart.print1(" ");
        }
      } else if (i > 14 && i < 21) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6 || j == 32) {
          uart.print1("\u2503");
        } else if (j == 43 || j == 94) {
          uart.print1("\u2551");
        } else if (j > 43 && j < 94) {
          bool isAdded = false;
          for (uint8_t k = 0; k < sizeChart && !isAdded; k++) {
            if (i < segmentChart[k].startLine && i >= segmentChart[k].endLine) {
              if (segmentChart[k].column == j) {
                uart.print1("\u2551");
                isAdded = true;
              }
            }
          }
          if (!isAdded) {
            uart.print1(" ");
          }
        } else if (j > 16 && j < 22) {

          uart.print1(" ");

        } else {
          uart.print1(" ");
        }
      }

      else if (i == 21) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6 || j == 32) {
          uart.print1("\u2503");
        } else if (j == 43) {
          uart.print1("\u255A");
        } else if (j == 94) {
          uart.print1("\u255D");
        } else if (j > 43 && j < 94) {
          bool isAdded = false;
          for (uint8_t k = 0; k < sizeChart && !isAdded; k++) {
            if (segmentChart[k].startLine == i) {
              if (segmentChart[k].column == j) {
                uart.print1("\u2569");
                isAdded = true;
              }
            }
          }
          if (!isAdded) {
            uart.print1("\u2550");
          }
        } else {
          uart.print(" ");
        }
      }

      else if (i == 23) {
        if (j == 0 || j == 100) {
          uart.print1("\u2502");
        } else if (j == 6) {
          uart.print1("\u2517");
        } else if (j == 32) {
          uart.print1("\u251B");
        } else if (j > 6 && j < 32) {
          uart.print1("\u2501");
        } else {
          uart.print1(" ");
        }

      } else if (i == 26) {
        if (j == 0) {
          uart.print1("\u2514");
        } else if (j == 100) {
          uart.print1("\u2518");
        } else {
          uart.print1("\u2500");
        }
      } else if (i == 27) {
        if (j == 0) {
          uart.print1("Produit par: P.A.M.S");
        }
      }

      else {
        uart.print1(" ");
      }
    }
    uart.print1("\n");
  }
}
