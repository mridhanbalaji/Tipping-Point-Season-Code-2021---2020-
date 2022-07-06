/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Mridhan Balaji                                   */
/*    Created:      Wed May 11 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Intake               motor         21              
// LifterFront          motor_group   1, 2            
// Pneumatics           digital_out   A               
// LifterBack           motor         9               
// DriveTrainLeft       motor_group   13, 14          
// DriveTrainRight      motor_group   17, 18          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition; 

//define your global instances of motors and other devices here
// You may want to perform some actions before the competition starts. Do them in the following function. You must return from this function
// or the autonomous and usercontrol tasks will not be started. This function is only called once after the v5 has been powered on and not every time the robot is disabled. 

int main() {
  //Initalizing Robot Configuration. DO NOT REMOVE!
  vexcodeInit(); 
  //All activites that occur before the competition starts.
  //Example: clearing encoders, setting serve positions, ..
  Pneumatics1.set(false);
  Pneumatics2.set(false);
  
}

int doDrive() {
  int DriveTrainRightVelocity = 0;
  int DriveTrainLeftVelocity = 0;
  while (true) {
    DriveTrainRightVelocity = Controller1.Axis3.position() - Controller1.Axis1.position();
    DriveTrainLeftVelocity = Controller1.Axis3.position() + Controller1.Axis1.position();
    if (DriveTrainRightVelocity > 100) {
      DriveTrainRightVelocity = 100;
    } else if (DriveTrainRightVelocity < -100) {
      DriveTrainRightVelocity = -100;
    }
    if (DriveTrainLeftVelocity > 100) {
      DriveTrainLeftVelocity = 100;
    } else if (DriveTrainLeftVelocity < -100) {
      DriveTrainLeftVelocity = -100;
    }
    DriveTrainRight.spin(vex::directionType::rev, DriveTrainRightVelocity, vex::velocityUnits::pct);
    DriveTrainLeft.spin(vex::directionType::rev, DriveTrainLeftVelocity, vex::velocityUnits::pct);
    vex::task::sleep(20);
  }
  return 0;
}
int doIntake() {
  int intakeVelocity = 0;
  while(true){
    if (Controller1.ButtonX.pressing() and Controller1.ButtonB.pressing()){
      intakeVelocity = 0;
    } else if (Controller1.ButtonX.pressing()) {
      intakeVelocity = 100;
    } else if (Controller1.ButtonB.pressing()) {
      intakeVelocity = -100;
    } else {
      intakeVelocity = 0;
    }
    Intake.spin(vex::directionType::fwd, intakeVelocity, vex::velocityUnits::pct);
    vex::task::sleep(20);
  }
  return 0;
}
int doLifterFront() {
  int lifterFrontVelocity = 0;
  while(true){
    if (Controller1.ButtonR1.pressing() and Controller1.ButtonR2.pressing()) {
      lifterFrontVelocity = 0;
    } else if (Controller1.ButtonR1.pressing()) {
      lifterFrontVelocity = 100;
    } else if (Controller1.ButtonR2.pressing()) {
      lifterFrontVelocity = -100;
    } else {
      lifterFrontVelocity = 0;
    }
    LifterFront.spin(vex::directionType::fwd, lifterFrontVelocity, vex::velocityUnits::pct);
    vex::task::sleep(20);
  }
  return 0;
}
int doLifterBack() {
  int lifterBackVelocity = 0;
  while(true){
    if (Controller1.ButtonL1.pressing() and Controller1.ButtonL2.pressing()) {
      lifterBackVelocity = 0;
    } else if (Controller1.ButtonL1.pressing()) {
      lifterBackVelocity = 100;
    } else if (Controller1.ButtonL2.pressing()) {
      lifterBackVelocity = -100;
    } else {
      lifterBackVelocity = 0;
    }
    LifterBack.spin(vex::directionType::fwd, lifterBackVelocity, vex::velocityUnits::pct);
    vex::task::sleep(20);
  }
  return 0;
}
int doPneumatics() {
  while(true){
    enableDrivePID = false;
    if(Controller1.ButtonUp.pressing()){
      Pneumatics1.set(true);
      Pneumatics2.set(true);
    }
    if(Controller1.ButtonDown.pressing()){
      Pneumatics1.set(false);
      Pneumatics2.set(false);
    }
    vex::task::sleep(20);
  }
  return 0;
}
//User Control Task

void usercontrol(void){
  DriveTrainLeft.setVelocity(100, percent);
  DriveTrainRight.setVelocity(100, percent); 
  Intake.setVelocity(100, percent); 
  LifterFront.setVelocity(100, percent); 
  LifterBack.setVelocity(100, percent);
  vex::task driving(doDrive); 
  vex::task liftingFront(doLifterFront);
  vex::task liftingBack(doLifterBack);
  vex::task intaking(doIntake);
  vex::task doingPneumatics(doPneumatics);
}