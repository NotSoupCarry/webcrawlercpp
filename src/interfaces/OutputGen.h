//
// Created by soup on 02/01/2026.
//

#ifndef WEBCRAWLERCPP_OUTPUTGEN_H
#define WEBCRAWLERCPP_OUTPUTGEN_H

#include <string>
#include <fstream>
#include <set>

class OutputGen {
private:
    std::ofstream file;
    std::string filename;
    bool isOpen;

public:
    OutputGen();
    ~OutputGen();

    bool open(const std::string& filename);
    void close();
    void writeLine(const std::string& text);
    void writeHeader(const std::string& startUrl, int maxDepth, int maxLinksPerPage);
    void writeCrawlInfo(const std::string& url, int depth, int linksFound);
    void writeFooter(const std::set<std::string>& visitedUrls);
};


#endif //WEBCRAWLERCPP_OUTPUTGEN_H
