#include "Transmitter.h"
#include "Controller.h"
#include "Display.h"
// Defining up a wireless transmitter RC
Transmitter sender = Transmitter();
// Defining up a PS2 controller
Controller ctrl;
// Defining up an LCD screen 
Display screen;

//Test values
int offset[4] = {10, 20, 30, 40};
int ypra[4] = {100, 110, 120, 130};
int sensors[4] = { 1, 2, 3, 4 };

void setup() {
    Serial.begin(9600); 

    screen.InitDispaly();
}

void loop() {
    delay(1000);

    // Get values from  the PS2 controller
    //ctrl.Get_Values(ypra, offset);
    
    // Update values to show on the LCD screen
    screen.SetOffsetYPRA( offset);
    screen.SetSensorYPRA(  ypra);
    screen.SetReferenceYPRA(  sensors);
    screen.UpdateScreen();

    // Send values over the radio
    //sender.testParser();
    unsigned short int values[4];
    for(int i = 0; i<4; i++){
        values[i] = sensors[i];
    }
    sender.getSensorValues(values);
    sender.sendData();
}
