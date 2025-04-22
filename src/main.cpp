/*
    M5Tough_measures.ino - Main funtion to M5Tough TFM composters
    Created by Ignacio Diestro Gil - 2025
*/

#include <M5Unified.h>
#include "config/mainConfig.h"

//Utils libraries
#include "SimulatedMeasures.h"
#include "MqttConnection.h"
#include "LogsUtils.h"
#include "JsonUtils.h"

//Instance classes
SimulatedMeasures simulatedMeasures;
MqttConnection mqttConnection;
JsonUtils jsonUtils;


void setup(void) {
    //Init M5 and serial port
    init();
}

void loop(void) {
    // Initial CPU pause
    delay(100);

    //JOB TEST
    jsonUtils.loadDefaultJson();
    jsonUtils.setValue("m5BateryLevel", String(simulatedMeasures.getEnvironmentTemperature()), "float");

    Serial.println(jsonUtils.getJsonAsString());

    //Final delay
    delay(2000);


}

//Initial system load and config
void init() {
    //Init M5 and serial port
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    //Initial message
    LogsUtils::printLog("---Iniciando sistema---");
    //Init wifi and broker connection
    mqttConnection.init();
    LogsUtils::printLog("---Sistema iniciado---");
    //Wait after setup
    delay(5000);
}

