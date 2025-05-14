/*
    M5Tough_measures.ino - Main funtion to M5Tough TFM composters
    Created by Ignacio Diestro Gil - 2025
*/

#include <M5Unified.h>
#include "config/mainConfig.h"

//Utils libraries
#include "MqttConnection.h"
#include "LogsUtils.h"
#include "MeasuresDataHelper.h"

//Instance classes
MqttConnection mqttConnection;
MeasuresDataHelper measuresDataHelper;

//Main values
String composterId;


void setup(void) {
    //Init M5 and serial port
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);
    //Initial message
    LogsUtils::printLog("---Iniciando sistema---");
    //Init wifi and broker connection
    mqttConnection.init();
    LogsUtils::printLog("---Sistema iniciado---");
    //Get composter ID
    composterId = mqttConnection.getClientId();
    //Wait after setup
    delay(5000);
}

void loop(void) {
    // Initial CPU pause
    delay(10);

    //Mqtt Connection loop
    mqttConnection.loop(); 

    // Read values and send messages
    static unsigned long lastPublishTime = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastPublishTime >= 10000) { // 10 seconds
        lastPublishTime = currentMillis;
            // Set composter ID
            measuresDataHelper.setComposterId(composterId);
            // Set measures data
            mqttConnection.topicPublication(measuresDataHelper.setMeasuresIntoJson());
    }
}

