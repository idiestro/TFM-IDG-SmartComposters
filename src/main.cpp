/*
    M5Tough_measures.ino - Main funtion to M5Tough TFM composters
    Created by Ignacio Diestro Gil - 2025
*/

#include <M5Unified.h>
#include <Wire.h>
#include "config/mainConfig.h"

//Utils libraries
#include "MqttConnection.h"
#include "LogsUtils.h"
#include "MeasuresDataHelper.h"
#include "MeasuresReader.h"

//Instance classes
MqttConnection mqttConnection;
MeasuresDataHelper measuresDataHelper;
MeasuresReader measuresReader;

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
    //Init measures reader
    measuresReader.initSensors();
    LogsUtils::printLog("---Sistema iniciado---");
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
        //Get measures from sensors and set into final payload
        String finalPayload = measuresDataHelper.setMeasuresIntoJson();
        //Publish measures to MQTT broker
        mqttConnection.topicPublication(finalPayload);
    }
}

