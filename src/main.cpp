/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Mann Made 3796A                                           */
/*    Created:      Fri 11/6/2020                                             */
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
// LIntakeMotor         motor         8               
// RIntakeMotor         motor         9               
// Controller1          controller                    
// OutakeMotor          motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

/* Program Variables
base_speed: The velocity which the base will move at by defalt.

intake_speed: The speed at which the transport mechanism will spin.

drive_sun: short for drive sensitivity. The variable will effect the degree which the analog sticks
  need to be pressed to trigger motion.
*/

int intake_speed = 100;

#include "vex.h"

// Helper Functions

/*
Sets the velocity of each of the four drive motors and spins them.
@param rf the modifying value for RFDriveMotor velocity  
@param lf the modifying value for LFDriveMotor velocity
@param br the modifying value for BRDriveMotor velocity
@param bl the modifying value for BLDriveMotor velocity
@return none
*/

void base_drive(int rf, int lf, int br, int bl)
{
  RFDriveMotor.setVelocity(rf, percent);
  LFDriveMotor.setVelocity(lf, percent);
  BRDriveMotor.setVelocity(br, percent);
  BLDriveMotor.setVelocity(bl, percent);

  RFDriveMotor.spin(forward);
  LFDriveMotor.spin(forward);
  BRDriveMotor.spin(forward);
  BLDriveMotor.spin(forward);
}

/*
Spins all motors on the intake and outake
*/
void intake_spin()
{
  LIntakeMotor.setVelocity(intake_speed, percent);
  RIntakeMotor.setVelocity(intake_speed, percent);
  OutakeMotor.setVelocity(intake_speed, percent);

  LIntakeMotor.spin(forward);
  RIntakeMotor.spin(reverse);
  OutakeMotor.spin(reverse);
}
/*
Stops the intake motors
*/
void halt_intake()
{
  LIntakeMotor.stop();
  RIntakeMotor.stop();
  OutakeMotor.stop();
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
    int joystick_y_axis = Controller1.Axis3.position(percent);
    int joystick_x_axis = Controller1.Axis4.position(percent);
    int turn_axis = Controller1.Axis1.position(percent);

    int RF_velocity = joystick_y_axis - joystick_x_axis;
    int LF_velocity = joystick_y_axis + joystick_x_axis;
    int BR_velocity = joystick_x_axis - joystick_y_axis;
    int BL_velocity = joystick_x_axis + joystick_y_axis;

    bool intake_button = Controller1.ButtonR1.pressing();

    // Spins the drive motors to move.
    // While the right joystick is not in use the base will drive in an eight directional path.
    // Whle the right joystick is in use all motors will turn to rotate the robot in place.
    if (turn_axis != 0)
    {
      base_drive(RF_velocity, LF_velocity, BR_velocity, BL_velocity);
    }
    else 
    {
      base_drive(turn_axis, turn_axis, turn_axis, turn_axis);
    }

    // Spins intake motors while right trigger is pressed.
    if (intake_button)
    {
      intake_spin();
    }
    else
    {
      halt_intake();
    }
      
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
