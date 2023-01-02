#include "main.h"
#include "pros/adi.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

using namespace std;
using namespace pros;

namespace intake {

    #define INTAKE_PORT 12
    #define INTAKE_GEARSET E_MOTOR_GEAR_200
    #define OPTICAL_PORT 20

    extern Motor motor;
    extern Optical optical;

    void spin(double pwr);
    void opticalLED(int pwm);
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

    int voltageUpdate();
    void setTargetSpeed(double pwr);

};

namespace endgame {

    #define SOLENOID_PORT 3
    #define DEFAULT_STATE 0

    extern ADIDigitalOut solenoid;

    void setState(int newState);

};

namespace driver {

    #define MACRO_COOLDOWN 375;

    extern Controller master;

    extern int macroCooldown;

    void cd(int increment);
    void rm();

};

namespace brainScreen {

    #define BRAIN_UPDATE_CD 50;

    extern int brainCD;

   void init();
   void rb();
   void cd(int increment);
   void update();

}