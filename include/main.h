//#define DEBUG

#define NORMAL_MODE
//#define CANview_MODE
//#define CANview_MODE_ONLY

#ifdef DEBUG
#define PRINTLN(x) Serial.println(F(x));
#define PRINT(x) Serial.print(x);
#else
#define PRINTLN(x) 
#define PRINT(x)
#endif

//Data logger system
//Periods expressed in ms
#define BME_LOG_PERIOD 2000
#define MPU_LOG_PERIOD 100
#define APRS_TX_PERIOD 2000

//APRS
//Set your callsign and SSID here. Common values for the SSID are
#define S_CALLSIGN      "EA3RKL"
#define S_CALLSIGN_ID   1   // 11 is usually for balloons
//Destination callsign: APRS (with SSID=0) is usually okay.
#define D_CALLSIGN      "APRS"
#define D_CALLSIGN_ID   0
//Symbol Table: '/' is primary table '\' is secondary table
#define SYMBOL_TABLE '/' 
//Primary Table Symbols: /O=balloon, /-=House, /v=Blue Van, />=Red Car
#define SYMBOL_CHAR 'v'

//MPU-6050
#define INTERRUPT_PIN 39  
#define LED_PIN LED_BUILTIN

//GPS
#define GPS_Baud 9600
#define GPS_Serial Serial1

//BME
#define SEALEVELPRESSURE_HPA (984.75)

//Power
#define ACS711_AnalogPin A3
#define POWER_SUPPLY 5.00  //V
#define TOTAL_BATTERY 1000 //mAh


void error(int num);