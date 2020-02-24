#ifndef _APRS_CANSAT_H_
#define _APRS_CANSAT_H_

#include <Arduino.h>
#include <main.h>
#include "aprs.h"


void APRS_setup(int tx_periode);
void APRS_broadcastLocation(double lati,double longui, const char *comment);

#endif
