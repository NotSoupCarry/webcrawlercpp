//
// Created by soup on 30/12/2025.
//

#ifndef WEBCRAWLER_URLNORMALIZER_H
#define WEBCRAWLER_URLNORMALIZER_H


#include <string>

class UrlNormalizer {
public:
    UrlNormalizer();
    ~UrlNormalizer();

    std::string normalize(const std::string& url, const std::string& baseUrl);
    std::string getDomain(const std::string& url);
    bool isValid(const std::string& url);

private:
    std::string removeFragment(const std::string& url);
    bool isAbsolute(const std::string& url);
    std::string makeAbsolute(const std::string& relativeUrl, const std::string& baseUrl);
};


#endif //WEBCRAWLER_URLNORMALIZER_H