#include <ncurses.h>
#include <string>
#include <vector>
#include "layout.h"

// Mempertahankan Global Scope sesuai permintaan Capt
Node windows[6];

/**
 * LOGIKA RENDER_SAFE (FIXED)
 * Memastikan konten dibersihkan tanpa merusak garis sasis.
 */
void Node::render_safe(std::string data) {
    // 1. Cleansing area konten 
    // Menggunakan h-1 dan w-1 agar tidak menabrak garis pembatas layout
    for (int i = 1; i < h; i++) {
        mvhline(y + i, x + 1, ' ', w - 1); 
    }

    // 2. Redraw Label (Identitas pilar)
    // Ditulis di koordinat y (garis pembatas atas)
    attron(A_BOLD);
    mvprintw(y, x + 2, " [%s] ", label.c_str());
    attroff(A_BOLD);

    // 3. Bounding Box Enforcement
    if (data.length() > (size_t)(w - 4)) {
        data = data.substr(0, w - 7) + "...";
    }

    // 4. Output Data & Refresh
    mvprintw(y + 1, x + 2, "%s", data.c_str());
    // Refresh dipindahkan ke main loop untuk efisiensi, 
    // tapi tetap saya biarkan di sini jika Capt ingin instan.
}

/**
 * DRAW LAYOUT STRUCTURE (Final Model 1)
 * Hanya menggambar garis sasis (static structure)
 */
void draw_layout_structure(int tab) {
    int h_height = 3;
    int mid_x = COLS / 2;
    int r_w = COLS - mid_x;
    int r_h_node = (LINES - h_height) / 3;

    // --- INISIALISASI PEMBAGIAN SLOT (Persis Model 1 Capt) ---
    windows[0] = {0, 0, h_height, COLS, "BLACK PEARL CONTROL v1.0"};
    windows[1] = {h_height + 1, 0, (LINES - h_height) / 2, mid_x, "GUIDELINES"};
    windows[2] = {windows[1].y + windows[1].h, 0, (LINES - (windows[1].y + windows[1].h)), mid_x, "TERMINAL"};
    windows[3] = {h_height + 1, mid_x, r_h_node, r_w, "ZEROTRUST INTEL"};
    windows[4] = {windows[3].y + r_h_node, mid_x, r_h_node, r_w, "SERVICES & CONTAINERS"};
    windows[5] = {windows[4].y + r_h_node, mid_x, (LINES - (windows[4].y + r_h_node)), r_w, "ENV INFO"};

    // --- DRAWING SASIS (Hanya Garis) ---
    // Gunakan attron(A_DIM) agar garis terlihat seperti dashboard intelijen
    attron(A_DIM);
    
    // Garis Horizontal Utama (Header)
    mvhline(h_height, 0, ACS_HLINE, COLS);
    
    // Garis Vertikal Tengah
    mvvline(h_height + 1, mid_x, ACS_VLINE, LINES - h_height);
    
    // Garis Horizontal Kiri (Bawah Guidelines)
    mvhline(windows[1].y + windows[1].h, 0, ACS_HLINE, mid_x);
    
    // Garis Horizontal Kanan (Pemisah Intel, Services, Env)
    mvhline(windows[3].y + windows[3].h, mid_x + 1, ACS_HLINE, r_w - 1);
    mvhline(windows[4].y + windows[4].h, mid_x + 1, ACS_HLINE, r_w - 1);
    
    attroff(A_DIM);
}
