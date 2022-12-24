#include "main.h"

using namespace pros;

namespace drivetrain {

#define FRONT_LEFT_MOTOR 1
#define BACK_LEFT_MOTOR 2
#define MIDDLE_LEFT_MOTOR 3
#define MIDDLE_RIGHT_MOTOR 4
#define FRONT_RIGHT_MOTOR 5
#define BACK_RIGHT_MOTOR 6
#define GYRO1_PORT 1
#define GYRO2_PORT 2
#define GEARSET E_MOTOR_GEAR_600
#define WHEEL_DIAMETER 2
#define STRAFE_COMPENSATION 0.8
#define SETTLE_TIME_MSEC 500
#define POSITIONAL_TOLERANCE 3
#define ANGULAR_TOLERANCE 1
#define MINIMUM_SPEED 127 * 0.1

extern Motor FL;
extern Motor BL;
extern Motor ML;
extern Motor MR;
extern Motor FR;
extern Motor BR;
extern MotorGroup ALL;
extern ADIGyro Gyro1;
extern ADIGyro Gyro2;

int heading();
void drive(int strafe, int forward, int turn);
void strafe(double distance, int speed);
void forward(double distance, int speed);
void turnTo(int angle, int speed);

}