#pragma once
#include <string>
#include <vector>
#include <map>

struct VideoItem;
void InitNetwork(const std::string& server_url);
std::vector<VideoItem> SearchVideos(const std::string& query, const std::string& account_id);
std::string GetStreamURL(const std::string& video_id, const std::string& account_id);
void LoginAccount();
void SwitchAccount(const std::string& account_id);
std::vector<std::string> ListAccounts();