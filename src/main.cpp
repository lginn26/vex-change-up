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
int base_speed = 75;
int intake_speed = 100;
double drive_sen = 50;

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
  
/*
Spins all four drive motors in their set velocities.
*/
void base_drive()
{
  RFDriveMotor.spin(forward);
  LFDriveMotor.spin(forward);
  BRDriveMotor.spin(forward);
  BLDriveMotor.spin(forward);
}

/*
Stops all four drive motors.
*/
void halt_drive()
{
  RFDriveMotor.stop();
  LFDriveMotor.stop();
  BRDriveMotor.stop();
  BLDriveMotor.stop();
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
    bool intake_button = Controller1.ButtonR1.pressing();

    bool active_y_axis = (joystick_y_axis > drive_sen) || (joystick_y_axis < -drive_sen);
    bool active_x_axis = (joystick_x_axis > drive_sen) || (joystick_x_axis < -drive_sen);
    bool active_turn_axis = turn_axis != 0;

    // The conditional sets drive motor velocities based on joystick positions.
    // It is not responcible for driving the motors

    if ((joystick_y_axis >= drive_sen) && (joystick_x_axis >= drive_sen))
    {
      // drive northeast
      set_drive(0, 1, -1, 0);
    }
    else if ((joystick_y_axis <= -drive_sen) && (joystick_x_axis >= drive_sen))
    {
      // drive southeast
      set_drive(-1, 0, 0, 1);
    }
    else if ((joystick_y_axis <= -drive_sen) && (joystick_x_axis <= -drive_sen))
    {
      // drive southwest
      set_drive(0, -1, 1, 0);
    }
    else if ((joystick_y_axis >= drive_sen) && (joystick_x_axis <= -drive_sen))
    {
      // drive northwest
      set_drive(1, 0, 0, -1);
    }
    else if (joystick_y_axis >= drive_sen)
    {
      // drive north
      set_drive(1, 1, -1, -1);
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

    // The conditional is responcible for setting drive motor velocities when needed.
    if (turn_axis > 0)
    {
      // turn right
      set_drive(-1, 1, -1, 1);
    }
    else if (turn_axis < 0)
    {
      // turn left
      set_drive(1, -1, 1, -1);
    }

    // Spins all motors in their set direction while joysticks are in use.
    if (active_y_axis || active_x_axis || active_turn_axis)
    { 
      base_drive();
    }
    else
    {
      halt_drive();
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
