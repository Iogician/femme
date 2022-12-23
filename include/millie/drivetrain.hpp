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
#define SETTLE_TIME_MSEC 500

extern Motor FL;
extern Motor BL;
extern Motor ML;
extern Motor MR;
extern Motor FR;
extern Motor BR;
extern ADIGyro Gyro1;
extern ADIGyro Gyro2;

void drive(int strafe, int forward, int turn);
void strafe(int distance, int speed);
void forward(int distance, int speed);
void turnTo(int angle, int speed);

}