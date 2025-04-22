/*
    JsonUtils.cpp - Library for json utilities
    Created by Ignacio Diestro Gil - 2025
*/

#include "JsonUtils.h"
#include "data_payloads/fiwareDefaultPayload.h"


JsonUtils::JsonUtils() : doc(2048) {
}

/*
* Load default json payload in a .h file.
* @param filePath: Path to the JSON file.
*/
bool JsonUtils::loadDefaultJson() {
    String payload = fiwarePayload;

    // Deserialize json payload
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        Serial.print("Error al parsear el JSON: ");
        Serial.println(error.c_str());
        return false;
    }

    return true;
}

/*
* Set a new value in the JSON document at the specified path.
* @param jsonPath: Path to the JSON element (e.g., "root.child.grandchild").
* @param newValue: New value to set.
* @param valueType: Type of the new value (e.g., "string", "int", "float", "bool").
*/
bool JsonUtils::setValue(const String& jsonPath, const String& newValue, const String& valueType) {
    JsonVariant current = doc.as<JsonVariant>();
    int start = 0, end;
    while ((end = jsonPath.indexOf('.', start)) != -1) {
        String key = jsonPath.substring(start, end);
        current = current[key];
        if (current.isNull()) return false;
        start = end + 1;
    }

    String lastKey = jsonPath.substring(start);
    JsonVariant target = current[lastKey];

    return parseAndSet(target, newValue, valueType);
}

/*
* Parse a value and set it in the JSON document.
* @param target: JsonVariant to set the value in.
* @param value: Value to set.
* @param type: Type of the value (e.g., "string", "int", "float", "bool").
*/
bool JsonUtils::parseAndSet(JsonVariant& target, const String& value, const String& type) {
    if (type == "string") {
        target.set(value);
    } else if (type == "float") {
        target.set(value.toFloat());
    } else if (type == "int") {
        target.set(value.toInt());
    } else if (type == "bool") {
        target.set(value == "true" || value == "1");
    } else {
        Serial.println("Tipo no soportado en parseAndSet");
        return false;
    }
    return true;
}

/*
* Get the JSON document as a string.
* @return: JSON document as a string.
*/
String JsonUtils::getJsonAsString() {
    String output;
    serializeJson(doc, output);
    return output;
}
