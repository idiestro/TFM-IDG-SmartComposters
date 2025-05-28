/*
    SimularedMeasures.h - Library for simulate measures from composter
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef MEASURES_READER_H
#define MEASURES_READER_H

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

class MeasuresReader {
    public:
        MeasuresReader();
        void initSensors();
        float getEnvironmentTemperature();
        float getEnvironmentHumidity();
        float getEnvironmentGasO2();
        float getEnvironmentGasCO2();
        float getBiomassTemperature();
        float getBiomassWeight();
        float getBiomassFluidAmount();
        float getBiomassPh();
    
    private:
        void initI2CWire();
        void initEnvIv();
        void initEns160();
        void initDS18B20();
};

#endif
