// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Claw                 motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Claw                 motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Claw                 motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Claw                 motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// Motor8               motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Catapult             motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Clawbot (Drivetrain) - Template                           */
/*                                                                            */
/*    Name:                                                                   */
/*    Date                                                                    */
/*    Class:                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// PickupMotor          motor         9               
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

bool catapultOn = true;

void caton(){
  if(catapultOn == true){
    Catapult.spin(forward);
    catapultOn = false;
    Catapult.setVelocity(100, percent);
  }else{
    catapultOn = true;
    Catapult.setVelocity(0, percent);
  }
}

double map(double x, double a1, double a2, double b1, double b2) {
  return (x-a1)/(a2-a1) * (b2-b1)+b1;
}

double speedcontroler() {
    int difference = Controller1.Axis3.position(percent) - Controller1.Axis2.position(percent);
    if (difference < 0) {
        difference = -difference; // make the difference positive if it's negative
    }
    if (difference < 30) {
      difference = 0;
    }
    printf("Difference: %d\n", difference);
    double speed = map(difference, 200, 0, 0.9, 1.0);
    double modifier = 0.75;
    bool faster = Controller1.ButtonL1.pressing();
    bool mid = Controller1.ButtonL2.pressing();
    if (faster) {
      modifier = 0.5;
    }
    if (mid) {
      modifier = 0.75;
    }
    if (mid && faster) {
      modifier = 0.25;
    }
    speed *= modifier;
    printf("Speed: %f\n", speed);
    return speed;
}

void Drive() {
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  Claw.spin(forward);
  Claw.setMaxTorque(100, percent);
  Controller1.ButtonX.pressed(caton);

  while (true) {
    double speed = speedcontroler();

    if (Controller1.ButtonR1.pressing()){
      Claw.setVelocity(-100, percent);
    } else if (Controller1.ButtonR2.pressing()){
      Claw.setVelocity(100, percent);
    } else {
      Claw.setVelocity(0, percent);
    }

    LeftMotor.setVelocity(speed*Controller1.Axis3.position(percent),percent);
    RightMotor.setVelocity(speed*Controller1.Axis2.position(percent),percent);
    task::sleep(10);
  }
}

void pre_auton(){
  vexcodeInit();
}

void move(int speed, double distance){
  LeftMotor.setVelocity(speed, percent);
  RightMotor.setVelocity(speed, percent);
  LeftMotor.spin(forward);
  RightMotor.spinFor(forward, distance, turns);
  LeftMotor.stop();
}

void autonomous(){
  Catapult.spin(forward);
  RightMotor.spin(forward);
  Catapult.setVelocity(100, percent);
  RightMotor.setVelocity(100, percent);
  LeftMotor.spinFor(reverse, 2, turns);
  RightMotor.stop();
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(Drive);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
