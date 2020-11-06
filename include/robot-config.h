using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RFDriveMotor;
extern motor LFDriveMotor;
extern motor BRDriveMotor;
extern motor BLDriveMotor;
extern motor LIntakeMotor;
extern motor RIntakeMotor;
extern controller Controller1;
extern motor OutakeMotor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );