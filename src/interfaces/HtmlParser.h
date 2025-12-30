//
// Created by soup on 30/12/2025.
//

#ifndef WEBCRAWLER_HTMLPARSER_H
#define WEBCRAWLER_HTMLPARSER_H

#include <string>
#include <vector>

class HtmlParser {
public:
    HtmlParser();
    ~HtmlParser();

    std::vector<std::string> extractLinks(const std::string& html);

private:
    size_t findNextAnchor(const std::string& html, size_t startPos);

    std::string extractHref(const std::string& html, size_t anchorPos);
};

#endif //WEBCRAWLER_HTMLPARSER_H