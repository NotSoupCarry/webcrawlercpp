//
// Created by giuse on 30/12/2025.
//

#include "../interfaces/HtmlParser.h"
#include <algorithm>
#include <cctype>
#include <iostream>

HtmlParser::HtmlParser() {std::cout << "HtmlParser created" << std::endl;}
HtmlParser::~HtmlParser() {std::cout << "HtmlParser destroyed" << std::endl;}

std::vector<std::string> HtmlParser::extractLinks(const std::string& html) {
    std::vector<std::string> links;
    size_t pos = 0;

    while (true) {
        pos = findNextAnchor(html, pos);

        if (pos == std::string::npos)
            break;


        std::string href = extractHref(html, pos);

        if (!href.empty())
            links.push_back(href);

        pos++;
    }

    std::cout << "Found " << links.size() << " links" << std::endl;
    return links;
}

size_t HtmlParser::findNextAnchor(const std::string& html, size_t startPos) {
    size_t pos = startPos;

    while (pos < html.size()) {
        pos = html.find('<', pos);

        if (pos == std::string::npos) {
            return std::string::npos;
        }

        if (pos + 1 < html.size()) {
            char next = std::tolower(html[pos + 1]);

            if (next == 'a') {
                if (pos + 2 < html.size()) {
                    char after = html[pos + 2];
                    if (after == ' ' || after == '\t' || after == '\n' || after == '>') {
                        return pos;
                    }
                }
            }
        }

        pos++;
    }

    return std::string::npos;
}

std::string HtmlParser::extractHref(const std::string& html, size_t anchorPos) {
    // Trova la fine del tag <a ...>
    size_t tagEnd = html.find('>', anchorPos);

    if (tagEnd == std::string::npos) {
        return "";
    }

    // Cerca href= all'interno del tag
    std::string tag = html.substr(anchorPos, tagEnd - anchorPos);

    size_t hrefPos = tag.find("href");
    if (hrefPos == std::string::npos) {
        // Prova case-insensitive
        std::string tagLower = tag;
        std::transform(tagLower.begin(), tagLower.end(), tagLower.begin(), ::tolower);
        hrefPos = tagLower.find("href");

        if (hrefPos == std::string::npos) {
            return "";
        }
    }

    // skip "href"
    hrefPos += 4;

    // skip " " "="
    while (hrefPos < tag.size() && (tag[hrefPos] == ' ' || tag[hrefPos] == '=')) {
        hrefPos++;
    }

    if (hrefPos >= tag.size()) {
        return "";
    }

    char delimiter = tag[hrefPos];
    size_t urlStart, urlEnd;

    if (delimiter == '"' || delimiter == '\'') {
        urlStart = hrefPos + 1;
        urlEnd = tag.find(delimiter, urlStart);
    } else {
        urlStart = hrefPos;
        urlEnd = tag.find_first_of(" \t\n>", urlStart);
    }

    if (urlEnd == std::string::npos) {
        urlEnd = tag.size();
    }

    return tag.substr(urlStart, urlEnd - urlStart);
}