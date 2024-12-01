#include <Wire.h>
#include "Adafruit_TCS34725.h"
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
#define cambien 2
long time1,time2,time3;
int mDO,mXL,mXD;
int DO,XL,XD;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include <Servo.h>

Servo M1;
Servo M2;
Servo M3;
void setup() {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  M1.attach(4);
  M2.attach(5);
  M3.attach(6);
  //Serial.println("Color View Test!");
  pinMode(cambien, INPUT_PULLUP);
  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  M1.write(0);
  M2.write(0);
  M3.write(0);
  hienthi();
}
void hienthi(){
  lcd.setCursor(0, 0);
  lcd.print("DO");
  lcd.setCursor(7, 0);
  lcd.print("XL");
  lcd.setCursor(14, 0);
  lcd.print("XD");
  lcd.setCursor(0, 1);
  lcd.print(mDO);
  lcd.setCursor(7, 7);
  lcd.print(mXL);
  lcd.setCursor(14, 14);
  lcd.print(mXD);
}
void loop() {
  
  float red, green, blue;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.println("");
  DO = int(red);
  XL = int(green);
  XD = int(blue);

  

 if(DO >= 100 && XL < 100 && XD < 100){
  if(millis() - time1 < 500){
    mDO = mDO + 1;
    hienthi();
    M1.write(90);
    delay(500);
    M1.write(0);
  }
 }
 else{
    time1 = millis();
  }

 if(DO < 100 && XL >= 100 && XD < 100){
  if(millis() - time2 < 500){
    mXL = mXL + 1;
    hienthi();
    M2.write(90);
    delay(500);
    M2.write(0);
  }
 }
 else{
    time2 = millis();
  }

 if(DO < 100  && XL < 100 && XD >= 100){
  if(millis() - time3 < 500){
    mXD = mXD + 1;
    hienthi();
    M3.write(90);
    delay(500);
    M3.write(0);
  }
 }
 else{
    time3 = millis();
  }
 
}
