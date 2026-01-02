//
// Created by soup on 30/12/2025.
//

#include <iostream>
#include "../interfaces/WebCrawler.h"

using namespace std;

int main() {
    cout << "=== WebCrawler ===" << endl;
    string startUrl = "https://www.repubblica.it/";
    // string startUrl;
    // cout<< "enter the starting url: "; cin >> startUrl;

    int maxDepth = 2;
    int maxLinks = 2;

    cout << "  URL: " << startUrl << endl;
    cout << "  Max Depth: " << maxDepth << endl << endl;

    WebCrawler crawler(maxDepth, maxLinks);
    crawler.crawl(startUrl);

    cout << "\n=== VISITED URL  ===" << endl << endl;
    int count = 1;
    for (const auto& url : crawler.getVisitedUrls()) {
        cout << count++ << ". " << url << endl;
    }
    cout << endl;
}