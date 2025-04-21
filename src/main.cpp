/*
    M5Tough_measures.ino - Main funtion to M5Tough TFM composters
    Created by Ignacio Diestro Gil - 2025
*/

#include <M5Unified.h>
#include "mainConfig.h"

//Utils libraries
#include "SimulatedMeasures.h"
#include "MqttConnection.h"
#include "LogsUtils.h"

//Instance classes
SimulatedMeasures simulatedMeasures;
MqttConnection mqttConnection;


void setup(void) {
    //Init M5 and serial port
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(PORT_SPEED);
    //Initial message
    LogsUtils::printLog("---Iniciando sistema---");
    //Init wifi and broker connection
    mqttConnection.init();
    LogsUtils::printLog("---Sistema iniciado---");
    //Wait after setup
    delay(5000);
}

void loop(void) {
    // Initial CPU pause
    delay(100);
    delay(2000);


}
