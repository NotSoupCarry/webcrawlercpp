//
// Created by soup on 30/12/2025.
//

#include "../interfaces/UrlNormalizer.h"
#include <iostream>

UrlNormalizer::UrlNormalizer() { std::cout << "UrlNormalizer created" << std::endl; }
UrlNormalizer::~UrlNormalizer() { std::cout << "UrlNormalizer destroyed" << std::endl; }

std::string UrlNormalizer::normalize(const std::string &url, const std::string &baseUrl) {
    if (url.empty())
        return "";

    if (url[0] == '#')
        return "";

    if (url.find("javascript:") == 0 || url.find("mailto:") == 0)
        return "";

    std::string result = url;

    if (!isAbsolute(result))
        result = makeAbsolute(result, baseUrl);

    result = removeFragment(result);

    size_t schemeEnd = result.find("://");
    if (schemeEnd != std::string::npos) {
        size_t domainStart = schemeEnd + 3;
        size_t domainEnd = result.find('/', domainStart);

        if (domainEnd == std::string::npos) {
            domainEnd = result.size();
        }

        for (size_t i = 0; i < domainEnd; i++) {
            result[i] = std::tolower(result[i]);
        }
    }

    return result;
}

std::string UrlNormalizer::getDomain(const std::string &url) {
    size_t schemeEnd = url.find("://");

    if (schemeEnd == std::string::npos) {
        return "";
    }

    size_t domainStart = schemeEnd + 3;
    size_t domainEnd = url.find('/', domainStart);

    if (domainEnd == std::string::npos) {
        domainEnd = url.size();
    }

    return url.substr(domainStart, domainEnd - domainStart);
}

bool UrlNormalizer::isValid(const std::string &url) {
    if (url.empty())
        return false;

    return url.find("http://") == 0 || url.find("https://") == 0;
}

std::string UrlNormalizer::removeFragment(const std::string &url) {
    size_t fragmentPos = url.find('#');

    if (fragmentPos != std::string::npos) {
        return url.substr(0, fragmentPos);
    }

    return url;
}

bool UrlNormalizer::isAbsolute(const std::string &url) {
    return url.find("http://") == 0 || url.find("https://") == 0;
}

std::string UrlNormalizer::makeAbsolute(const std::string &relativeUrl, const std::string &baseUrl) {
    if (relativeUrl[0] == '/') {
        size_t schemeEnd = baseUrl.find("://");
        if (schemeEnd == std::string::npos) {
            return "";
        }

        size_t domainStart = schemeEnd + 3;
        size_t domainEnd = baseUrl.find('/', domainStart);

        std::string domain;
        if (domainEnd != std::string::npos) {
            domain = baseUrl.substr(0, domainEnd);
        } else {
            domain = baseUrl;
        }

        return domain + relativeUrl;
    } else {
        size_t lastSlash = baseUrl.rfind('/');

        if (lastSlash != std::string::npos) {
            std::string basePath = baseUrl.substr(0, lastSlash + 1);
            return basePath + relativeUrl;
        }

        return baseUrl + "/" + relativeUrl;
    }
}
