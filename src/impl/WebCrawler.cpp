//
// Created by soup on 30/12/2025.
//

#include "../interfaces/WebCrawler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

WebCrawler::WebCrawler(int maxDepth) : maxDepth(maxDepth), currentDepth(0) {std::cout << "WebCrawler created, Max depth: " << maxDepth << std::endl;}
WebCrawler::~WebCrawler() {std::cout << "WebCrawler destroyed " << std::endl;}

void WebCrawler::crawl(const std::string& startUrl) {
    std::cout << "\n=== START CRAWLING ===" << std::endl;
    std::cout << "starting URL: " << startUrl << std::endl;

    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::ostringstream filename;
    filename << "outputs/crawl_"
             << std::put_time(ltm, "%Y%m%d_%H%M%S")
             << ".txt";

    if (!outputGen.open(filename.str())) {
        std::cerr << "Error creating the output file" << std::endl;
        return;
    }

    outputGen.writeHeader(startUrl, maxDepth);

    allowedDomain = urlNormalizer.getDomain(startUrl);
    std::cout << "allowd domain: " << allowedDomain << std::endl << std::endl;

    crawlRecursive(startUrl, 0);

    outputGen.writeFooter(visitedUrls);
    outputGen.close();

    std::cout << "\n=== CRAWLING ENDED ===" << std::endl;
    std::cout << "visited urls: " << visitedUrls.size() << std::endl;
    std::cout << "Output saved in: " << filename.str() << std::endl;
}

void WebCrawler::crawlRecursive(const std::string& url, int depth) {
    if (depth > maxDepth)
        return;


    if (visitedUrls.count(url))
        return;


    if (!shouldCrawl(url))
        return;


    std::string indent(depth * 2, ' ');
    std::cout << indent << "[Depth " << depth << "] Crawling: " << url << std::endl;

    visitedUrls.insert(url);

    std::string html = httpClient.downloadPage(url);

    if (html.empty()) {
        std::cout << indent << "  -> eror downloading" << std::endl;
        return;
    }

    std::vector<std::string> links = htmlParser.extractLinks(html);
    std::cout << indent << "  -> found " << links.size() << " link" << std::endl;

    int crawledLinks = 0;
    for (const auto& link : links) {
        std::string normalizedUrl = urlNormalizer.normalize(link, url);

        if (!normalizedUrl.empty() && shouldCrawl(normalizedUrl)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            crawlRecursive(normalizedUrl, depth + 1);
            crawledLinks++;

            // if (crawledLinks >= 5) {
            //     std::cout << indent << "  -> Link limit of 5" << std::endl;
            //     break;
            // }
        }
    }
}

bool WebCrawler::shouldCrawl(const std::string& url) {
    if (!urlNormalizer.isValid(url))
        return false;

    if (visitedUrls.count(url))
        return false;

    if (std::string domain = urlNormalizer.getDomain(url); domain != allowedDomain)
        return false;

    return true;
}

const std::set<std::string>& WebCrawler::getVisitedUrls() const {
    return visitedUrls;
}

void WebCrawler::setAllowedDomain(const std::string& domain) {
    allowedDomain = domain;
}