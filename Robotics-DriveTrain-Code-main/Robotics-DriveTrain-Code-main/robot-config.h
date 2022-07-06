using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Intake;
extern motor_group LifterFront;
extern digital_out Pneumatics1;
extern motor LifterBack;
extern motor_group DriveTrainLeft;
extern motor_group DriveTrainRight;
extern digital_out Pneumatics2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );