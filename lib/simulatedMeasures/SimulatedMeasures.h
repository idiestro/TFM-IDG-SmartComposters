/*
    SimularedMeasures.h - Library for simulate measures from composter
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef SIMULATED_MEASURES_H
#define SIMULATED_MEASURES_H

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

class SimulatedMeasures {
    public:
        SimulatedMeasures();
        float getEnvironmentTemperature();
        float getEnvironmentHumidity();
        float getEnvironmentGasO2();
        float getEnvironmentGasCO2();
        float getBiomassTemperature();
        float getBiomassWeight();
        float getBiomassFluidAmount();
        float getBiomassPh();
};

#endif
