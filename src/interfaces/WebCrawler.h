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

class WebCrawler {
private:
    HttpClient httpClient;
    HtmlParser htmlParser;
    UrlNormalizer urlNormalizer;

    std::set<std::string> visitedUrls;
    std::queue<std::string> urlsToVisit;

    std::string allowedDomain;
    int maxDepth;
    int currentDepth;

    // Controlla se un URL può essere crawlato
    bool shouldCrawl(const std::string &url);

    // Crawl ricorsivo con limite di profondità
    void crawlRecursive(const std::string &url, int depth);

public:
    WebCrawler(int maxDepth = 2);
    ~WebCrawler();

    void crawl(const std::string &startUrl);
    const std::set<std::string> &getVisitedUrls() const;
    void setAllowedDomain(const std::string &domain);
};

#endif //WEBCRAWLER_WEBCRAWLER_H
