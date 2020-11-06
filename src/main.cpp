/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RFDriveMotor         motor         1               
// LFDriveMotor         motor         2               
// BRDriveMotor         motor         3               
// BLDriveMotor         motor         4               
// LeftIntakeMotor      motor         8               
// RightIntakeMotor     motor         9               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

// Program Variables
int base_speed = 75;
double drive_sen = .5;

#include "vex.h"

// Helper Functions

/*
Sets the velocity of each of the four drive motors 
@param rf the modifying value for RFDriveMotor velocity  
@param lf the modifying value for LFDriveMotor velocity
@param br the modifying value for BRDriveMotor velocity
@param bl the modifying value for BLDriveMotor velocity
@return none
*/
void set_drive(int rf, int lf, int br, int bl)
{
  RFDriveMotor.setVelocity(rf * base_speed, percent);
  LFDriveMotor.setVelocity(lf * base_speed, percent);
  BRDriveMotor.setVelocity(br * base_speed, percent);
  BLDriveMotor.setVelocity(bl * base_speed, percent);
}

void base_drive()
{
  RFDriveMotor.spin(forward);
  LFDriveMotor.spin(forward);
  BRDriveMotor.spin(forward);
  BLDriveMotor.spin(forward);
}

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // Local Drive Variables
    int joystick_y_axis = Controller1.Axis3.value();
    int joystick_x_axis = Controller1.Axis4.value();

    // The conditional sets drive motor velocities based on joystick positions

    if (joystick_y_axis >= drive_sen)
    {
      // drive north
      set_drive(1, 1, -1, -1);
    }
    else if (((joystick_y_axis > 0) && (joystick_y_axis < drive_sen)) && ((joystick_x_axis > 0) && (joystick_x_axis < drive_sen)))
    {
      // drive northeast
      set_drive(0, 1, 0, -1);
    }
    else if (joystick_x_axis >= drive_sen)
    {
      // drive east
      set_drive(1, -1, 1, -1);
    }
    else if (joystick_y_axis <= -drive_sen)
    {
      // drive south
      set_drive(-1, -1, 1, 1);
    }
    else if (joystick_x_axis <= -drive_sen)
    {
      // drive west
      set_drive(-1, 1, -1, 1);
    }

    base_drive();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
