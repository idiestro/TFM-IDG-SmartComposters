/*
    ConfigReader.h - Library for read config files
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef ConfigReader_h
#define ConfigReader_h

#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <map>

class ConfigReader {
private:
    std::map<String, String> configMap;

    void readConfig();

public:
    //Constructor
    ConfigReader();

    String getConfigParameter(const String& param);
};

#endif
