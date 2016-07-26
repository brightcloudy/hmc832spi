#include "hmc832spi.h"
#include <stdio.h>
int main (int argc, char ** argv) {
  wiringPiSetup();
  digitalWrite(3, LOW);
  pinMode (3, OUTPUT);
  wiringPiSPISetupMode(0, 1000000, 3);
  unsigned int i;
  for (i = 0;i < 0x14;i++) {
    printf("0x%06X in register 0x%02X\n", readReg(i), i);
  }
  return 0;
}

