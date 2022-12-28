#include "main.h"
#include "millie/robot.hpp"

using namespace pros;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		lcd::set_text(2, "I was pressed!");
	} else {
		lcd::clear_line(2);
	}
}

void initialize() {
	lcd::initialize();
	lcd::set_text(1, "Hello PROS User!");

	lcd::register_btn1_cb(on_center_button);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	Controller master(pros::E_CONTROLLER_MASTER);
	drivetrain::ALL.set_brake_modes(E_MOTOR_BRAKE_COAST);

	while (true) {

		drivetrain::drive(master.get_analog(ANALOG_LEFT_X), master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X) * 0.9);		
		
		delay(20);
	}
}
