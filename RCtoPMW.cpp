/*
Script created for RC control of the BLDC motors for DMT11B project
Created and edited by Antonin Roche on 27/03/2023
*/

#include <Arduino.h>
#include <TLE9879_Group.h>

#include "RCtoPMW.hh"


int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue, int offset){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit)-offset;
}

int PMWtoRPM (int channelValue, int minLimit, int maxLimit, int minRPM, int maxRPM){
    return map(channelValue,minLimit, maxLimit, minRPM, maxRPM);
}

void changeRPM(int RPM_val, uint8_t board, TLE9879_Group *shields){
    shields->setMotorSpeed(RPM_val, board);
    shields->setMode(START_MOTOR, board);
}

//void stopMotor(int curRPM, uint8_t board, TLE9879_Group *shields){
//    // Two cases: clockwise (-RPM) or anti-clockwise direction(+RPM)
//
//    if (curRPM<0){
//
//        while (curRPM < -400){ //low limit on speed can change
//            curRPM = curRPM + 300;
//            shields->setMotorSpeed(curRPM, board);
//        }
//        shields->setMotorMode(STOP_MOTOR, board);
//    } else if(curRPM>0){
//        
//        while (curRPM > 400){ //low limit on speed can change
//            curRPM = curRPM - 300;
//            shields->setMotorSpeed(curRPM, board);
//        }
//        shields->setMotorMode(STOP_MOTOR, board);
//    } else{
//
//    }
//}
