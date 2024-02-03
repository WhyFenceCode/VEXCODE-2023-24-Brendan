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
    printf("Speed: %f\n", speed);
    return speed;
}

void Drive() {
  LeftMotor.spin(forward);
  RightMotor.spin(forward);
  PickupMotor.spin(forward);
  PickupMotor.setStopping(hold);
  PickupMotor.setMaxTorque(100, percent);
  while (true) {
    double speed = speedcontroler();

    LeftMotor.setVelocity(speed*Controller1.Axis3.position(percent),percent);

    RightMotor.setVelocity(speed*Controller1.Axis2.position(percent),percent);
    static double pickup_speed = 0;
    if (Controller1.ButtonR1.pressing()) {
      pickup_speed = -12;
    } else if (Controller1.ButtonR2.pressing()) {
      pickup_speed = 12;
    } else if (Controller1.ButtonUp.pressing()) {
      pickup_speed = -7;
    } else if (Controller1.ButtonDown.pressing()) {
      pickup_speed = 7;
    } else {
      pickup_speed = 0;
    }
    PickupMotor.setVelocity(pickup_speed,percent);
    // printf("Speed: %f\n", speed);
    // if (pickup_speed > 0) {
    //   pickup_speed-= 0.2;
    // } else if (pickup_speed < 0) {
    //   pickup_speed+= 0.2;
    // }
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
  PickupMotor.setVelocity(25, percent); 
  PickupMotor.spinFor(forward, 120, degrees); 
  PickupMotor.setVelocity(100, percent);
  move(100, 4.25);
  // left
  LeftMotor.spinFor(reverse, 2.1, turns);
  // right
  // RightMotor.spinFor(reverse, 2.1, turns);
  PickupMotor.setVelocity(25, percent); 
  PickupMotor.spinFor(reverse, 85, degrees);
  move (100, 4);
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
