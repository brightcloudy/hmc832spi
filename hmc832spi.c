#include "hmc832spi.h"

void toggleSEN(void) {
    digitalWrite(3, HIGH);
    usleep(10000);
    digitalWrite(3, LOW);
}

unsigned int readReg(unsigned char reg_num) {
  unsigned char buffer[5];
  unsigned int * cmdstart = (unsigned int *) (&buffer[0]);
  *cmdstart = ntohl(0x00000000 | (reg_num << 8));
  wiringPiSPIDataRW(0, buffer, 4);
  toggleSEN();
  *cmdstart = ntohl(0x00000000 | (reg_num << 8));
  wiringPiSPIDataRW(0, buffer, 4);
  toggleSEN();
  unsigned int readResultShifted = (buffer[0] << 25) + (buffer[1] << 17) + (buffer[2] << 9) + (buffer[3] << 1);
  unsigned int readRegValue = (readResultShifted >> 8);
  unsigned int readRegNum = ((readResultShifted & 0xFF) >> 3);
  return readRegValue;
}

void writeReg(unsigned char reg_num, unsigned int value) {
  unsigned char buffer[5];
  unsigned int * cmdstart = (unsigned int *) (&buffer[0]);
  *cmdstart = ntohl((value << 8) | ((reg_num & 0x1F) << 3));
  wiringPiSPIDataRW(0, buffer, 4);
  toggleSEN();
}

void setOutputDivider(unsigned char divider_val) {
  unsigned char buffer[5];
  unsigned int * cmdstart = (unsigned int *) (&buffer[0]);
  unsigned int vcospival = (0x0000000) | (0x02 << 3) | (divider_val << 7);
  *cmdstart = ntohl((vcospival << 8) | (0x05 << 3));
  wiringPiSPIDataRW(0, buffer, 4);
  toggleSEN();
  /* *cmdstart = 0x00000000;
  wiringPiSPIDataRW(0, buffer, 4);
  toggleSEN(); */
}
