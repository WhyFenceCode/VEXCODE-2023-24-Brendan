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
// PickupMotor          motor         10              
// Controller1          controller                    
// RightMotor           motor         18              
// LeftMotor            motor         13              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

double map(double x, double a1, double a2, double b1, double b2) {
  return (x-a1)/(a2-a1) * (b2-b1)+b1;
}

double speedcontroler() {
    int difference = Controller1.Axis2.position(percent) - Controller1.Axis2.position(percent);
    if (difference < 0) {
        difference = -difference; // make the difference positive if it's negative
    }
    if (difference < 30) {
      difference = 0;
    }
    double speed = map(difference, 200, 0, 0.5, 1.0);
    double modifier = 0.75;
    bool faster = Controller1.ButtonL1.pressing();
    bool fastest = Controller1.ButtonL2.pressing();
    if (faster) {
      modifier = 0.5;
    }
    if (fastest) {
      modifier = 1.0;
    }
    if (fastest && faster) {
      modifier = 0.25;
    }
    speed *= modifier;
    return speed;
}

void Drive() {
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  PickupMotor.spin(forward);
        PickupMotor.setStopping(hold);
  while (true) {
    double speed = speedcontroler();

    LeftMotor.setVelocity(speed*Controller1.Axis3.position(percent),percent);
    RightMotor.setVelocity(speed*Controller1.Axis2.position(percent),percent);
    if (Controller1.ButtonR1.pressing()) {
      PickupMotor.setVelocity(-8,percent);
    } else if (Controller1.ButtonR2.pressing()) {
      PickupMotor.setVelocity(8,percent);
    } else if (Controller1.ButtonUp.pressing()) {
      PickupMotor.setVelocity(-3,percent);
    } else if (Controller1.ButtonDown.pressing()) {
      PickupMotor.setVelocity(3,percent);
    } else {
      PickupMotor.setVelocity(0,percent);
    }

    task::sleep(10);
    }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drive();
}
