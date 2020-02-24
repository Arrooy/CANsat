#include <main.h>
#include <Arduino.h>
#include <SD.h>
#include <APRS.h>
#include <GPS.h>
#include <BME_280.h>
#include <MPU6050.h>
#include <Power.h>

unsigned long long globalTime = 0;

//TODO: POWER module.

void setup() {

  //Init teensy builtin led and turn it off
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BUILTIN, LOW);
  

  #ifdef CANview_MODE
  Serial.begin(9600);
  while (!Serial);
  #endif

  #ifdef DEBUG 
    #ifndef CANCANview_MODE
      Serial.begin(115200);
      while (!Serial);
    #endif
  #endif
  
  #ifdef MODE_SIMPLE
  //Serial.begin(115200);
  
  APRS_setup(3000);
  #else
#ifndef CANview_MODE_ONLY
  PRINTLN("Starting GPS");
  
  //Start the GPS module.
  GPS_begin();

  PRINTLN("Starting SD card");
  //Initialize the SD card.
  if (!SD.begin(BUILTIN_SDCARD)) {
    //Something went wrong. Blink led 8 times
    error(8);
  }
  
  PRINTLN("Starting APRS");
  //Initialize the APRS module. Set tx period to 3s.
  APRS_setup(2000);

  PRINTLN("Starting BME");
  //Initialize the BME sensor.
  BME_init();
  
  #endif
  PRINTLN("Starting MPU");
  
  //Initialize the MPU-6050 sensor.
 // MPU_setup();
  
  globalTime = millis();
  
  #ifdef DEBUG
  Serial.println("Starting LOOP");
  #endif
  
  #endif
}

void loop() {
  
  #ifdef MODE_SIMPLE
  APRS_broadcastLocation(0.0f,0.0f, "Hi from Arroyos' house :)");
  delay(200);
  #else
  #ifdef CANview_MODE
  static unsigned long SEND_t = millis();
  if(millis() - SEND_t >= 200){
    MPU_sendData();
    SEND_t = millis();
  }
  #else
/*
  static unsigned long BME_t = millis();
  static unsigned long MPU_t = millis();
  
  globalTime = millis();

  if(millis() - BME_t >= BME_LOG_PERIOD){
    BME_log(globalTime);  
    BME_t = millis();
  }
  
  if(millis() - MPU_t >= MPU_LOG_PERIOD){
    MPU_log(globalTime);
    MPU_t = millis();
  }*/
  #endif
  
  
  #ifdef DEBUG
  MPU_printYPR();
  #endif
  #endif

}

void error(int num) {
  noInterrupts();
  while (1) {
    for (int i = 0; i < num; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    delay(1000);
  }
}
