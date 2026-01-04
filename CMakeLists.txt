cmake_minimum_required(VERSION 4.1)
project(webcrawlercpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/mingw_64")

# Qt configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
message(STATUS "Qt6 found at: ${Qt6_DIR}")

add_executable(webcrawlercpp
        src/starter/main.cpp
        src/impl/HttpClient.cpp
        src/impl/HtmlParser.cpp
        src/impl/UrlNormalizer.cpp
        src/impl/WebCrawler.cpp
        src/impl/OutputGen.cpp
        src/QT/MainWindow.h
        src/QT/MainWindow.cpp
)

target_link_libraries(webcrawlercpp
        Qt6::Widgets
        wininet
        ws2_32
)

# Link WinINet (Windows)
if(WIN32)
    target_link_libraries(webcrawlercpp wininet ws2_32)
endif()