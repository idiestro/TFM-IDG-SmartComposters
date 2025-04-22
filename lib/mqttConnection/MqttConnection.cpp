/*
    MqttConnection.cpp - Library for mqtt transfer protocol
    Created by Ignacio Diestro Gil - 2025
*/

#include "MqttConnection.h"
#include "LogsUtils.h"
#include "config/mqttConnectionConfig.h"
#include "config/.wifiConfig.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

//Definitions
#define payloadBufferSize 80

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
    //Init wifi connection
    wifiConnection(WIFI_SSID, WIFI_PASS);
    //Init server
    client.setServer(MQTT_BROKER, MQTT_PORT);
    client.setCallback(callback);
    //Init broker connection
    brokerConnection();
}

//Wifi connection manager
void MqttConnection::wifiConnection(const char* wifiSsid, const char* wifiPassword) {
  delay(10);
  //Print wifi connection info
  LogsUtils::printLog("Conectando a:");
  LogsUtils::printLog(String(wifiSsid));
  //Connect to Wifi
  WiFi.begin(wifiSsid, wifiPassword);
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
void MqttConnection::topicSubscription(const char* subscriptionTopic) {
    //Topic Subscription
    client.subscribe(subscriptionTopic);
    client.setKeepAlive(30);
    //Print subscription info
    LogsUtils::printLog("Suscrito a topic: ");
    LogsUtils::printLog(subscriptionTopic);
}

//Publish into topic
void MqttConnection::topicPublication(String payload, const char* publicationTopic){
    //Parse payload into char array
    char message[payloadBufferSize];
    payload.toCharArray(message,payloadBufferSize);
    //Send message
    client.publish(publicationTopic, message);
    //Print info for sent message
    LogsUtils::printLog("Mensaje: ");
    LogsUtils::printLog(payload);
    LogsUtils::printLog("Publicado en topic: ");
    LogsUtils::printLog(publicationTopic);
}

//Callback por si recibimos mensaje - Modulo
void callback(char* topic, byte* message, unsigned int length) {
    //Print callback info
    LogsUtils::printLog("Mensaje recibido en topic: ");
    LogsUtils::printLog(topic);
    LogsUtils::printLog("- Mensaje: ");

    //Print received message
    String receivedMessage;
    for (int i = 0; i < length; i++) {
    receivedMessage += (char)message[i];
    }
    LogsUtils::printLog(receivedMessage);
}

//Extract M5Tough MacAddress
void MqttConnection::setClientId(){
    clientId= WiFi.macAddress();
}

//Getter & Setters
PubSubClient MqttConnection::getMqttClient(){
    return client;
}
String MqttConnection::getClientId(){
    return clientId;
}

