#include "HttpRestClient.h"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

HttpRestClient::HttpRestClient() {}

HttpResponse HttpRestClient::httpPost(String& url, String& payload, std::map<String, String>& headers) {
    HTTPClient http;
    WiFiClientSecure client;
    client.setInsecure(); 

    HttpResponse response;
    response.statusCode = -1;

    if (http.begin(client, url)) {
        for (const auto& header : headers) {
            http.addHeader(header.first, header.second);
        }

        response.statusCode = http.POST(payload);
        if (response.statusCode > 0) {
            response.body = http.getString();
            response.headers["X-Subject-Token"] = http.header("X-Subject-Token");

        } else {
            Serial.printf("HTTP POST error: %s\n", http.errorToString(response.statusCode).c_str());
            response.body = "";
        }

        http.end();
    } else {
        Serial.println("Error al iniciar la conexión HTTP.");
    }

    return response;
}
