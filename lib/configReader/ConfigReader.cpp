/*
    ConfigReader.cpp - Library for read config files
    Created by Ignacio Diestro Gil - 2025
*/

#include "ConfigReader.h"

ConfigReader::ConfigReader() {
    //Init SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Error al montar SPIFFS");
        return;
    }

    //Read config file
    readConfig();
}

void ConfigReader::readConfig() {
    //Open config file
    File configFile = SPIFFS.open("/config.txt", "r");
    if (!configFile) {
        Serial.println("Error al abrir config.txt");
        return;
    }

    String line;
    while (configFile.available()) {
        line = configFile.readStringUntil('\n');
        int separatorIndex = line.indexOf('=');
        if (separatorIndex != -1) {
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);
            configMap[key] = value;
        }
    }
    configFile.close();
}

//Get config properties using key
String ConfigReader::getConfigParameter(const String& param) {
    if (configMap.find(param) != configMap.end()) {
        return configMap[param];
    } else {
        Serial.print("Parámetro no encontrado: ");
        Serial.println(param);
        //Empty value if not found
        return "";
    }
}
