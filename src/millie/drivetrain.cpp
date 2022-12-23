#include "millie/robot.hpp"

using namespace pros;

namespace drivetrain {
    Motor FL(FRONT_LEFT_MOTOR);
    Motor BL(BACK_LEFT_MOTOR);
    Motor ML(MIDDLE_LEFT_MOTOR);
    Motor MR(MIDDLE_RIGHT_MOTOR);
    Motor FR(FRONT_RIGHT_MOTOR);
    Motor BR(BACK_RIGHT_MOTOR);
    MotorGroup ALL({FL, BL, ML, MR, FR, BR});
    MotorGroup LEFT({FL, BR});
    MotorGroup RIGHT({FR, BL});
    ADIGyro Gyro1(GYRO1_PORT);
    ADIGyro Gyro2(GYRO2_PORT);

    void drive(int strafe, int forward, int turn) {
        FL = forward + turn + strafe;
        FR = forward - turn - strafe;
        ML = forward + turn;
        MR = forward - turn;
        BL = forward + turn - strafe;
        BR = forward - turn + strafe;      
    };

    void strafe(int distance, int speed) {
        
    };

    void forward(int distance, int speed) {
        int direction = distance / abs(distance);
        speed *= direction;
        ALL.tare_position();
        ALL.move_absolute(distance, speed);
    };

    void turnTo(int angle, int speed) {

    };    
}