/*
    MeasuresDataHelper.cpp - Library for set measures into Json payload to send
    Created by Ignacio Diestro Gil - 2025
*/

#include "MeasuresDataHelper.h"

#include <SimulatedMeasures.h>
#include <MeasuresReader.h>
#include <JsonUtils.h>
#include <data_payloads/fiwareDefaultFormatPayload.h>

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

//Init classes
SimulatedMeasures simulatedMeasures;
MeasuresReader measuresReader;
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
    //Environment variables
    jsonUtils.setValue("environmentGasCO2.value", String(measuresReader.getEnvironmentGasCO2()), "float");
    jsonUtils.setValue("environmentGasO2.value", String(-1), "float");
    jsonUtils.setValue("environmentHumidity.value", String(measuresReader.getEnvironmentHumidity()), "float");
    jsonUtils.setValue("environmentTemperature.value", String(measuresReader.getEnvironmentTemperature()), "float");
    //Biomass variables
    jsonUtils.setValue("biomassFluidAmount.value", String(-1), "float");
    jsonUtils.setValue("biomassPh.value", String(-1), "float");
    jsonUtils.setValue("biomassTemperature.value", String(measuresReader.getBiomassTemperature()), "float");
    jsonUtils.setValue("biomassWeight.value", String(-1), "float");
    jsonUtils.setValue("m5BateryLevel.value", String(-1), "int");
    
    return jsonUtils.getJsonAsString();
     
}