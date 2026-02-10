#include <ncurses.h>
#include <string>
#include <vector>
#include "layout.h"

// Inisialisasi global registry monitor sesuai Model 1 Capt
Node windows[6];

/**
 * IMPLEMENTASI RENDER_SAFE (Strict Isolation)
 * Tugas: Membersihkan area konten tanpa menyentuh garis sasis.
 */
void Node::render_safe(std::string data) {
    // 1. ISOLASI TOTAL: Bersihkan area dalam monitor saja
    // Menggunakan h-1 dan w-2 agar TIDAK menimpa garis pembatas kanan/bawah
    for (int i = 1; i < h - 1; i++) {
        mvhline(y + i, x + 1, ' ', w - 2);
    }

    // 2. SASIS PROTECTION: Gambar ulang label identitas di koordinat y
    // Ini memastikan garis horizontal atas tetap memiliki label pilar
    attron(A_BOLD);
    mvprintw(y, x + 2, " [%s] ", label.c_str());
    attroff(A_BOLD);

    // 3. BOUNDARY ENFORCEMENT: Cegah teks meluap (Truncate)
    // -4 memberikan padding aman dari garis pembatas vertikal
    if (data.length() > (size_t)(w - 4)) {
        data = data.substr(0, w - 7) + "...";
    }

    // 4. NATIVE INJECTION: Cetak data ke pilar (Baris y + 1)
    mvprintw(y + 1, x + 2, "%s", data.c_str());
}

/**
 * DRAW LAYOUT STRUCTURE (Model 1 Implementation)
 * Tugas: Membangun sasis statis yang kokoh.
 */
void draw_layout_structure(int tab) {
    int h_height = 3;       // Tinggi Header
    int mid_x = COLS / 2;   // Titik tengah horizontal
    int r_w = COLS - mid_x; // Lebar pilar kanan
    int r_h_node = (LINES - h_height) / 3; // Tinggi rata-rata pilar kanan

    // --- INISIALISASI MONITOR (Model 1) ---
    windows[0] = {0, 0, h_height, COLS, "BLACK PEARL CONTROL v1.0"};
    windows[1] = {h_height + 1, 0, (LINES - h_height) / 2, mid_x, "GUIDELINES"};
    windows[2] = {windows[1].y + windows[1].h, 0, (LINES - (windows[1].y + windows[1].h)), mid_x, "TERMINAL"};
    windows[3] = {h_height + 1, mid_x, r_h_node, r_w, "ZEROTRUST INTEL"};
    windows[4] = {windows[3].y + r_h_node, mid_x, r_h_node, r_w, "SERVICES & CONTAINERS"};
    windows[5] = {windows[4].y + r_h_node, mid_x, (LINES - (windows[4].y + r_h_node)), r_w, "ENV INFO"};

    // --- DRAWING STATIC CHASSIS (Dermaga) ---
    // Gunakan A_DIM agar garis tidak terlalu terang (Intelligence Aesthetic)
    attron(A_DIM);

    // Garis Header Horizontal
    mvhline(h_height, 0, ACS_HLINE, COLS);

    // Garis Vertikal Utama (Pilar Kiri & Kanan)
    mvvline(h_height + 1, mid_x, ACS_VLINE, LINES - h_height);

    // Garis Horizontal Kiri
    mvhline(windows[1].y + windows[1].h, 0, ACS_HLINE, mid_x);

    // Garis Horizontal Kanan
    mvhline(windows[3].y + windows[3].h, mid_x + 1, ACS_HLINE, r_w - 1);
    mvhline(windows[4].y + windows[4].h, mid_x + 1, ACS_HLINE, r_w - 1);

    attroff(A_DIM);
}
