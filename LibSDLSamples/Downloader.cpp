#include "Downloader.h"
#include <SDL.h>

#pragma warning(disable : 4996)
using namespace std;

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
    string data((const char*)ptr, (size_t)size * nmemb);
    *((stringstream*)stream) << data << endl;
    return size * nmemb;
}
size_t write_data_to_file(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
    if (!stream)
    {
        printf("!!! No stream\n");
        return 0;
    }

    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}
std::string gen_random(const int len) {

    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srand((unsigned)time(NULL) * getpid());

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


    return tmp_s;

}
HTTPDownloader::HTTPDownloader() {
    curl = curl_easy_init();
}

HTTPDownloader::~HTTPDownloader() {
    curl_easy_cleanup(curl);
}

string HTTPDownloader::download(const std::string& url) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    std::stringstream out;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    }
    return out.str();
}
string HTTPDownloader::downloadtostring(const std::string& urlval) {
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* url = urlval.c_str();
    char outfilename[FILENAME_MAX] = "D:\\Files\info.mvt";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return "";
    //return out.str();
}
std::string HTTPDownloader::download_mvt(const std::string& url)
{
    std::string BaseFileLevel = "D:\\Files\\MVTFilesRepo\\";
    std::string RandomFileName = gen_random(26) + ".mvt";
    std::string CompleteFilePath = BaseFileLevel + RandomFileName;
    //char outfilename[FILENAME_MAX] = CompleteFilePath.c_str();
    FILE* fp = fopen(CompleteFilePath.c_str(), "wb");
    if (!fp)
    {
        printf("!!! Failed to create file on the disk\n");
        return "";
    }
    
    CURL* curlCtx = curl_easy_init();
    //char* outputurl = curl_easy_escape(curlCtx, url.c_str(), url.size());
    curl_easy_setopt(curlCtx, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curlCtx, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curlCtx, CURLOPT_WRITEFUNCTION, callbackfunction);
    curl_easy_setopt(curlCtx, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode rc = curl_easy_perform(curlCtx);
    if (rc)
    {
        printf("!!! Failed to download: %s\n", url);
        return "";
    }

    long res_code = 0;
    curl_easy_getinfo(curlCtx, CURLINFO_RESPONSE_CODE, &res_code);
    if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK))
    {
        printf("!!! Response code: %d\n", res_code);
        return "";
    }

    curl_easy_cleanup(curlCtx);

    fclose(fp);

    return CompleteFilePath;
}