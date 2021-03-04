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
// right_front_motor    motor         10              
// left_front_motor     motor         12              
// left_rear_motor      motor         6               
// right_rear_motor     motor         16              
// left_intake_motor    motor         13              
// right_intake_motor   motor         14              
// Controller1          controller                    
// outake_motor         motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

/* Program Variables
base_speed_mod: A percentage that will limit the max speed of the drive.

turn_speed_mod: A percentage that will limit the max speed of the left analog turn.

intake_speed: The speed at which the transport mechanism will spin.

auton_base_drive: The speed that the robot will drive during autonomus period.

auton_mode: An integer that indicates the autonmus to preform.

*/

int intake_speed = 100;
int auton_base_drive = 75;

double base_speed_mod = .75;
double turn_speed_mod = .75;

/*
Auton Modes:
0 : Starts back parralell with colored tile facing away from the right goal. Scores center goal on team side.
1 : Starts front parralell with colored tile facing twaords the right goal. Scores the right goal on team side.
*/

int auton_mode = 0;

#include "vex.h"

// Driver Functions

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

// Auton Functions
/**
Drives the robot in a line for a given number of seconds.

@param speed the percent unit of power to feed each drive motor. Positive values will drive foward and negative values back.
@param time the number of seconds to spin drive motors.
*/
void auton_drive(double speed, double time)
{
  base_drive(-speed, speed, -speed, speed);
  
  wait(time, seconds);

  right_front_motor.stop();
  left_front_motor.stop();
  right_rear_motor.stop();
  left_rear_motor.stop();
}

/**
Spins both outakes and intakes for a specified number of seconds.

@param time the number of seconds to spin intake/outake motors.
*/
void auton_intake_outake_spin(double time)
{
  right_intake_motor.setVelocity(-intake_speed, percent);
  left_intake_motor.setVelocity(intake_speed, percent);
  outake_motor.setVelocity(-intake_speed, percent);

  right_intake_motor.spin(forward);
  left_intake_motor.spin(forward);
  outake_motor.spin(forward);

  wait(time, seconds);

  right_intake_motor.stop();
  left_intake_motor.stop();
  outake_motor.stop();
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
  // drive foward enough to flip the hood
  auton_drive(auton_base_drive, .5);

  // spin both outake and intake to push preload into the center of the outake
  auton_intake_outake_spin(.25);
  // drive to the goal
  auton_drive(auton_base_drive, 1);

  // spin outake to score the ball.
  auton_intake_outake_spin(1);
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
    int intake_button = Controller1.ButtonR2.pressing();
    int outake_button = Controller1.ButtonR1.pressing();
    int rev_intake_button = Controller1.ButtonL2.pressing();
    int rev_outake_button = Controller1.ButtonL1.pressing();

    // Sets velocity of all four drive motors based on the position of the joysticks.
    int right_front_velocity = -joystick_y_axis + (joystick_x_axis * turn_speed_mod) - turn_axis;
    int left_front_velocity = joystick_y_axis + (joystick_x_axis * turn_speed_mod) + turn_axis;
    int right_rear_velocity = -joystick_y_axis + (joystick_x_axis * turn_speed_mod) - turn_axis;
    int left_rear_velocity = joystick_y_axis + (joystick_x_axis * turn_speed_mod) + turn_axis;

    // Spins the drive motors to move.
    // While the right joystick is not in use the base will drive in an eight directional path.
    // Whle the right joystick is in use all motors will turn to rotate the robot in place.

    base_drive(right_front_velocity, left_front_velocity, right_rear_velocity, left_rear_velocity);

    // Sets the velocity and direction of the Intake motors.
    // Right buttons will spin the intakes inwards.
    // Left button will spin the intakes in reverse.
    left_intake_motor.setVelocity((intake_speed * intake_button) + (rev_intake_button * -intake_speed), percent);
    right_intake_motor.setVelocity((-intake_speed * intake_button) + (rev_intake_button * intake_speed), percent);

    // Sets the velocity of the Outake motors.
    outake_motor.setVelocity((-intake_speed * outake_button) + (intake_speed * rev_outake_button), percent);

    // Spins both intake and outake motors. Both spin independently of one another.
    left_intake_motor.spin(forward);
    right_intake_motor.spin(forward);
    outake_motor.spin(forward);
      
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
