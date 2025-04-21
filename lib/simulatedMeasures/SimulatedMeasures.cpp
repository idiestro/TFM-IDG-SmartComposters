/*
    SimularedMeasures.cpp - Library for simulate measures from composter
    Created by Ignacio Diestro Gil - 2025
*/

#include "SimulatedMeasures.h"

#include <stdlib.h>
#include <time.h>
#include <Arduino.h>

SimulatedMeasures::SimulatedMeasures(){
    randomSeed(micros());  // Inicializa el generador de números aleatorios
}

// Función para obtener la temperatura ambiental simulada
float SimulatedMeasures::getEnvironmentTemperature() {
    return 15 + rand() % 16;  // Temperatura aleatoria entre 15 y 30°C
}

// Función para obtener la humedad ambiental simulada
float SimulatedMeasures::getEnvironmentHumidity() {
    return 30 + rand() % 51;  // Humedad aleatoria entre 30 y 80%
}

// Función para obtener el nivel de oxígeno en el gas ambiental simulado
float SimulatedMeasures::getEnvironmentGasO2() {
    return 19 + rand() % 2;  // Oxígeno entre 19% y 20%
}

// Función para obtener el nivel de dióxido de carbono en el gas ambiental simulado
float SimulatedMeasures::getEnvironmentGasCO2() {
    return 0.04 + rand() % 3 * 0.01;  // CO2 entre 0.04% y 0.1%
}

// Función para obtener la temperatura de la biomasa simulada
float SimulatedMeasures::getBiomassTemperature() {
    return 30 + rand() % 11;  // Temperatura de biomasa entre 30 y 40°C
}

// Función para obtener el peso de la biomasa simulada
float SimulatedMeasures::getBiomassWeight() {
    return 100 + rand() % 901;  // Peso entre 100g y 1000g
}

// Función para obtener la cantidad de fluido de la biomasa simulada
float SimulatedMeasures::getBiomassFluidAmount() {
    return 10 + rand() % 91;  // Fluido entre 10ml y 100ml
}

// Función para obtener el pH de la biomasa simulada
float SimulatedMeasures::getBiomassPh() {
    return 6 + rand() % 5;  // pH entre 6 y 10
}
