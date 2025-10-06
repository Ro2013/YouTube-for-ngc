#include "network.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

std::string g_server_url;

void InitNetwork(const std::string& server_url) {
    g_server_url = server_url;
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

static size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::vector<VideoItem> SearchVideos(const std::string& query, const std::string& account_id) {
    std::vector<VideoItem> results;
    CURL* curl = curl_easy_init();
    if (!curl) return results;

    std::string url = g_server_url + "/api/search";
    Json::Value req;
    req["query"] = query;
    req["account_id"] = account_id;
    Json::StreamWriterBuilder writer;
    std::string post_data = Json::writeString(writer, req);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        Json::CharReaderBuilder reader;
        Json::Value json_resp;
        std::string errs;
        std::istringstream s(response_string);
        if (Json::parseFromStream(reader, s, &json_resp, &errs)) {
            auto items = json_resp["results"];
            for (auto& it : items) {
                VideoItem v;
                v.video_id = it["video_id"].asString();
                v.title = it["title"].asString();
                v.channel = it["channel"].asString();
                v.thumbnail = it["thumbnail"].asString();
                results.push_back(v);
            }
        }
    }
    curl_easy_cleanup(curl);
    return results;
}

std::string GetStreamURL(const std::string& video_id, const std::string& account_id) {
    std::string stream_url;
    CURL* curl = curl_easy_init();
    if (!curl) return "";

    std::string url = g_server_url + "/api/play";
    Json::Value req;
    req["video_id"] = video_id;
    req["account_id"] = account_id;
    Json::StreamWriterBuilder writer;
    std::string post_data = Json::writeString(writer, req);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    std::string response_string;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

    CURLcode res = curl_easy_perform(curl);
    if (res == CURLE_OK) {
        Json::CharReaderBuilder reader;
        Json::Value json_resp;
        std::string errs;
        std::istringstream s(response_string);
        if (Json::parseFromStream(reader, s, &json_resp, &errs)) {
            stream_url = json_resp["stream_url"].asString();
        }
    }
    curl_easy_cleanup(curl);
    return stream_url;
}