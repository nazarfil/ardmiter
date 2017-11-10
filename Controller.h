/* 
* Controller.h
*
* Created: 17/08/2017 13:57:34
* Author: sande
*/
#include "PS2X_lib.h"
#include <Arduino.h>

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


class Controller
{
//variables
public:
protected:
private:
PS2X ps2x; // create PS2 Controller Class
#define PS2_DAT        8  //14
#define PS2_CMD        9  //15
#define PS2_SEL        10  //16
#define PS2_CLK        7  //17
#define pressures   false
#define rumble      false
float ypra[4];
float ypra_Offset[4];
bool emergency_status;
bool start_stop_status;
int time_L1_pressed;
const float OFFSET_INCREMENT = 1;
const float MAX_PITCH_ROLL = 30;
const float MAX_YAW = 180;
const float MAX_ANALOG_STICK_VALUE=125;
const float MAX_OFFSET_YPR = 10;
const float MAX_OFFSET_ALT = 100;
int error = 0;
byte type = 0;
byte vibrate = 0;
bool running = false;
//functions
public:
	Controller();
	~Controller();
	void Init();
	void Get_Values(float *ypra_output, float *ypra_offset);
	bool Get_Emergency_Status();
	bool Get_Start_Stop_Status(int dt);
	bool Next_screen();
	bool Pressed();
	bool IsEnabled();
protected:
private:
	Controller( const Controller &c );
	Controller& operator=( const Controller &c );
	void Read_Values_FromController();

}; //Controller

#endif //__CONTROLLER_H__
