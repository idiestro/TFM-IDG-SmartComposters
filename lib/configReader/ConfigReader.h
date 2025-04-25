/*
    ConfigReader.h - Library for read crypted properties
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <ArduinoJson.h>

class ConfigReader {
public:
    // Constructor
    ConfigReader();

    static const char* base64Decode(const String &encoded);


private:
    static bool isBase64(unsigned char c);
};

#endif
