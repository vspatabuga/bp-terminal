#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "../layout.h"

void init_terminal_module() {
    // Membuat sesi tmux baru di latar belakang (detached)
    system("tmux kill-session -t blackpearl 2>/dev/null");
    system("tmux new-session -d -s blackpearl");
}

void render_terminal_output() {
    // "Memotret" 10 baris terakhir dari tmux
    FILE* pipe = popen("tmux capture-pane -t blackpearl -p | tail -n 10", "r");
    if (!pipe) return;

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    // Kirim hasil potret ke Monitor 2
    if (!result.empty()) {
        windows[2].render_safe(result);
    }
}

void update_terminal_input(int ch) {
    if (ch != ERR && ch != 0) {
        // Logika menembakkan karakter ke Tmux
        std::string cmd = "tmux send-keys -t blackpearl '" + std::string(1, (char)ch) + "'";
        if (ch == 10) cmd = "tmux send-keys -t blackpearl Enter";
        system(cmd.c_str());
    }
}
