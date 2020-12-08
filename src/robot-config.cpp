#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor right_front_motor = motor(PORT10, ratio18_1, false);
motor left_front_motor = motor(PORT12, ratio18_1, false);
motor left_rear_motor = motor(PORT6, ratio18_1, false);
motor right_rear_motor = motor(PORT9, ratio18_1, false);
motor left_intake_motor = motor(PORT13, ratio18_1, false);
motor right_intake_motor = motor(PORT14, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}