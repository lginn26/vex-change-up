#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RFDriveMotor = motor(PORT1, ratio18_1, false);
motor LFDriveMotor = motor(PORT2, ratio18_1, false);
motor BRDriveMotor = motor(PORT3, ratio18_1, false);
motor BLDriveMotor = motor(PORT4, ratio18_1, false);
motor LIntakeMotor = motor(PORT8, ratio18_1, false);
motor RIntakeMotor = motor(PORT9, ratio18_1, false);
controller Controller1 = controller(primary);
motor OutakeMotor = motor(PORT10, ratio18_1, false);

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