#include "robotdessin.h"

Led led(&PORTB, &DDRB, PB0, PB1);

void RobotAffichage::printPosition1(UART &uart, int i, int j) {
  if (i == 7) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 17) {
      uart.print1("\u2571");
    } else if (j == 21) {
      uart.print1("\u2572");
    }
  } else if (i == 8) {
    if (j == 17 || j == 21) {
      uart.print1("\u2502");
    } else {
      uart.print1(" ");
    }
  } else if (i == 9) {
    if (j == 17 || j == 18 || j == 20 || j == 21) {
      uart.print1("\u2506");
    } else {
      uart.print1(" ");
    }
  } else if (i == 10) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 21) {
      uart.print1("\u2571");
    } else if (j == 17) {
      uart.print1("\u2572");
    }
  } else {
    uart.print1(" ");
  }
}

void RobotAffichage::printPosition2(UART &uart, int i, int j) {
  if (i == 7) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 17) {
      uart.print1("\u2571");
    } else if (j == 21) {
      uart.print1("\u2572");
    }
  } else if (i == 9) {
    if (j == 17 || j == 21) {
      uart.print1("\u2502");
    } else {
      uart.print1(" ");
    }
  } else if (i == 8) {
    if (j == 17 || j == 18 || j == 20 || j == 21) {
      uart.print1("\u2506");
    } else {
      uart.print1(" ");
    }
  } else if (i == 10) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 21) {
      uart.print1("\u2571");
    } else if (j == 17) {
      uart.print1("\u2572");
    }
  } else {
    uart.print1(" ");
  }
}

void RobotAffichage::printPosition3(UART &uart, int i, int j) {
  if (i == 17) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 17) {
      uart.print1("\u2571");
    } else if (j == 21) {
      uart.print1("\u2572");
    }
  } else if (i == 18) {
    if (j == 17 || j == 21) {
      uart.print1("\u2502");
    } else {
      uart.print1(" ");
    }
  } else if (i == 19) {
    if (j == 17 || j == 18 || j == 20 || j == 21) {
      uart.print1("\u2506");
    } else {
      uart.print1(" ");
    }
  } else if (i == 20) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 21) {
      uart.print1("\u2571");
    } else if (j == 17) {
      uart.print1("\u2572");
    }
  } else {
    uart.print1(" ");
  }
}

void RobotAffichage::printPosition4(UART &uart, int i, int j) {
  if (i == 17) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 17) {
      uart.print1("\u2571");
    } else if (j == 21) {
      uart.print1("\u2572");
    }
  } else if (i == 19) {
    if (j == 17 || j == 21) {
      uart.print1("\u2502");
    } else {
      uart.print1(" ");
    }
  } else if (i == 18) {
    if (j == 17 || j == 18 || j == 20 || j == 21) {
      uart.print1("\u2506");
    } else {
      uart.print1(" ");
    }
  } else if (i == 20) {
    if (j == 18 || j == 19 || j == 20) {
      uart.print1("\u2500");
    } else if (j == 21) {
      uart.print1("\u2571");
    } else if (j == 17) {
      uart.print1("\u2572");
    }
  } else {
    uart.print1(" ");
  }
}

void RobotAffichage::printCircuit(int positionR1, Segment segmentChart[],
                                  uint8_t chartSize) {
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
          for (uint8_t k = 0; k < chartSize && !isAdded; k++) {
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
          for (uint8_t k = 0; k < chartSize && !isAdded; k++) {
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
          if (positionR1 == 1) {
            printPosition1(uart, i, j);
          } else if (positionR1 == 2) {
            printPosition2(uart, i, j);
          } else {
            uart.print1(" ");
          }
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
          for (uint8_t k = 0; k < chartSize && !isAdded; k++) {
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
          if (positionR1 == 3) {
            printPosition3(uart, i, j);
          } else if (positionR1 == 4) {
            printPosition4(uart, i, j);
          } else {
            uart.print1(" ");
          }
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
          for (uint8_t k = 0; k < chartSize && !isAdded; k++) {
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
