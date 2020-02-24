#include <main.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SD.h>

Adafruit_BME280 bme;

void BME_init()
{

  unsigned status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin();
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");

    while (true) error(3);
  }

  //Config #1. Menys precisio, menys consum.
  //Amb la seguent configuracio, sobte una precisio de :
  //Pressio = 1.0 Pa en 25ºC
  //Temperatura = 0.003ºC
  //Humitat = 0.04%
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X4, // temperature
                  Adafruit_BME280::SAMPLING_X8, // pressure
                  Adafruit_BME280::SAMPLING_X4, // humidity
                  Adafruit_BME280::FILTER_OFF);
  
  //COnfig 2. Més precisio, més consum.
//  bme.setSampling(Adafruit_BME280::MODE_FORCED,
//                  Adafruit_BME280::SAMPLING_X16, // temperature
//                  Adafruit_BME280::SAMPLING_X16, // pressure
//                  Adafruit_BME280::SAMPLING_X16, // humidity
//                  Adafruit_BME280::FILTER_OFF);
//  
}

void BME_measure()
{
  bme.takeForcedMeasurement();
}

//Retorna C
float BME_getTemperature()
{
  return bme.readTemperature();
}

//Retorna hPa.
unsigned long BME_getPressure()
{
  return bme.readPressure() / 100.0F;
}

//0 - 100 % relative humidity.
char BME_getHumidity()
{
  return bme.readHumidity();
}

//Altitude referenced to sea level.
float BME_getAltitude()
{
  return bme.readAltitude(SEALEVELPRESSURE_HPA);
}

void BME_print()
{

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void BME_log(unsigned long globalTime)
{
  bme.takeForcedMeasurement();
  File datalog = SD.open("BME.txt", FILE_WRITE);
  
  String dataString = String(globalTime) + ":"+ //ms
                      String(bme.readTemperature()) + ":"+ //Celsius
                      String(bme.readPressure() / 100.0F) + ":" + //hPa
                      String(bme.readHumidity()); //0 - 100 % relative humidity.
  
  if(datalog){
    datalog.println(dataString);
    datalog.close(); 
  }
}