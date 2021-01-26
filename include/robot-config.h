using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor right_front_motor;
extern motor left_front_motor;
extern motor left_rear_motor;
extern motor right_rear_motor;
extern motor left_intake_motor;
extern motor right_intake_motor;
extern controller Controller1;
extern motor outake_motor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );