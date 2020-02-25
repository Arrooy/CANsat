#ifndef _BME_280_CANSAT_H_
#define _BME_280_CANSAT_H_
void BME_init();

void BME_measure();
float BME_getTemperature();
unsigned long BME_getPressure();
char BME_getHumidity();
float BME_getAltitude();
void BME_print();
void BME_log(uint32_t globalTime);
#endif