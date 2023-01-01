#include "main.h"

using namespace std;
using namespace pros;

namespace drivetrain {

    #define FRONT_LEFT_MOTOR -6
    #define BACK_LEFT_MOTOR 15
    #define MIDDLE_LEFT_MOTOR 5
    #define MIDDLE_RIGHT_MOTOR -10
    #define FRONT_RIGHT_MOTOR 7
    #define BACK_RIGHT_MOTOR -19
    #define GYRO1_PORT 1
    #define GYRO2_PORT 2
    #define GEARSET E_MOTOR_GEAR_600
    #define WHEEL_DIAMETER 2
    #define STRAFE_COMPENSATION 0.8
    #define SETTLE_TIME_MSEC 500
    #define POSITIONAL_TOLERANCE 3
    #define ANGULAR_TOLERANCE 1
    #define MINIMUM_SPEED 127 * 0.1
    #define kP 8;

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
    double convertToInches(double ticks);
    double getMotorGroupPosition(std::vector<double> positions, int motorGroupSize);
    int angularCorrection(int targetHeading);
    int positionalCorrection(int targetDistance, int currentDistance);
    void strafe(double distance, int speed);
    void forward(double distance, int speed);
    void turnTo(int angle, int speed);

};

namespace distance {

    #define SERVO_PORT 2
    #define SERVO_GEARSET E_MOTOR_GEAR_100
    #define DISTANCE_PORT 9

    extern Motor Servo;
    extern Distance Sensor;

    int read();
    void rotateTo(double angle);

};