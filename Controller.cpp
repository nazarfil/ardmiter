/*
* Controller.cpp
*
* Created: 17/08/2017 13:57:33
* Author: sande
*/


#include "Controller.h"
#include "PS2X_lib.h"
#include <Arduino.h>

// default constructor
Controller::Controller()
{

}

// default destructor
Controller::~Controller()
{
} //~Controller

void Controller::Init(){

	delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it

	//CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

	//setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
	error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
}

void Controller::Get_Values(float *ypra_output, float *ypra_offset){

	Read_Values_FromController();

	//refrence values
	ypra_output[0] = this->ypra[0];
	ypra_output[1] = this->ypra[1];
	ypra_output[2] = this->ypra[2];
	ypra_output[3] = this->ypra[3];

	//offset values
	ypra_offset[0] = this->ypra_Offset[0];
	ypra_offset[1] = this->ypra_Offset[1];
	ypra_offset[2] = this->ypra_Offset[2];
	ypra_offset[3] = this->ypra_Offset[3];

}

bool Controller:: Next_screen(){

	if(ps2x.ButtonPressed(PSB_R1))
	return true;
	return false;

}

bool Controller::Get_Emergency_Status(){

	if (ps2x.ButtonPressed(PSB_R1))
	return true;
	else
	return false;

}

bool Controller::Get_Start_Stop_Status(int dt){

	if(ps2x.ButtonPressed(PSB_L1)){

		time_L1_pressed += dt;

		if(time_L1_pressed > 2000) {
			start_stop_status = !start_stop_status;
			time_L1_pressed = 0;
		}
	} else
	time_L1_pressed = 0;
	
	return start_stop_status;

}

void Controller::Read_Values_FromController(){

	ps2x.read_gamepad(false, vibrate);

	//Read the stick values
	float pitch = ps2x.Analog(PSS_LX)-125;
	float roll = ps2x.Analog(PSS_LY) -125;
	float yaw = ps2x.Analog(PSS_RX)  -125;
	float alt = ps2x.Analog(PSS_RY)  -125;

	//Convert these values to the in range values
	ypra[1] = map(pitch,-MAX_ANALOG_STICK_VALUE,MAX_ANALOG_STICK_VALUE,-MAX_PITCH_ROLL,MAX_PITCH_ROLL) *-1;
	ypra[2] = map(roll,-MAX_ANALOG_STICK_VALUE,MAX_ANALOG_STICK_VALUE,-MAX_PITCH_ROLL,MAX_PITCH_ROLL) *-1;
	ypra[0] = map(yaw,-MAX_ANALOG_STICK_VALUE,MAX_ANALOG_STICK_VALUE,-MAX_YAW,MAX_YAW) *-1;
	ypra[3] = alt *-1;


	//calculate the offsets

	//roll
	if(ps2x.ButtonPressed(PSB_PAD_UP))
	ypra_Offset[2] = ypra_Offset[2] > MAX_OFFSET_YPR ? MAX_OFFSET_YPR : ypra_Offset[2] + OFFSET_INCREMENT;
	if(ps2x.ButtonPressed(PSB_PAD_DOWN))
	ypra_Offset[2] = ypra_Offset[2] < -MAX_OFFSET_YPR ? -MAX_OFFSET_YPR : ypra_Offset[2] - OFFSET_INCREMENT;
	//pitch
	if(ps2x.ButtonPressed(PSB_PAD_LEFT))
	ypra_Offset[1] = ypra_Offset[1] > MAX_OFFSET_YPR ? MAX_OFFSET_YPR : ypra_Offset[1] + OFFSET_INCREMENT;
	if(ps2x.ButtonPressed(PSB_PAD_RIGHT))
	ypra_Offset[1] = ypra_Offset[1] < -MAX_OFFSET_YPR ? -MAX_OFFSET_YPR : ypra_Offset[1] - OFFSET_INCREMENT;
	//yaw
	if(ps2x.ButtonPressed(PSB_SQUARE))
	ypra_Offset[0] = ypra_Offset[0] > MAX_OFFSET_YPR ? MAX_OFFSET_YPR : ypra_Offset[0] + OFFSET_INCREMENT;
	if(ps2x.ButtonPressed(PSB_CIRCLE))
	ypra_Offset[0] = ypra_Offset[0] < -MAX_OFFSET_YPR ? -MAX_OFFSET_YPR : ypra_Offset[0] - OFFSET_INCREMENT;
	//alt
	if(ps2x.ButtonPressed(PSB_TRIANGLE))
	ypra_Offset[3] = ypra_Offset[3] > MAX_OFFSET_ALT ? MAX_OFFSET_ALT : ypra_Offset[3] + OFFSET_INCREMENT*2;
	if(ps2x.ButtonPressed(PSB_CROSS))
	ypra_Offset[3] = ypra_Offset[3] < -MAX_OFFSET_ALT ? -MAX_OFFSET_ALT : ypra_Offset[3] - OFFSET_INCREMENT*2;

	//add offsets
	ypra[0] += ypra_Offset[0];
	ypra[1] += ypra_Offset[1];
	ypra[2] += ypra_Offset[2];
	ypra[3] += ypra_Offset[3];

	//Check if controller is enabled
	if(ps2x.ButtonPressed(PSB_START))
	running = !running;

}

bool Controller::IsEnabled(){
	return running;
}

bool Controller::Pressed(){
	bool b_t = ps2x.ButtonPressed(PSB_TRIANGLE);
	bool b_x = ps2x.ButtonPressed(PSB_CROSS);
	bool b_o = ps2x.ButtonPressed(PSB_CIRCLE);
	bool b_s = ps2x.ButtonPressed(PSB_SQUARE);
	if( b_t || b_x || b_o || b_s)
		return true;
	else
		return false;
}