#include <Arduino.h>
#include <main.h>

float powerConsumed = 0; //Watts
float intensityConsumed = 0; //mAh

//Passem la intensitat ja que no fa falta fer dos lectures de l'ADC
void updatePowerConsumed(float intensity) {
    static long timeReference = millis();
    float aux = intensity / (millis() - timeReference); //TODO: Update formula.

    intensityConsumed += aux / 1000;
    powerConsumed += aux * POWER_SUPPLY;
    timeReference = millis();
}

float getPowerConsumed() {return powerConsumed;}

float getIntensityConsumed() {return intensityConsumed;}
float getBatteryUsed() {return (intensityConsumed*100) / TOTAL_BATTERY;}

float getIntensityValue() {
    return analogRead(ACS711_AnalogPin) * 25 / 1024;
}