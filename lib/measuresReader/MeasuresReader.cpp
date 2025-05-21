/*
    MeasuresReader.cpp - Library for get measures from composter sensors
    Created by Ignacio Diestro Gil - 2025
*/

#include "MeasuresReader.h"

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>
#include <Wire.h>
#include "M5UnitENV.h"



//Enviv Unit
SHT4X sht4;
BMP280 bmp;

MeasuresReader::MeasuresReader(){
}

void MeasuresReader::initSensors(){
    //Init Wire
    Wire.begin(32, 33);
    //ENVIV UNIT
    //SHT40
        if (!sht4.begin(&Wire, SHT40_I2C_ADDR_44, 32, 33, 400000U)) {
        Serial.println("Couldn't find SHT4x");
        while (1) delay(1);
    }

    // You can have 3 different precisions, higher precision takes longer
    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    sht4.setHeater(SHT4X_NO_HEATER);

    if (!bmp.begin(&Wire, BMP280_I2C_ADDR, 32, 33, 400000U)) {
        Serial.println("Couldn't find BMP280");
        while (1) delay(1);
    }
    /* Default settings from datasheet. */
    bmp.setSampling(BMP280::MODE_NORMAL,     /* Operating Mode. */
                    BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    BMP280::FILTER_X16,      /* Filtering. */
                    BMP280::STANDBY_MS_500); /* Standby time. */

}

// Función para obtener la temperatura ambiental simulada
float MeasuresReader::getEnvironmentTemperature() {
    sht4.update();
    return sht4.cTemp;
}

// Función para obtener la humedad ambiental simulada
float MeasuresReader::getEnvironmentHumidity() {
    sht4.update();
    return sht4.humidity;
}

// Función para obtener el nivel de oxígeno en el gas ambiental simulado
float MeasuresReader::getEnvironmentGasO2() {
    return 19 + rand() % 2;  // Oxígeno entre 19% y 20%
}

// Función para obtener el nivel de dióxido de carbono en el gas ambiental simulado
float MeasuresReader::getEnvironmentGasCO2() {
    return 0.04 + rand() % 3 * 0.01;  // CO2 entre 0.04% y 0.1%
}

// Función para obtener la temperatura de la biomasa simulada
float MeasuresReader::getBiomassTemperature() {
    return 30 + rand() % 11;  // Temperatura de biomasa entre 30 y 40°C
}

// Función para obtener el peso de la biomasa simulada
float MeasuresReader::getBiomassWeight() {
    return 100 + rand() % 901;  // Peso entre 100g y 1000g
}

// Función para obtener la cantidad de fluido de la biomasa simulada
float MeasuresReader::getBiomassFluidAmount() {
    return 10 + rand() % 91;  // Fluido entre 10ml y 100ml
}

// Función para obtener el pH de la biomasa simulada
float MeasuresReader::getBiomassPh() {
    return 6 + rand() % 5;  // pH entre 6 y 10
}
