/*
    RequestHelper.cpp - Library for request utilities
    Created by Ignacio Diestro Gil - 2025
*/

#include "RequestHelper.h"

#include <map>
#include "JsonUtils.h"
#include "HttpRestClient.h"
#include "data_payloads/fiwareDefaultPayloads.h"
#include "config/.fiwareConfig.h"


String token;

JsonUtils jsonUtils;


RequestHelper::RequestHelper() {
    token = new char[100];
}

/*
* Get Auth token from FIWARE
* @return: token as string
*/
String RequestHelper::getFiwareToken() {
    // Set Auth URL
    String& authUrl = "https://" + String(AUTH_HOST) + ":" + String(AUTH_PORT) + String(AUTH_FINAL_URL);

    //Set Auth Payload
    jsonUtils.loadDefaultJson(fiwareAuthPayload);
    //Set Payload values
    jsonUtils.setValue("auth.identity.password.user.domain.name", String(SERVICE), "string");
    jsonUtils.setValue("auth.identity.password.user.name", String(USERNAME), "string");
    jsonUtils.setValue("auth.identity.password.user.password", String(PASSWORD), "string");
    jsonUtils.setValue("auth.scope.project.doman.name", String(SERVICE), "string");
    jsonUtils.setValue("auth.scope.project.name", String(SUBSERVICE), "string");
    //Get json as string
    String authJsonPayload = jsonUtils.getJsonAsString();

    //Set Auth Headers
    std::map<String, String> headers = {
        {"Content-Type", "application/json"}
    };

    //Request Auth Token
    HttpResponse response = HttpRestClient::httpPost(authUrl, authJsonPayload, headers);

    return extractTokenFromResponseHeader(response.headers);
}

/*
* Extract token from response header
* @param headers: response headers
*/
String RequestHelper::extractTokenFromResponseHeader(std::map<String, String> headers) {
    return headers.find("X-Subject-Token")->second;    
}

/*
* Get Auth token as char
*/
String RequestHelper::getTokenAsString(){
    return token;
}