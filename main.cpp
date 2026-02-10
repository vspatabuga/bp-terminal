#include <ncurses.h>
#include <unistd.h>
#include <string>
#include "layout.h"

// Deklarasi fungsi dari module dan engine
void init_terminal_module();
void update_terminal_input(int ch);
void render_terminal_output();
void draw_layout_structure(int tab);

int main() {
    // --- 1. SETUP NCURSES ---
    initscr();
    noecho();
    curs_set(0);          // Sembunyikan kursor hardware
    nodelay(stdscr, TRUE); // Non-blocking input
    keypad(stdscr, TRUE);  // Aktifkan F1, F2, Arrow keys

    // --- 2. SETUP TMUX SESSION ---
    init_terminal_module();

    int current_tab = 1;
    bool is_running = true;

    // --- 3. ORCHESTRATION LOOP ---
    while (is_running) {
        int ch = getch();

        // Logika Kontrol (Tab Switching & Exit)
        if (ch == 27) is_running = false; // ESC untuk Exit
        if (ch == KEY_F(1)) current_tab = 1;
        if (ch == KEY_F(2)) current_tab = 2;

        // Distribusi Input ke Tmux (Hanya jika ada input)
        if (ch != ERR) {
            update_terminal_input(ch);
        }

        // Sinkronisasi Sasis (Drawing Phase)
        draw_layout_structure(current_tab);

        // Injeksi Data ke Monitor
        windows[0].render_safe("CAPT: PATABUGA | BLACK PEARL COMMAND CENTER");
        
        // Render Output Terminal dari Tmux ke Monitor Index 2
        render_terminal_output();

        // Contoh Pengisian Monitor Lain secara Statis (Sementara)
        if (current_tab == 1) {
            windows[3].render_safe("STATUS: TUNNEL ACTIVE - SG-01");
            windows[4].render_safe("PES: 1.000.000 NODES ONLINE");
            windows[5].render_safe("CPU: STABLE | MEM: OPTIMAL");
        }

        refresh();

        // --- PENDINGIN LAPTOP (Throttle) ---
        // 50ms = 20 FPS. Sangat cukup untuk TUI dan CPU tetap dingin.
        usleep(50000); 
    }

    // --- 4. CLEANUP ---
    // Pastikan mematikan sesi tmux agar tidak membebani sistem setelah keluar
    system("tmux kill-session -t blackpearl");
    endwin();

    return 0;
}
