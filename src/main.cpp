#include "main.h"
#include "millie/robot.hpp"

using namespace pros;
using namespace driver;

void initialize() {
	brainScreen::init();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	programming::runAutonomous();
};

void opcontrol() {

	drivetrain::ALL.set_brake_modes(E_MOTOR_BRAKE_COAST);
	flywheel::setTargetSpeed(0);

	while (true) {

		drivetrain::drive(master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X) * 0.9);		

		if (master.get_digital(DIGITAL_R1)) intake::spin(1);
		else if (master.get_digital(DIGITAL_R2)) intake::spin(-1);
		else intake::spin(0);

		if (master.get_digital(DIGITAL_X)) endgame::setState(1);

		if (macroCooldown >= MACRO_COOLDOWN + 1) {
			if (master.get_digital_new_press(DIGITAL_LEFT)) { distance::rotateTo(90); rm();}
			else if (master.get_digital_new_press(DIGITAL_RIGHT)) { distance::rotateTo(-90); rm();}
			else if (master.get_digital_new_press(DIGITAL_UP)) { distance::rotateTo(0); rm();};
			if (master.get_digital_new_press(DIGITAL_L1)) {
				if (flywheel::targetSpeed <= 0) flywheel::setTargetSpeed(SHORT_RANGE_POWER); 
				else flywheel::setTargetSpeed(0);
				rm();
			} 
			else if (master.get_digital_new_press(DIGITAL_L2)) {
				if (flywheel::targetSpeed < LONG_RANGE_POWER) flywheel::setTargetSpeed(LONG_RANGE_POWER); 
				else flywheel::setTargetSpeed(0);
				rm();
			};
			if (master.get_digital_new_press(DIGITAL_X)) changeDirection(direction * -1);
			if (master.get_digital_new_press(DIGITAL_Y)) endgame::setState(1);
		};

		cd(20);
		wait(20);
	};
};
