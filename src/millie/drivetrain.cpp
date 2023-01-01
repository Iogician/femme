#include "millie/robot.hpp"
#include "pros/distance.hpp"
#include "pros/motors.h"

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
        ALL.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
        FL = forward + turn + strafe;
        FR = forward - turn - strafe;
        ML = forward + turn;
        MR = forward - turn;
        BL = forward + turn - strafe;
        BR = forward - turn + strafe;      
    };

    int heading() {
        int avg = (Gyro1.get_value() + Gyro2.get_value())/20;
        if (avg < 0) avg = 360 - abs(avg);
        return avg;
    };

    double convertToInches(double ticks) {
        ticks *= 3.14 * 2 * WHEEL_DIAMETER;
        return ticks;
    };

    double getMotorGroupPosition(std::vector<double> positions, int motorGroupSize) {
        ALL.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
        double totalPosition = 0;
        for (int i = 0; i < motorGroupSize; i++) totalPosition += positions[i];
        double averagePosition = totalPosition/motorGroupSize;
        averagePosition = convertToInches(averagePosition);
        return averagePosition;
    };

    int angularCorrection(int targetHeading) {
        int turnPower = 0;
        int currentHeading = heading();
        double adjustedAngle = currentHeading;

        if (currentHeading > 180 && targetHeading < 180) adjustedAngle -= 360;
        else if (currentHeading < 180 && targetHeading > 180) adjustedAngle += 360;

        currentHeading = adjustedAngle;

        double angleDifference = abs(targetHeading - currentHeading);

        int direction = 0;

        if (currentHeading < targetHeading) direction = 1;
        else if (currentHeading > targetHeading) direction = -1;
        else direction = 0;

        if (angleDifference < ANGULAR_TOLERANCE) turnPower = 0;
        else {
            double powerRatio = 0;
            if (currentHeading > targetHeading) powerRatio = (currentHeading - targetHeading)/currentHeading;
            else if (currentHeading < targetHeading) powerRatio = (targetHeading - currentHeading)/targetHeading;
            turnPower = abs(powerRatio) * direction;
        };

        turnPower *= kP;

        return turnPower;
    };

    int positionalCorrection(int targetDistance, int currentDistance) {
        int throttle = 0;
        if (targetDistance > currentDistance) throttle = abs((targetDistance - currentDistance)/targetDistance);
        if (targetDistance < currentDistance) throttle = -abs((currentDistance - targetDistance)/currentDistance);
        throttle *= kP;
        return throttle;
    };

    void strafe(double distance, int speed) {
        int direction = distance / abs(distance);
        distance = convertToInches(distance) / STRAFE_COMPENSATION;
        speed *= direction;      
        ALL.tare_position();
        ALL.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
        int heldHeading = heading();
        while (abs(getMotorGroupPosition(RIGHT.get_positions(), 2)) < abs(distance) - POSITIONAL_TOLERANCE && abs(getMotorGroupPosition(RIGHT.get_positions(), 2)) > abs(distance) + POSITIONAL_TOLERANCE) {
            int current = getMotorGroupPosition(RIGHT.get_positions(), 2);
            int turnSpeed = 127 * angularCorrection(heldHeading);
            int strafeSpeed = speed * positionalCorrection(distance, current);
            int correctedDirection = direction * (strafeSpeed/abs(strafeSpeed));
            if (abs(strafeSpeed) < MINIMUM_SPEED) strafeSpeed = MINIMUM_SPEED * correctedDirection;
            drive(strafeSpeed, 0, turnSpeed);
            delay(20);
        };        
    };

    void forward(double distance, int speed) {
        int direction = distance / abs(distance);
        distance = convertToInches(distance);
        speed *= direction;
        ALL.tare_position();
        ALL.set_brake_modes(E_MOTOR_BRAKE_BRAKE);
        int heldHeading = heading();
        while (abs(getMotorGroupPosition(ALL.get_positions(), 6)) < abs(distance) - POSITIONAL_TOLERANCE && abs(getMotorGroupPosition(ALL.get_positions(), 6)) > abs(distance) + POSITIONAL_TOLERANCE) {
            int current = getMotorGroupPosition(ALL.get_positions(), 6);
            int turnSpeed = 127 * angularCorrection(heldHeading);
            int forwardSpeed = speed * positionalCorrection(distance, current);
            int correctedDirection = direction * (forwardSpeed/abs(forwardSpeed));
            if (abs(forwardSpeed) < MINIMUM_SPEED) forwardSpeed = MINIMUM_SPEED * correctedDirection;
            drive(0, forwardSpeed, turnSpeed);
            delay(20);
        };
    };

    void turnTo(int angle, int speed) {
        while (heading() < angle - ANGULAR_TOLERANCE && heading() > angle + ANGULAR_TOLERANCE) {
            int actualSpeed = speed * angularCorrection(angle);
            int direction = speed/abs(speed);
            if (abs(actualSpeed) < MINIMUM_SPEED) actualSpeed = MINIMUM_SPEED * direction;
            drive(0, 0, actualSpeed);
            delay(20);
        };
    };    
};

namespace distance {

    Motor Servo(SERVO_PORT, SERVO_GEARSET);
    Distance Sensor(DISTANCE_PORT);

    int read() {
        return Sensor.get();
    };
    void rotateTo(double angle) {
        Servo.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        Servo.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
        Servo.move_absolute(angle, 50);
    };

};

