/*
    ConfigReader.cpp - Library for read crypted properties
    Created by Ignacio Diestro Gil - 2025
*/

#include "ConfigReader.h"

#include <Arduino.h>
#include <stdlib.h>

ConfigReader::ConfigReader(){
}


/*
* Decrypt a base64 encoded string.
* @param encoded: Base64 encoded string.
* @return: Decrypted string.
*/
const char* ConfigReader::base64Decode(const String &encoded) {
    const char* base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    int in_len = encoded.length();
    int i = 0, in_ = 0;
    uint8_t char_array_4[4], char_array_3[3];
    int output_len = (in_len * 3) / 4;
    char* output = (char*)malloc(output_len + 1); // +1 para el null terminator
    int pos = 0;

    if (!output) return nullptr;

    while (in_len-- && (encoded[in_] != '=') && isBase64(encoded[in_])) {
        char_array_4[i++] = encoded[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = strchr(base64_chars, char_array_4[i]) - base64_chars;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++) output[pos++] = (char)char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (int j = 0; j < 4; j++)
            char_array_4[j] = strchr(base64_chars, char_array_4[j]) - base64_chars;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int j = 0; j < (i - 1); j++) output[pos++] = (char)char_array_3[j];
    }

    output[pos] = '\0'; // Null-terminator
    return output;
}

bool ConfigReader::isBase64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}