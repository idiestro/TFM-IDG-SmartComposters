/*
    MqttConnection.cpp - Library for mqtt transfer protocol
    Created by Ignacio Diestro Gil - 2025
*/

#include "MqttConnection.h"
#include "LogsUtils.h"
#include "ConfigReader.h"
#include "config/mqttConnectionConfig.h"
#include "config/wifiConfig.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//Definitions
#define payloadBufferSize 1024
MqttConnection* globalMqttInstance = nullptr;

//Callback function outside class
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    if (globalMqttInstance != nullptr) {
        globalMqttInstance->MqttConnection::handleCallback(topic, payload, length);
    }
}


//Declarations
WiFiClient espClient;
PubSubClient client(espClient);
LogsUtils logsUtils;

//BROKER connection
String clientId;


MqttConnection::MqttConnection() : client(espClient) {
    //Set clientId
    setClientId();
}

//Setup function to init wifi and broker connection
void MqttConnection::init(){
    reconnect();
}

//Reconnect main function
void MqttConnection::reconnect(){
    //Wifi disconnection check
    if(WiFi.status() != WL_CONNECTED){
        wifiConnection();
    }
    //Broker disconnection check
    if(!client.connected()){
        //Init server
        client.setServer(MQTT_BROKER, MQTT_PORT);
        globalMqttInstance = this;
        client.setCallback(mqttCallback);
        client.setKeepAlive(keepAliveInterval);
        client.setBufferSize(payloadBufferSize);
        //Init broker connection
        brokerConnection();
        //Topic subscription
        topicSubscription();
    }
}

//Wifi connection manager
void MqttConnection::wifiConnection() {
    delay(10);
    //Print wifi connection info
    LogsUtils::printLog("Conectando a:");
    LogsUtils::printLog(WIFI_SSID);
    //Connect to Wifi
    WiFi.begin(WIFI_SSID, ConfigReader::base64Decode(String(WIFI_PASS)));
    //Wait until successfull connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        LogsUtils::printLog(".");
    }
    //Show connection info
    LogsUtils::printLog("Conectado a Wifi");
    LogsUtils::printLog("IP address: " + WiFi.localIP().toString());
}

//Mqtt initial connection
void MqttConnection::brokerConnection(){
    //Connection loop
    while (!client.connected()) {
        LogsUtils::printLog("Conectando al Broker...");
        //Attempt to connect
        if (client.connect(clientId.c_str())) {
            LogsUtils::printLog("Conectado");
            LogsUtils::printLog("M5Stack Tough ID: ");
            LogsUtils::printLog(clientId);
        } 
        else {
            LogsUtils::printLog("Conexión fallida, rc=");
            LogsUtils::printLog(String(client.state()));
            LogsUtils::printLog(" reintentar en 5 segundos");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

//Subscribe to topic
void MqttConnection::topicSubscription() {
    //Topic Subscription
    if (client.subscribe(MQTT_SUBSCRIPTION_TOPIC)) {
        LogsUtils::printLog("Suscrito a topic: ");
        LogsUtils::printLog(MQTT_SUBSCRIPTION_TOPIC);
    } else {
        LogsUtils::printLog("Error al suscribirse al topic: ");
        LogsUtils::printLog(MQTT_SUBSCRIPTION_TOPIC);
    }
}

//Publish into topic
void MqttConnection::topicPublication(String payload){
    //Check if payload > buffer size
    if (payload.length() + 1 > payloadBufferSize) {
        LogsUtils::printLog("Error: El payload excede el tamaño del buffer.");
        return;
    }
    //Parse payload into char array
    char message[payloadBufferSize];
    payload.toCharArray(message, payloadBufferSize);
    
    //Send message
    if (client.publish(MQTT_PUBLICATION_TOPIC, message)) {
        LogsUtils::printLog("Mensaje Mqtt");
        Serial.println(payload);
        //LogsUtils::printLog(payload);
        LogsUtils::printLog("Publicado en topic: ");
        LogsUtils::printLog(MQTT_PUBLICATION_TOPIC);
    } else {
        LogsUtils::printLog("Error al publicar mensaje");
    }
}

//Callback para mensajes recibidos
void MqttConnection::handleCallback(char* topic, byte* payload, unsigned int length) {
    LogsUtils::printLog("Mensaje recibido en topic: ");
    LogsUtils::printLog(topic);
    LogsUtils::printLog("- Mensaje: ");

    String receivedMessage;
    for (int i = 0; i < length; i++) {
        receivedMessage += (char)payload[i];
    }
    LogsUtils::printLog(receivedMessage);
}
//Extract M5Tough MacAddress
void MqttConnection::setClientId(){
    clientId = WiFi.macAddress();
}

//Loop for mqtt connection
void MqttConnection::loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}

//Getter & Setters
PubSubClient MqttConnection::getMqttClient(){
    return client;
}

String MqttConnection::getClientId(){
    return clientId;
}
