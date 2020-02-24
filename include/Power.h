#ifndef _POWER_CANSAT_H_
#define _POWER_CANSAT_H_

//Actualitza els valors de potecia consumida actual i intensitat total fins al moment
void updatePowerConsumed(float intensity);

//Retorna la quantitat de Watts consumits
float getPowerConsumed();

//Retorna la quantitat de mAh consumits
float getIntensityConsumed();

//Retorna la bateria que ha gastat el mòdul des del inici del funcionament
float getBatteryUsed();

//Retorna el valor de la intensitat actual llegit pel sensor
float getIntensityValue();

#endif
