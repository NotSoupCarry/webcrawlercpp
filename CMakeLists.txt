cmake_minimum_required(VERSION 4.1)
project(webcrawlercpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(webcrawlercpp src/starter/main.cpp
        src/impl/HttpClient.cpp
        src/impl/HtmlParser.cpp
        src/impl/UrlNormalizer.cpp
        src/impl/WebCrawler.cpp
)

if(WIN32)
    target_link_libraries(webcrawlercpp wininet ws2_32)
endif()
