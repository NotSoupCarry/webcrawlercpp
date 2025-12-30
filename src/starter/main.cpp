//
// Created by soup on 30/12/2025.
//

#include <iostream>
#include "../interfaces/WebCrawler.h"

using namespace std;

int main() {
    cout << "=== WebCrawler ===" << endl;
    // string startUrl = "https://www.repubblica.it/";
    string startUrl;
    cout<< "enter the starting url: " ;
    cin >> startUrl;

    int maxDepth = 10;

    cout << "  URL: " << startUrl << endl;
    cout << "  Max Depth: " << maxDepth << endl << endl;

    WebCrawler crawler(maxDepth);
    crawler.crawl(startUrl);

    cout << "\n=== VISITED URL  ===" << endl << endl;
    int count = 1;
    for (const auto& url : crawler.getVisitedUrls()) {
        cout << count++ << ". " << url << endl;
    }
}