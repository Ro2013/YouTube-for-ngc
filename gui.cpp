#include "gui.h"
#include "network.h"
#include "input.h"
#include "video.h"
#include "history.h"
#include <string>
#include <vector>
#include <iostream>

// UI state
enum Page { HOME, SHORTS, PROFILE, SEARCH, VIDEO };
Page current_page = HOME;

struct VideoItem {
    std::string video_id;
    std::string title;
    std::string channel;
    std::string thumbnail;
};

std::vector<VideoItem> search_results;
std::string search_text;

void InitGUI() {
    // 初始化 UI, 左側欄, 搜尋框
}

void UpdateGUI() {
    // 根據 current_page 繪製 UI
    // 搜尋框啟用時顯示鍵盤
    if (IsKeyboardActive()) {
        // 顯示注音/英文鍵盤
    }

    // 搜尋結果往下滑動可載入更多
    if (IsScrollDown()) {
        LoadMoreSearchResults();
    }
}

void ShutdownGUI() {
    // 清理 UI 資源
}

// 新增完整定義
void LoadMoreSearchResults() {
    std::cout << "載入更多搜尋結果..." << std::endl;

    // 呼叫 network 模組取得更多搜尋結果
    std::vector<VideoItem> more_results = NetworkFetchMore(search_text);

    // 將新結果加入 search_results
    search_results.insert(search_results.end(), more_results.begin(), more_results.end());
}
