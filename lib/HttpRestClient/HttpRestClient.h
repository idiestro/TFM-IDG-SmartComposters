#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <map>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>


struct HttpResponse {
    int statusCode;
    String body;
    std::map<String, String> headers;
};

class HttpRestClient {
public:
    //Constructor
    HttpRestClient();

    static HttpResponse httpPost(String& url, String& payload, std::map<String, String>& header);

private:
};

#endif
