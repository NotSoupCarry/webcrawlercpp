//
// Created by soup on 30/12/2025.
//

#include "../interfaces/HttpClient.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>

HttpClient::HttpClient() { std::cout << "HttpClient created" << std::endl; }
HttpClient::~HttpClient() { std::cout << "HttpClient destroyed" << std::endl; }

std::string HttpClient::downloadPage(const std::string &url) {
    std::string result;

    HINTERNET hInternet = InternetOpenA(
        "MyCrawler/1.0",
        INTERNET_OPEN_TYPE_DIRECT,
        NULL, NULL, 0
    );

    if (!hInternet) {
        std::cerr << "Error starting WinINet" << std::endl;
        return "";
    }

    HINTERNET hUrl = InternetOpenUrlA(
        hInternet,
        url.c_str(),
        NULL, 0,
        INTERNET_FLAG_RELOAD,
        0
    );

    if (!hUrl) {
        std::cerr << "error opening this link: " << url << std::endl;
        InternetCloseHandle(hInternet);
        return "";
    }

    char buffer[4096];
    DWORD bytesRead;

    std::cout << "downloading..." << std::endl;

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        result.append(buffer, bytesRead);
    }

    std::cout << "downloaded " << result.size() << " BYTES" << std::endl;

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    return result;
}
