#include "millie/robot.hpp"
#include "pros/motors.h"

using namespace pros;

namespace intake {

    Motor motor(INTAKE_PORT, INTAKE_GEARSET);
    Optical optical(OPTICAL_PORT);

    void opticalLED(int pwm) {
        optical.set_led_pwm(pwm);
    };

    void spin(double pwr) {
        motor.move_voltage(MAXIMUM_VOLTAGE * pwr);
        opticalLED(pwr * 100);
        if (abs(pwr) > 0) flywheel::brake(true); 
        else flywheel::brake(false); 
    };

    void spinForTime(double pwr, int time) {
        spin(pwr);
        wait(time);
        spin(0);
    };

    string getColor() {
        double hue = optical.get_hue();
        string color = "None";
        if (optical.get_proximity() > 200) {
            if (hue > 300 || hue < 30) color = "Blue";
            if (hue > 180 || hue < 300) color = "Red";
        };
        return color;
    };

}

namespace flywheel {

    Motor motor(FLYWHEEL_PORT, FLYWHEEL_GEARSET);

    int targetSpeed = 0;
    double actualSpeed = 0;

    int voltageUpdate() {
        if (targetSpeed == 0)  {motor.move_voltage(0); return 0; }
        actualSpeed = motor.get_actual_velocity();
        int currentVoltage = actualSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int convertedTarget = targetSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int error = (convertedTarget - currentVoltage) * kP;
        int finalVoltage = convertedTarget + error;
        motor.move_voltage(finalVoltage);
        return finalVoltage;
    };

    void setTargetSpeed(double pwr) {
        targetSpeed = TECHNICAL_FLYWHEEL_RPM * pwr;
        if (targetSpeed > 0) brake(false);
        voltageUpdate();
    };

    void brake(bool mode) {
        if (mode == true && abs(actualSpeed) < 30) motor.set_brake_mode(MOTOR_BRAKE_BRAKE);
        else motor.set_brake_mode(MOTOR_BRAKE_COAST);
    };

}

namespace endgame {

    ADIDigitalOut solenoid(SOLENOID_PORT, DEFAULT_STATE);

    int state = DEFAULT_STATE;

    void setState(int newState) {
        solenoid.set_value(newState);
        state = newState;
        driver::master.rumble(".");
    };

}