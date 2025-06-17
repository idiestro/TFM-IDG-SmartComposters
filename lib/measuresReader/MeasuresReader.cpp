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
#include "ScioSense_ENS160.h"
#include <OneWire.h>
#include <DallasTemperature.h>


//Temporization data
unsigned long lastEns160RequestTime = 0;
//Enviv Unit
SHT4X sht4;
BMP280 bmp;
//ENS160
ScioSense_ENS160 ens160(ENS160_I2CADDR_1);
float lastCo2Value = -1.0;
bool ens160MeasurementRequested = false;
//DE18B20
#define ONE_WIRE_BUS 0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//PH sensor
#define PH_PIN 35

MeasuresReader::MeasuresReader(){
}

void MeasuresReader::initSensors(){
    //Init I2C wire
    initI2CWire();
    //Init ENV IV sensor
    initEnvIv();
    //Init ENS160
    initEns160();
    //Init DS18B20
    initDS18B20();

}

// Get environment temperature from SHT4X sensor
float MeasuresReader::getEnvironmentTemperature() {
    sht4.update();
    return sht4.cTemp;
}

// Get environment humidity from SHT4X sensor
float MeasuresReader::getEnvironmentHumidity() {
    sht4.update();
    return sht4.humidity;
}

// Get environment gas O2 level
float MeasuresReader::getEnvironmentGasO2() {
    return -1;
}

// Get environment gas CO2 level using ENS160
float MeasuresReader::getEnvironmentGasCO2() {
    //Get measurement delay time
    const unsigned long MEASUREMENT_DELAY = 200;

    if (!ens160MeasurementRequested) {
        // New measurement requested
        ens160.measure();
        lastEns160RequestTime = millis();
        ens160MeasurementRequested = true;
    } else if (millis() - lastEns160RequestTime >= MEASUREMENT_DELAY) {
        if (ens160.available()) {
            lastCo2Value = ens160.geteCO2();
            //Set for new medition
            ens160MeasurementRequested = false; 
        }
    }
    return lastCo2Value; 
}

// Get biomass temperature from DS18B20 sensor
float MeasuresReader::getBiomassTemperature() {
    sensors.requestTemperatures();
    return sensors.getTempCByIndex(0);
}

// Get biomass weight
float MeasuresReader::getBiomassWeight() {
    return -1;  
}

// Get biomass fluid amount
float MeasuresReader::getBiomassFluidAmount() {
    return -1;  
}

// Get biomass pH level from analog pin
float MeasuresReader::getBiomassPh() {
    int analogValue = analogRead(PH_PIN);
    float voltage = analogValue * (5.0 / 4095.0); // 5 for 5V reference, could be 3.3 for 3.3V reference
    return voltage;
}

//Init I2C wire
void MeasuresReader::initI2CWire(){
    Wire.begin(32, 33);
}

//Init ENVIV UNIT with I2C
void MeasuresReader::initEnvIv(){
    //SHT40
        if (!sht4.begin(&Wire, SHT40_I2C_ADDR_44, 32, 33, 400000U)) {
        Serial.println("SHT4x no encontrado");
        while (1) delay(1);
    }

    // Precision and heater settings
    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    sht4.setHeater(SHT4X_NO_HEATER);

    if (!bmp.begin(&Wire, BMP280_I2C_ADDR, 32, 33, 400000U)) {
        Serial.println("BMP28 no encontrado0");
        while (1) delay(1);
    }
    // Default settings from datasheet
    bmp.setSampling(BMP280::MODE_NORMAL,     // Operating Mode
                    BMP280::SAMPLING_X2,     // Temp. oversampling 
                    BMP280::SAMPLING_X16,    // Pressure oversampling 
                    BMP280::FILTER_X16,      // Filtering 
                    BMP280::STANDBY_MS_500); // Standby time
}

//Init ENS160+AHT21
void MeasuresReader::initEns160(){
    // ENS160
    if (!ens160.begin()) {
        Serial.println("ENS160 no encontrado");
        while (1);
    }
    //Set in Standard mode
    ens160.setMode(ENS160_OPMODE_STD);
    //Active automatic meditions
    //ens160.measure(true); //Not needed, batery save

}

//Init DS18B20
void MeasuresReader::initDS18B20(){
    // Initialize the OneWire bus
    sensors.begin();
    sensors.setResolution(12);  // Set resolution to 12 bits
}