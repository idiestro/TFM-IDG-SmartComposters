/*
    MeasuresDataHelper.cpp - Library for set measures into Json payload to send
    Created by Ignacio Diestro Gil - 2025
*/

#include "MeasuresDataHelper.h"

#include <SimulatedMeasures.h>
#include <JsonUtils.h>
#include <data_payloads/fiwareDefaultFormatPayload.h>

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

//Init classes
SimulatedMeasures simulatedMeasures;
JsonUtils jsonUtils;

MeasuresDataHelper::MeasuresDataHelper(){
    jsonUtils.loadDefaultJson(fiwareFormatPayload);
}

void MeasuresDataHelper::setComposterId(String composterId) {
    // Set composter ID
    jsonUtils.setValue("id", composterId, "string");
}   


String MeasuresDataHelper::setMeasuresIntoJson() {
    // Set values in JSON
    jsonUtils.setValue("biomassFluidAmount.value", String(simulatedMeasures.getBiomassFluidAmount()), "float");
    jsonUtils.setValue("biomassPh.value", String(simulatedMeasures.getBiomassPh()), "float");
    jsonUtils.setValue("biomassTemperature.value", String(simulatedMeasures.getBiomassTemperature()), "float");
    jsonUtils.setValue("biomassWeight.value", String(simulatedMeasures.getBiomassWeight()), "float");
    jsonUtils.setValue("environmentGasCO2.value", String(simulatedMeasures.getEnvironmentGasCO2()), "float");
    jsonUtils.setValue("environmentGasO2.value", String(simulatedMeasures.getEnvironmentGasO2()), "float");
    jsonUtils.setValue("environmentHumidity.value", String(simulatedMeasures.getEnvironmentHumidity()), "float");
    jsonUtils.setValue("environmentTemperature.value", String(simulatedMeasures.getEnvironmentTemperature()), "float");
    jsonUtils.setValue("m5BateryLevel.value", String(100), "int");
    
    return jsonUtils.getJsonAsString();
     
}