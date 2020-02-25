
#include <main.h>
#include <Arduino.h>
#include <SD.h>
#include <APRS.h>
#include <GPS.h>
#include <BME_280.h>
#include <MPU6050.h>
#include <Power.h>

uint32_t globalTime = 0;

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
  
  #ifndef CANview_MODE_ONLY

  PRINTLN("Starting BME");
  //Initialize the BME sensor.
  BME_init();

  PRINTLN("Starting GPS");
  
  //Start the GPS module.
  //GPS_begin();

  PRINTLN("Starting SD card");
  //Initialize the SD card.
  if (!SD.begin(BUILTIN_SDCARD)) {
    //Something went wrong. Blink led 8 times
    error(8);
  }
  
  PRINTLN("Starting APRS");
  //Initialize the APRS module.
  APRS_setup();
  
  #endif
  PRINTLN("Starting MPU");
  
  //Initialize the MPU-6050 sensor.
 // MPU_setup();
  
  globalTime = millis();
  
  #ifdef DEBUG
  Serial.println("Starting LOOP");
  #endif
}

void loop() {

  #ifdef CANview_MODE
  
  static unsigned long SEND_t = millis();
  if(millis() - SEND_t >= 200){
    MPU_sendData();
    SEND_t = millis();
  }
  
  #else

  //NORMAL MODE
  static uint32_t BME_t  = millis();
  static uint32_t APRS_t = millis();
  static uint32_t MPU_t  = millis();

  globalTime = millis();

  
  if(APRS_not_busy()){
  
    if(globalTime - BME_t >= BME_LOG_PERIOD)
    {
      BME_log(globalTime); 
      BME_t = millis();
    }
    
    if(globalTime - MPU_t >= MPU_LOG_PERIOD)
    {
      
      MPU_log(globalTime);
      
      #ifdef DEBUG
      //MPU_printYPR();
      #endif
      
      MPU_t = millis();
    }

    if(globalTime - APRS_t >= APRS_TX_PERIOD)
    {
      float lat,lon;
      GPS_getPosition(&lat,&lon);
      //Aquesta funció activa el busy. Per aixo esta al final.
      APRS_broadcastLocation(lat,lon," Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby Sayonara bby");
      APRS_t = millis();
    }
  }else{
    APRS_t = millis();
  }

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
