#include "millie/robot.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"

using namespace pros;

namespace driver {

    Controller master(E_CONTROLLER_MASTER);

    int macroCooldown = 0;

    void cd(int increment) { 
        macroCooldown += increment; 
    };

    void rm() {
        macroCooldown = 0;
    }

};

namespace brainScreen {

    int brainCD = 0;

    void init() {
        lcd::initialize();
        lcd::set_background_color(52, 39, 89);
        lcd::set_text_color(255, 255, 255);
    };

    void rb() {
        brainCD = 0;
    }

    void cd(int increment) {
        brainCD += increment;
    }

    void update() {
        if (brainCD >= BRAIN_UPDATE_CD + 1) {
            rb();
            lcd::set_text(1, "Heading: " + to_string(drivetrain::heading()));
            lcd::set_text(2, "FlyComp: " + to_string(flywheel::voltageUpdate()));
            lcd::set_text(3, "FlyTarget: " + to_string(flywheel::targetSpeed));
            lcd::set_text(4, "Encoder: " + to_string(drivetrain::getMotorGroupPosition(drivetrain::ALL.get_positions(), 6)));
            lcd::set_text(5, "Distance: " + to_string(distance::read()));
        };
    };

};