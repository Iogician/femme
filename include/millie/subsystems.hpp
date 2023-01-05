#include "main.h"
#include "pros/adi.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

using namespace std;
using namespace pros;

namespace intake {

    #define INTAKE_PORT -12
    #define INTAKE_GEARSET E_MOTOR_GEAR_200
    #define OPTICAL_PORT 20

    extern Motor motor;
    extern Optical optical;

    void opticalLED(int pwm);
    void spin(double pwr);
    void spinForTime(double pwr, int time);
    string getColor();

};

namespace flywheel {

    #define FLYWHEEL_PORT 8
    #define FLYWHEEL_GEARSET E_MOTOR_GEAR_600
    #define LONG_RANGE_POWER 0.6666667
    #define SHORT_RANGE_POWER 0.3333333
    #define MAXIMUM_VOLTAGE 12000
    #define TECHNICAL_FLYWHEEL_RPM 600

    extern Motor motor;

    extern int targetSpeed;
    extern double actualSpeed;

    int voltageUpdate();
    void setTargetSpeed(double pwr);
    void brake(bool mode);

};

namespace endgame {

    #define SOLENOID_PORT 8
    #define DEFAULT_STATE 0

    extern ADIDigitalOut solenoid;

    extern int state;

    void setState(int newState);

};