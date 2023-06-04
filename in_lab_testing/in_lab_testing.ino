#include <TLE9879_Group.h>
#include <SPI.h>

TLE9879_Group *shields;

void setup() {

  // Creating the shield object and intializing the boards
  shields = new TLE9879_Group(1);
  shields->setMode(HALL, BOARD1);

  // set the motor parameters
  shields->setParameter(HALL_POLE_PAIRS, 8, BOARD1); 
  shields->setParameter(HALL_INIT_DUTY, 20, BOARD1);
  shields->setParameter(HALL_SPEED_KP,500, BOARD1);
  shields->setParameter(HALL_SPEED_KI,100, BOARD1);

  // Starting the motor and stopping the motor

  shields->setMotorSpeed(-1000, BOARD1);
  shields->setMotorMode(START_MOTOR, BOARD1);
  delay(3000);
  
  shields->setMotorMode(STOP_MOTOR, BOARD1);

  shields->setParameter(HALL_INPUT_A ,0, BOARD1);
  shields->setParameter(HALL_INPUT_B ,1, BOARD1);
  shields->setParameter(HALL_INPUT_C ,2, BOARD1);
  delay(1000);
  
  shields->setMotorSpeed(-1000, BOARD1);
  shields->setMotorMode(START_MOTOR, BOARD1);
  delay(3000);
  
  shields->setMotorMode(STOP_MOTOR, BOARD1);

  delay(1000);

  
}

void loop() {
  // put your main code here, to run repeatedly:
    

}
