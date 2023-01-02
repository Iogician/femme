#include "millie/robot.hpp"

using namespace pros;

namespace intake {

    Motor motor(INTAKE_PORT, INTAKE_GEARSET);
    Optical optical(OPTICAL_PORT);

    void spin(double pwr) {
        motor.move_voltage(MAXIMUM_VOLTAGE * pwr);
    };

    void opticalLED(int pwm) {

    };

    string getColor() {
        return "";
    };

}

namespace flywheel {

    Motor motor(FLYWHEEL_PORT, FLYWHEEL_GEARSET);

    int targetSpeed = 0;

    int voltageUpdate() {
        if (targetSpeed == 0)  {motor.move_voltage(0); return 0; }
        int currentVoltage = motor.get_actual_velocity() * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int convertedTarget = targetSpeed * (MAXIMUM_VOLTAGE/TECHNICAL_FLYWHEEL_RPM);
        int error = (convertedTarget - currentVoltage) * kP;
        int finalVoltage = convertedTarget + error;
        motor.move_voltage(finalVoltage);
        return finalVoltage;
    };

    void setTargetSpeed(double pwr) {
        targetSpeed = TECHNICAL_FLYWHEEL_RPM * pwr;
        voltageUpdate();
    };

}

namespace endgame {

    ADIDigitalOut solenoid(SOLENOID_PORT, DEFAULT_STATE);

    void setState(int newState) {
        solenoid.set_value(newState);
    };

}