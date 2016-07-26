#include "hmc832spi.h"
#include <stdio.h>
int main (int argc, char ** argv) {
  wiringPiSetup();
  digitalWrite(3, LOW);
  pinMode (3, OUTPUT);
  wiringPiSPISetupMode(0, 1000000, 3);
  unsigned int lownoisevals[] = {0x2A, 0x90, 0xF98, 0x4B38, 0x00, 0x30F4A, 0x14D, 0xC1BEFF, 0x30ED5A, 0x2006, 0xF8061, 0x00, 0x00, 0x00, 0x01, 0x20, 0x7FFFF, 0x00, 0x1259, 0x666666};
  unsigned char lownoiseregs[] = {0x03, 0x05, 0x05, 0x05, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x04};
  unsigned int i;
  for (i = 0;i < 0x14;i++) {
    writeReg(lownoiseregs[i], lownoisevals[i]);
  }
  setOutputDivider(10);
  writeReg(0x05, 0x00);
  writeReg(0x03, 42);
  writeReg(0x04, 0x9EB852);
  return 0;
}

