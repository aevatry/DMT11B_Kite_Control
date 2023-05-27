# DMT11B_Kite_Control
 Arduino code for control of the BLDC motors in control pod

Project is to control a kite using two bldc motors. The motors are controlled using a BLDC motor shield based on arduino and RC controller (receiver is flying with the kite)
Motor used : DF45M024053-A2 from nanotec
BLDC motor shield: BLDC Shield with TLE9879QXA40 for Arduino
Radio Controller: FS-T6
Radio Receiver: FS-R6B
 
For the motors need a 24V power supply. Max motor current is 7A. Max discharge current of batteries (NiMH AA) is 7.6A. 
Use a LM2596 for stepdown voltage to power the arduino using the same battery. 

