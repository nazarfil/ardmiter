#include "Display.h"

Display::Display(){
  lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
};

Display::~Display(){

};

void Display::InitDispaly(){
    lcd->begin(columns, rows);
};

void Display::UpdateScreen(){
      //Load Screen
      LoadScreen();

        //Update values
    for (int row; row < 4; row++) {
        lcd->setCursor(2, row);
        PrintChar(offset_ypra[row]);
        lcd->setCursor(9, row);
        PrintChar(reference_ypra[row]);
        lcd->setCursor(16, row);
        PrintChar(sensor_ypra[row]);
    }
};

void Display::LoadScreen(){

    //Create Colmuns
  for (int col = 6; col < 14; col = col + 7) {
    for (int row = 0; row < 5; row++) {
      lcd->setCursor(col, row);
      lcd->print("|");
    }
  }

  //Create Yaw headers
  for (int col = 1; col < 16; col = col + 7) {
    lcd->setCursor(col, 0);
    lcd->print("Y");
  }

  //Create Pitch headers
  for (int col = 1; col < 16; col = col + 7) {
    lcd->setCursor(col, 1);
    lcd->print("P");
  }

  //Create Roll headers
  for (int col = 1; col < 16; col = col + 7) {
    lcd->setCursor(col, 2);
    lcd->print("R");
  }

  //Create Altitude headers
  for (int col = 1; col < 16; col = col + 7) {
    lcd->setCursor(col, 3);
    lcd->print("A");
  }

  //Create offset headers
  for (int row = 0; row < 4; row++) {
    lcd->setCursor(0, row);
    lcd->print("o");
  }

  //Create reference headers
  for (int row = 0; row < 4; row++) {
    lcd->setCursor(7, row);
    lcd->print("r");
  }

  //Create Sensor headers
  for (int row = 0; row < 4; row++) {
    lcd->setCursor(14, row);
    lcd->print("s");
  }
};

void Display::PrintChar( int numb){
    String out;
    if (numb > 0)
      out = "+" + String(numb);
    else
      out =  String(numb);
  
    out = out.substring(0,4);
    lcd->print(out);
};

void Display::SetOffsetYPRA(int ypra[]){
   for(int i =0; i<4; i++){
       offset_ypra[i]= ypra[i];
   }
};

void Display::SetSensorYPRA(int ypra[]){
    for(int i =0; i<4; i++){
        sensor_ypra[i] = ypra[i];
    }
};

void Display::SetReferenceYPRA(int ypra[]){
    for(int i=0; i<4; i++){
        reference_ypra[i] = ypra[i];
    }
};
