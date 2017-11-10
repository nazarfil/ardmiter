#include "Transmitter.h"
#include "stdio.h"
#include "stdlib.h"
#include "Arduino.h"

#define CYCLUS_STOP 0x0c
const unsigned char msg_length = 12;

using namespace std;
Transmitter::Transmitter()
{
    short int sensor[4] = {0x0001, 0x0101, 0x0010, 0x0001};
    getSensorValues(sensor);
};

Transmitter::~Transmitter(){

};

unsigned char Transmitter::checkSum( char *x, int size )
{
  unsigned int sum=0;
  char curr_value;
  for( int i = 0; i< size; i++){
    curr_value = x[i];
    while( curr_value > 0x0 ){
      sum +=  (curr_value & 0x01);
      curr_value >>=  1;
    }
  }
  return sum;
}

void Transmitter::getSensorValues(short int* sensor){
    yaw = (short int)sensor[0];
    pitch = (short int)sensor[1];
    roll = (short int)sensor[2];
    altitude = (short int)sensor[3];
};

void Transmitter::parseBuffer(){

    /*
        heartbeat_bit -> :
        000ConrollerMethodBit GeneralErrBIT_EMERGeNCYBIT_BATTERYBiT_HEARTBIT ->
                            -> 0x07 -> 
    */
    //printf("end__: 0x%02x \n", 'e');
   short int mask = 0xff;
   // 0_   = magic nubmer
   msg_buffer[0] = 0x01;  
   // 1_2_ = yaw parsed from int 
   msg_buffer[2] = yaw & mask;
   msg_buffer[1] = (yaw >> 8) & mask; 

   // 3_4_ = pitch parsed from int
   msg_buffer[4] = pitch & mask;
   msg_buffer[3] = (pitch >> 8) & mask;

   // 5_6_ = roll parsed from int
   msg_buffer[6] = roll & mask; 
   msg_buffer[5] = (roll >> 8) & mask;

   // 7_8_ = altitude parsed from int
   msg_buffer[8] = altitude & mask;
   msg_buffer[7] = (altitude >> 8) & mask;

   // 9_ = EndOfBuffer;
   unsigned char check_sum = checkSum( msg_buffer, 9);  
   msg_buffer[9] = check_sum;   
   //Error code : 0xff -> 0x0001 (Methods) 0(GenError)0(Emergency)0(BatteryErr)0(Heartbit)
   unsigned char heartbeat_bit  = 0x01; // hex : 0000 0001
   unsigned char battery_bit= 0x02; // hex : 0000 0010
   unsigned char emergency_bit = 0x04 ;// hex= 0000 0100
   unsigned char general_err_bit = 0x08; // hex -=  0000 1000
   unsigned char error_msg = 0x0; // error msg buffer 0000 0000
   error_msg = error_msg || general_err_bit || emergency_bit || battery_bit || heartbeat_bit ; //hex -> 0000 1111

   unsigned char control_msg = 0x00 || CYCLUS_STOP;
   msg_buffer[10] = control_msg || error_msg;
   msg_buffer[11] = 'e';

   //?? To ADD:
   /*Test the code 
    -> I have to download serial communication program -> Data Visualizer;
    */
 

};

void Transmitter::printBuffer( char* buffer, int size){    

    short int temp;
    for(int i = 0; i<size; i++){
       // temp = 0x0000;
        //temp = (temp | (buffer[2*i+1] << 8) | (buffer[2*i+2])) ;
        Serial.println(buffer[i], HEX);

     }
};

void Transmitter::testParser(){
    //parseBuffer();
    printBuffer( msg_buffer, msg_length);
    
};

void Transmitter::sendData(){
    parseBuffer();
    testParser(); 
};
