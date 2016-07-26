#ifndef HMC832SPI_H_
#define HMC832SPI_H_
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

void toggleSEN(void);
unsigned int readReg(unsigned char reg_num);
void writeReg(unsigned char reg_num, unsigned int value);
void setOutputDivider(unsigned char divider_val);
#endif
