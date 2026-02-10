#include <ncurses.h>
#include <string>
#include <vector>

struct Node {
    int y, x, h, w;
    std::string label;

    void render_safe(std::string data) {
    // 1. Cleansing area konten dengan presisi agar tidak menghapus garis pembatas
    for (int i = 1; i < h; i++) {
        // x + 1 agar tidak menghapus garis kiri
        // w - 1 agar tidak menyentuh garis kanan (mid_x atau COLS)
        mvhline(y + i, x + 1, ' ', w - 1); 
    }

    // 2. Redraw Label (Sebagai penanda identitas node)
    mvprintw(y, x + 2, " %s ", label.c_str());

    // 3. Bounding Box Enforcement (Truncate)
    // -4 memberikan padding aman agar teks tidak mepet garis
    if (data.length() > (size_t)(w - 4)) {
        data = data.substr(0, w - 7) + "...";
    }

    // 4. Output Data & Push ke layar
    mvprintw(y + 1, x + 2, "%s", data.c_str());
    refresh(); 
}
};

// --- FIX 1: Pindahkan ke Global Scope agar bisa diakses Module luar ---
Node windows[6];

int main() {
    initscr(); noecho(); curs_set(0);

    int h_height = 3;
    int mid_x = COLS / 2;
    int r_w = COLS - mid_x;
    int r_h_node = (LINES - h_height) / 3;

    // --- INISIALISASI PEMBAGIAN SLOT (Model 1) ---
    windows[0] = {0, 0, h_height, COLS, "BLACK PEARL CONTROL v1.0"};
    windows[1] = {h_height + 1, 0, (LINES-h_height)/2, mid_x, "GUIDELINES"};
    windows[2] = {windows[1].y + windows[1].h, 0, (LINES - (windows[1].y + windows[1].h)), mid_x, "TERMINAL"};
    windows[3] = {h_height + 1, mid_x, r_h_node, r_w, "ZEROTRUST INTEL"};
    windows[4] = {windows[3].y + r_h_node, mid_x, r_h_node, r_w, "SERVICES & CONTAINERS"};
    windows[5] = {windows[4].y + r_h_node, mid_x, (LINES - (windows[4].y + r_h_node)), r_w, "ENV INFO"};

    // --- DRAWING STATIC STRUCTURE (Sasis/Dermaga) ---
    mvhline(h_height, 0, ACS_HLINE, COLS);
    mvvline(h_height + 1, mid_x, ACS_VLINE, LINES - h_height);
    mvhline(windows[1].y + windows[1].h, 0, ACS_HLINE, mid_x);
    mvhline(windows[3].y + windows[3].h, mid_x + 1, ACS_HLINE, r_w);
    mvhline(windows[4].y + windows[4].h, mid_x + 1, ACS_HLINE, r_w);

    // --- INITIAL TEST INJECTION ---
    windows[0].render_safe("User: Capt | Status: Ready");
    
    // Program akan menunggu di sini. 
    // Dalam tahap selanjutnya, getch() diganti dengan loop monitoring.
    getch(); 
    endwin();
    return 0;
}
