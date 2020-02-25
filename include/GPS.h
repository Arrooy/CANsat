#ifndef _GPS_CANSAT_H_
#define _GPS_CANSAT_H_
void GPS_begin();
void GPS_read();
void GPS_getPosition(float * lat,float * lon);
void GPS_print();
void GPS_log();
#endif