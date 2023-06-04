#include <TLE9879_Group.h>
#include <SPI.h>
#include "RCtoPMW.hh"

TLE9879_Group *shields;

// Define RC Input Connections based on PWM pins used
#define CH1 3
#define CH4 9

// define a range of values for reading RC receiver
// This is needed in order to follow the current value of RPM for each motor
const int minPWM = -100;
const int maxPWM = 100;
int defaultPWM = 0;

// defining the limits of the motor
const int maxRPM = 4000;
const int minRPM = -4000;
// defining deadband
const int deadband = 800;

//logic to follow sate of motor
uint8_t MotorState1;
uint8_t MotorState2;

// Integers to represent values from sticks and pots
int ch1Value;
int ch4Value;

// Integers to represent the initial offset of the controller
int offset1;
int offset4;

// RPM current value to follow in functions
int rpm1;
int rpm4;




void setup() {
  // Set up serial monitor
  Serial.begin(9600);

  // Set all PWM pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH4, INPUT);
  
  // Reading offsets for reading the . Controller needs to be idle
  offset1 = readChannel(CH1, minPWM, maxPWM, defaultPWM, 0); 
  offset4 = readChannel(CH4, minPWM, maxPWM, defaultPWM, 0);

  // Creating the shield object and intializing the boards
  shields = new TLE9879_Group(2);
  shields->setMode(HALL, BOARD1);
  shields->setMode(HALL, BOARD2);

  // set the motor parameters
  shields->setParameter(HALL_POLE_PAIRS, 8, BOARD1); 
  shields->setParameter(HALL_INIT_DUTY, 20, BOARD1);
  shields->setParameter(HALL_SPEED_KP,500, BOARD1);
  shields->setParameter(HALL_SPEED_KI,100, BOARD1);
  
  shields->setParameter(HALL_POLE_PAIRS, 8, BOARD2);
  shields->setParameter(HALL_INIT_DUTY, 20, BOARD2);
  shields->setParameter(HALL_SPEED_KP,500, BOARD2);
  shields->setParameter(HALL_SPEED_KI,100, BOARD2);

  MotorState1 = 0;
  MotorState2 = 0;
}

void loop() {

// !! Cannot have functions to control the motors: they get set back in bootloader mode automatically
  
  ch1Value = readChannel(CH1, minPWM, maxPWM, defaultPWM, offset1);
  ch4Value = readChannel(CH4, minPWM, maxPWM, defaultPWM, offset4);

  rpm1 = PMWtoRPM(ch1Value, minPWM, maxPWM, minRPM, maxRPM);
  rpm4 = PMWtoRPM(ch4Value, minPWM, maxPWM, minRPM, maxRPM);

  if(abs(rpm4) < deadband && MotorState2 == 1){
    shields->setMotorMode(STOP_MOTOR, BOARD2);
    MotorState2 = 0;
    delay(10);
  }else if(abs(rpm4) < deadband && MotorState2 == 0){
    
  }else if (abs(rpm4) > deadband && MotorState2 == 1){
    shields->setMotorSpeed(rpm4, BOARD2);
    delay(20);
  }else if ((abs(rpm4) > deadband && MotorState2 == 0)){
    shields->setMotorSpeed(rpm4, BOARD2);
    shields->setMotorMode(START_MOTOR, BOARD2);
    MotorState2 = 1;
    delay(10);
  }

  if (abs(rpm1) < deadband && MotorState1 == 1){
    shields->setMotorMode(STOP_MOTOR, BOARD1);
    MotorState1 = 0;
    delay(10);
  } else if(abs(rpm1) < deadband && MotorState1 == 0){
    
  }else if (abs(rpm1) > deadband && MotorState1 == 1){
    shields->setMotorSpeed(rpm1, BOARD1);
    delay(20);
  }else if (abs(rpm1) > deadband && MotorState1 == 0){
    shields->setMotorSpeed(rpm1, BOARD1);
    shields->setMotorMode(START_MOTOR, BOARD1);
    MotorState1 = 1;
    delay(10);
    }
     


//  Serial.print("rpm4 = ");
//  Serial.println(rpm4);
  
}
