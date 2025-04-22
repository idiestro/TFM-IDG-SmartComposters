/*
    RequestHelper.h - Library for request utilities
    Created by Ignacio Diestro Gil - 2025
*/

#ifndef REQIEST_HELPER_H
#define REQIEST_HELPER_H

#include "JsonUtils.h"


class RequestHelper {
public:
    // Constructor
    RequestHelper();

    String getFiwareToken();
    String getTokenAsString();

private:
    String token;
    String extractTokenFromResponseHeader(std::map<String, String> headers);

};

#endif
