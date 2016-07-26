#include "hmc832spi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main (int argc, char ** argv) {
  wiringPiSetup();
  digitalWrite(3, LOW);
  pinMode (3, OUTPUT);
  wiringPiSPISetupMode(0, 1000000, 3);
  int i;
  unsigned char outputdivider = 1;
  if (argc != 2) {
    return 1;
  }
  float frequency = atof(argv[1]);
  if (frequency < 1500.0) {
    for (i = 62;i >= 2;i -= 2) {
      if ((frequency * i) < 3000.0) {
        outputdivider = i;
        break;
      }
    }
  }
  float vcofrequency = frequency * outputdivider;
  unsigned int integerdivider = floor(vcofrequency / 50.0);
  unsigned int fractionaldivider = round((fmod(vcofrequency, 50.0) / 50.0) * pow(2,24));
  printf("%i %i %i\n", outputdivider, integerdivider, fractionaldivider);
  setOutputDivider(outputdivider);
  writeReg(0x05, 0x00);
  writeReg(0x03, integerdivider);
  writeReg(0x04, fractionaldivider); 
  return 0;
}

