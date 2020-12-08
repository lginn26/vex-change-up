// ---- START VEXCODE CONFIGURED DEVICES ----//
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
// Controller1          controller                    
// right_front_motor    motor         10              
// left_front_motor     motor         12              
// left_rear_motor      motor         6               
// right_rear_motor     motor         9               
// left_intake_motor    motor         13              
// right_intake_motor   motor         14              
// ---- END VEXCODE CONFIGURED DEVICES ----

/* Program Variables
base_speed_mod: A percentage that will limit the max speed of the drive.

turn_speed_mod: A percentage that will limit the max speed of the left analog turn.

intake_speed: The speed at which the transport mechanism will spin.

drive_sun: short for drive sensitivity. The variable will effect the degree which the analog sticks
  need to be pressed to trigger motion.
*/

int intake_speed = 100;
double base_speed_mod = .75;
double turn_speed_mod = .75;

#include "vex.h"

// Helper Functions

/*
Sets the velocity of each of the four drive motors and spins them.
@param rf the modifying value for right_front_motor velocity  
@param lf the modifying value for left_front_motor velocity
@param br the modifying value for right_rear_motor velocity
@param bl the modifying value for left_rear_motor velocity
@return none
*/

void base_drive(int rf, int lf, int br, int bl)
{
  right_front_motor.setVelocity(rf * base_speed_mod, percent);
  left_front_motor.setVelocity(lf * base_speed_mod, percent);
  right_rear_motor.setVelocity(br * base_speed_mod, percent);
  left_rear_motor.setVelocity(bl * base_speed_mod, percent);

  right_front_motor.spin(forward);
  left_front_motor.spin(forward);
  right_rear_motor.spin(forward);
  left_rear_motor.spin(forward);
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
    int intake_button = Controller1.ButtonR1.pressing();

    // Sets velocity of all four drive motors based on the position of the joysticks.
    int right_front_velocity = -joystick_y_axis + (joystick_x_axis * turn_speed_mod) - turn_axis;
    int left_front_velocity = joystick_y_axis + (joystick_x_axis * turn_speed_mod) + turn_axis;
    int right_rear_velocity = -joystick_y_axis + (joystick_x_axis * turn_speed_mod) - turn_axis;
    int left_rear_velocity = joystick_y_axis + (joystick_x_axis * turn_speed_mod) + turn_axis;

    // Spins the drive motors to move.
    // While the right joystick is not in use the base will drive in an eight directional path.
    // Whle the right joystick is in use all motors will turn to rotate the robot in place.

    base_drive(right_front_velocity, left_front_velocity, right_rear_velocity, left_rear_velocity);

    // Spins intake motors while right trigger is pressed.
    left_intake_motor.setVelocity(intake_speed * intake_button, percent);
    right_intake_motor.setVelocity(intake_speed * intake_button, percent);
    
    left_intake_motor.spin(forward);
    right_intake_motor.spin(reverse);
      
     // Sleep the task for a short amount of time to
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
