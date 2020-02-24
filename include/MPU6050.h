#ifndef _MPU6050_CANSAT_H_
#define _MPU6050_CANSAT_H_
void MPU_setup();
void MPU_printYPR();
void MPU_sendData();
void MPU_log(unsigned long globalTime);
#endif