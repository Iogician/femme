#include "millie/robot.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"

using namespace pros;

void wait(int waitTime) {
    int t = 0;
    while (t < waitTime) {
        t += 2;
        flywheel::voltageUpdate();
        brainScreen::update();
        brainScreen::cd(2);
        delay(2);
    };
};

namespace driver {

    Controller master(E_CONTROLLER_MASTER);

    int macroCooldown = 0;
    int direction = 1;

    void changeDirection(int newDirection) {
        direction = newDirection;
    };

    void cd(int increment) { 
        macroCooldown += increment; 
    };

    void rm() {
        macroCooldown = 0;
    }

};

namespace programming {

    int routine = 1;

    void doNothing() {
        driver::master.rumble("-");
    };

    void spinOneRoller() {
        drivetrain::driveForTime(0, 50, 0, 375);
        intake::spinForTime(-1, 500);
    };

    void shootDiscs() {
        flywheel::setTargetSpeed(SHORT_RANGE_POWER);
        wait(3000);
        flywheel::setTargetSpeed(LONG_RANGE_POWER);
        wait(3000);
        flywheel::setTargetSpeed(1);
        wait(3000);
        intake::spinForTime(1, 2000);
        wait(2000);
        flywheel::setTargetSpeed(0);
    };

    void runAutonomous() {
        drivetrain::resetGyros();
        if (routine == 1) spinOneRoller();
        else if (routine == 2) shootDiscs();
        else doNothing();
    };

};

namespace brainScreen {

    int brainCD = 0;

    void leftButton() {
        programming::routine -= 1;
        if (programming::routine < 0) programming::routine = TOTAL_ROUTINES;
        driver::master.rumble(".");
    };

    void centerButton() {

    };

    void rightButton() {
        programming::routine += 1;
        if (programming::routine > TOTAL_ROUTINES) programming::routine = 0;
        driver::master.rumble(".");
    };

    void init() {
        lcd::initialize();
        lcd::set_background_color(52, 39, 89);
        lcd::set_text_color(255, 255, 255);
        lcd::register_btn0_cb(leftButton);
        lcd::register_btn1_cb(centerButton);
        lcd::register_btn2_cb(rightButton);
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
            lcd::set_text(6, "Hue: " + to_string(intake::optical.get_hue()));
        };
    };

};