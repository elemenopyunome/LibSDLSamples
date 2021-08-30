#ifndef HTTPDOWNLOADER_HPP
#define HTTPDOWNLOADER_HPP

#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include <sstream>
#include <iostream>
class HTTPDownloader {
public:
    HTTPDownloader();
    ~HTTPDownloader();
    std::string download(const std::string& url);
    std::string downloadtostring(const std::string& url);
    std::string download_mvt(const std::string& url);
private:
    void* curl;
};

#endif  /* HTTPDOWNLOADER_HPP */