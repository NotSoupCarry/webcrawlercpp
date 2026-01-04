//
// Created by suop on 30/12/2025.
//

#ifndef WEBCRAWLER_WEBCRAWLER_H
#define WEBCRAWLER_WEBCRAWLER_H


#include <string>
#include <set>
#include <queue>
#include "HttpClient.h"
#include "HtmlParser.h"
#include "UrlNormalizer.h"
#include "OutputGen.h"
#include <functional>

class WebCrawler {
private:
    HttpClient httpClient;
    HtmlParser htmlParser;
    UrlNormalizer urlNormalizer;
    OutputGen outputGen;

    std::set<std::string> visitedUrls;
    std::queue<std::string> urlsToVisit;

    std::function<void(const std::string&)> logCallback;
    std::function<void(int, int)> progressCallback;
    std::function<bool()> shouldStopCallback;

    std::string allowedDomain;
    int maxDepth;
    int maxLinksPerPage;
    int currentDepth;

    bool shouldCrawl(const std::string &url);

    void crawlRecursive(const std::string &url, int depth);

public:
    WebCrawler(int maxDepth, int maxLinksPerPage);
    ~WebCrawler();

    void crawl(const std::string &startUrl);
    const std::set<std::string> &getVisitedUrls() const;
    void setAllowedDomain(const std::string &domain);

    void setLogCallback(std::function<void(const std::string&)> callback);
    void setProgressCallback(std::function<void(int, int)> callback);
    void setShouldStopCallback(std::function<bool()> callback);
};

#endif
//WEBCRAWLER_WEBCRAWLER_H
