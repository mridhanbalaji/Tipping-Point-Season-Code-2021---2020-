/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Mridhan Balaji                                   */
/*    Created:      Wed May 11 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

//Setting PID Values - Proportional, Integral, Derivative
double kP  = 0.0; 
double kI = 0.0; 
double kD = 0.0;
double turnkP = 0.0;
double turnkI = 0.0; 
double turnkD = 0.0; 

//Autonomous Settings
float desiredValue = 0;
float computedValue = desiredValue*28.648; 
float desiredTurnValue = 0; 

float error;
float prevError = 0; 
float derivative; 
float totalError = 0; 

float turnError; 
float turnPrevError = 0;
float turnDerivative;
float turnTotalError = 0; 

bool resetDriveSensors = false; 


//EnableDrivePID meant for Loop 
bool enableDrivePID = true; 

//PID for DriveTrain 
int drivePID(){
  if (resetDriveSensors){
    resetDriveSensors = false; 
    DriveTrainLeft.setPosition(0, degrees);
    DriveTrainRight.setPosition(0, degrees); 
  }
  while(enableDrivePID){
    //Getting Position for both of the Motors
    int leftDriveTrainPosition = DriveTrainLeft.position(degrees);
    int rightDriveTrainPosition = DriveTrainRight.position(degrees);

    //Lateral Movement PID
    //Get Average of the Two Motor Groups
    float averagePosition = (rightDriveTrainPosition + leftDriveTrainPosition)/2; 
    //Proportional
    error = averagePosition - computedValue; 
    //Derivative 
    derivative = error - prevError;
    //Integral
    totalError += error; 

    double lateralMotorPower = error * kP + derivative * kD + totalError * kI; 

    //Turning Movement PID
    //Get Average of the Two Motor Groups
    float turnDifference = leftDriveTrainPosition - rightDriveTrainPosition; 

    //Proportional
    turnError = turnDifference - desiredTurnValue;

    //Derivative 
    turnDerivative = turnError - turnPrevError; 

    //Integral 
    turnTotalError += turnError; 

    double turnMotorPower = turnError * turnkP + turnDerivative * turnkD + turnTotalError *turnkI; 
    //////////////////////////////////////////////////////////////////////
    DriveTrainLeft.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt); 
    DriveTrainRight.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt); 

    prevError = error; 
    turnPrevError = turnError; 
    vex::task::sleep(20); 
  }
  return 1; 
}

//Autonomous Task

void autonomous (void){
  //......Insert pain here (auton code)
  vex::task pid(drivePID); 
}

//Create the gps sensor, and establish the variable
public vex::gps::gps(int32_t index, double ox, double oy, distanceUnits units=distanceUnits::mm, double heading_offset=0, turnType dir=turnType::right)



//set the Origin
public void vex::gps::setOrigin(double x, double y, distanceUnits units=distanceUnits::mm)

// Even Better, sets the origin, to the starting position, use over that
public void vex::gps::setOrigin()



//sETTING THE DESIRED LOCAITION FOR AUTON, OR OTHER TASKS
public void vex::gps::setLocation(double x, double y, distanceUnits units=distanceUnits::mm, double angle=0, rotationUnits units_r=rotationUnits::deg)

//THIS IS THE SAME THING, BUT WITHOUT UNITS FOR X,Y AND ROTIAITION
public void vex::gps::setLocation(double x, double y, double angle

//To use to see if the GPS sensors locaition has changed. (Would recomend refreshing and updating the cordinates every 10 miliseconds)
public void vex::gps::changed(void(*callback)(void))

// X positionof the GPS Sensor
public double vex::gps::xPosition(distanceUnits units=distanceUnits::mm)


//The Y position of the GPS sensor
public double vex::gps::yPosition(distanceUnits units=distanceUnits::mm)