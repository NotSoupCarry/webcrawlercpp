//
// Created by soup on 30/12/2025.
//

#ifndef WEBCRAWLER_HTTPCLIENT_H
#define WEBCRAWLER_HTTPCLIENT_H


#include <string>

class HttpClient {
public:
    HttpClient();
    ~HttpClient();

    static std::string downloadPage(const std::string& url);
};


#endif //WEBCRAWLER_HTTPCLIENT_H