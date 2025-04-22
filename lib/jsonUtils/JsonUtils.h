/*
    JsonUtils.h - Library for json utilities
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

class JsonUtils {
public:
    // Constructor
    JsonUtils();

    bool loadDefaultJson();
    bool setValue(const String& jsonPath, const String& newValue, const String& valueType);
    String getJsonAsString();

private:
    DynamicJsonDocument doc;
    bool parseAndSet(JsonVariant& target, const String& value, const String& type);
};

#endif
