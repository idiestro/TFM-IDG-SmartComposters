/*
    JsonUtils.h - Library for json utilities
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <ArduinoJson.h>

class JsonUtils {
public:
    // Constructor
    JsonUtils();

    bool loadDefaultJson(String inputJsonAsString);
    bool setValue(const String& jsonPath, const String& newValue, const String& valueType);
    String getJsonAsString();

private:
    DynamicJsonDocument jsonDoc;
    bool parseAndSet(JsonVariant& target, const String& value, const String& type);
};

#endif
