#include <TinyGPS.h>
#include <main.h>
#include <GPS.h>
#include <APRS.h>
#include <SD.h>

// Create an IntervalTimer object 
IntervalTimer PeriodicCaller;
TinyGPS gps;

void magic();
void GPS_printStats();

//Note: The GPS takes 3.50s to start blinking the blue led
//Note2: The GPS takes 4.30s to load fully.
void GPS_begin()
{
  bool encode_done = false;
  GPS_Serial.begin(GPS_Baud);
  while(!encode_done){
    if(GPS_Serial.available() > 0){
      if(gps.encode(GPS_Serial.read())){
        #ifdef DEBUG
          GPS_printStats();
        #endif
        
        encode_done = (gps.satellites() != gps.GPS_INVALID_SATELLITES);
      }
    }
  }

  PeriodicCaller.priority(200);
  PeriodicCaller.begin(GPS_read, 150000);
  //With 250000us, the buffer fills up to 240 Bytes.
  //With 200000us, the buffer fills up to 192 Bytes.
  //With 150000us, the buffer fills up to 144 Bytes.
  //Some margin is aded in case an interruption happens while on the LOW priority ISR.
}

void GPS_read()
{
  float flat, flon;
  unsigned long fix_age; // returns +- latitude/longitude in degrees
 
  bool encodedDone = false;
  
  //We dont want to call again untill the function is ended.
  PeriodicCaller.end();
  
  PRINT(GPS_Serial.available());
  PRINTLN(" Bytes ready to read.");
 
  while(GPS_Serial.available() > 0){
    int aux = GPS_Serial.read();
    if(gps.encode(aux)){
      #ifdef DEBUG
      GPS_printStats();
      #endif
      encodedDone = true;
    }
  } 
  
  //Es fa el comput a fora el bucle, per buidar completament el buffer del rx.
  if(encodedDone && APRS_not_busy()){
    GPS_log();
  }

  //ReEnable future readings
  PeriodicCaller.begin(GPS_read, 150000);
}

void GPS_getPosition(float * lat,float * lon)
{
  unsigned long fix_age;
  gps.f_get_position(lat, lon, &fix_age);
}

void GPS_printStats(){
  unsigned long chars;
  unsigned short sentences,failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  Serial.print("Satelites:");
  Serial.print(gps.satellites());
  Serial.print(" Chars:");
  Serial.print(chars);
  Serial.print(" Sentences:");
  Serial.print(sentences);
  Serial.print(" Checksums:");
  Serial.println(failed_checksum);
}

void GPS_log()
{
  float flat, flon;
  unsigned long fix_age; // returns +- latitude/longitude in degrees 
  unsigned long date, time;
  
  //Nota: No he fet gps.crack_datetime per reduir cost computacional
  gps.get_datetime(&date, &time, &fix_age);
  
  gps.f_get_position(&flat, &flon, &fix_age);
  
  File datalog = SD.open("GPS.txt", FILE_WRITE);

  String dataString = String(time)              + ":" + // HHMMSSCC nidea que es cc, millor mirar TinyGPS. 
                      String(flat)              + ":" + // Latitude
                      String(flon)              + ":" + // Longitude
                      String(gps.f_altitude())  + ":" + // Meters
                      String(gps.course())      + ":" + // Degrees
                      String(gps.f_speed_mps()) + ":" + // m/s
                      String(gps.satellites());         // Number of satellites.       
                      
  
  if(datalog){
    datalog.println(dataString);
    datalog.close(); 
  }
}