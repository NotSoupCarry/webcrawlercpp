//
// Created by soup on 02/01/2026.
//

#include "../interfaces/OutputGen.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <direct.h>

OutputGen::OutputGen() : isOpen(false) {
}

OutputGen::~OutputGen() {
    if (isOpen) {
        close();
    }
}

bool OutputGen::open(const std::string& filename) {
    this->filename = filename;

    struct stat info;
    if (stat("outputs", &info) != 0) {
        _mkdir("outputs");  // Windows
        // mkdir("outputs"); // Linux
        std::cout << "folder 'outputs' created" << std::endl;
    }

    file.open(filename, std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error cant open file: " << filename << std::endl;
        return false;
    }

    isOpen = true;
    std::cout << "Output saved in: " << filename << std::endl;
    return true;
}

void OutputGen::close() {
    if (isOpen) {
        file.close();
        isOpen = false;
    }
}

void OutputGen::writeLine(const std::string& line) {
    if (isOpen) {
        file << line << std::endl;
        file.flush();
    }
}

void OutputGen::writeHeader(const std::string& startUrl, int maxDepth, int maxLinksPerPage) {
    if (!isOpen) return;

    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::ostringstream oss;
    oss << std::put_time(ltm, "%Y/%m/%d %H:%M:%S");

    writeLine("========================================");
    writeLine("             CRAWLING LOG               ");
    writeLine("========================================");
    writeLine("");
    writeLine("Date/Time: " + oss.str());
    writeLine("Start URL: " + startUrl);
    writeLine("Max Depth: " + std::to_string(maxDepth));
    writeLine("Limit of Links per page: " + std::to_string(maxLinksPerPage));
    writeLine("");
    writeLine("========================================");
    writeLine("");
}

void OutputGen::writeCrawlInfo(const std::string& url, int depth, int linksFound) {
    if (!isOpen) return;

    std::string indent(depth * 2, ' ');

    writeLine(indent + "[Depth " + std::to_string(depth) + "] Crawling: " + url);
    writeLine(indent + "  -> Found " + std::to_string(linksFound) + " links");
}

void OutputGen::writeFooter(const std::set<std::string>& visitedUrls) {
    if (!isOpen) return;

    writeLine("");
    writeLine("========================================");
    writeLine("         CRAWLING COMPLETED             ");
    writeLine("========================================");
    writeLine("");
    writeLine("Total pages visited: " + std::to_string(visitedUrls.size()));
    writeLine("");
    writeLine("");

    int count = 1;
    for (const auto& url : visitedUrls) {
        writeLine(std::to_string(count++) + ". " + url);
    }

    writeLine("");
    writeLine("========================================");
    writeLine("               END OF LOG               ");
    writeLine("========================================");
}
