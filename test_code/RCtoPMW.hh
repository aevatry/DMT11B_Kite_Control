#ifndef RCtoPMW_H
#define RCtoPMW_H

#include <Arduino.h>

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue, int offset);
int PMWtoRPM (int channelValue, int minLimit, int maxLimit, int minRPM, int maxRPM);
void changeRPM(int RPM_val, uint8_t board, TLE9879_Group *shields);
void stopMotor(int curRPM, uint8_t board, TLE9879_Group *shields);


#endif