#include "gui.h"
#include "network.h"
#include "input.h"
#include "video.h"
#include "history.h"

int main(int argc, char** argv) {
    // 初始化 SDL2 / libOGC / 控制器
    InitInput();
    InitGUI();
    InitNetwork("https://ngc-k22w.onrender.com");
    InitVideo();
    InitHistory();

    bool running = true;
    while (running) {
        PollInput();
        UpdateGUI();
        UpdateVideo();
        UpdateHistory();
        running = !IsExitRequested();
    }

    ShutdownVideo();
    ShutdownGUI();
    ShutdownInput();
    return 0;
}