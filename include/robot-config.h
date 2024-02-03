using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Catapult;
extern controller Controller1;
extern motor RightMotor;
extern motor LeftMotor;
extern motor Claw;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );