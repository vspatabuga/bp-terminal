#include <ncurses.h>

int main() {
    initscr();
    noecho();
    curs_set(0);

    // --- KALIBRASI LAYOUT ---
    int header_height = 3; 
    int mid_x = COLS / 2;
    int one_third_y = (LINES - header_height) / 3 + header_height;
    int two_third_y = ((LINES - header_height) / 3) * 2 + header_height;
    int mid_y_left = (LINES - header_height) / 2 + header_height;

    // --- 1. HEADER: Rata Kiri & Garis Pembatas ---
    // Teks berada di kiri (X=2) sesuai instruksi Anda
    mvprintw(1, 2, "BLACK PEARL CONTROL SYSTEM v1.0");
    
    // Garis pembatas horizontal antara header dan pilar
    mvhline(header_height, 0, ACS_HLINE, COLS); 

    // --- 2. PEMBATAS PILAR (50/50 - TMUX STYLE) ---
    // Garis Vertikal Utama (Pemisah Pilar Kiri & Kanan)
    mvvline(header_height + 1, mid_x, ACS_VLINE, LINES - header_height); 

    // Garis Horizontal Pilar Kiri (Pemisah Node 1 & 2)
    mvhline(mid_y_left, 0, ACS_HLINE, mid_x);

    // Garis Horizontal Pilar Kanan (Pemisah Node 3, 4, & 5)
    mvhline(one_third_y, mid_x + 1, ACS_HLINE, COLS - mid_x);
    mvhline(two_third_y, mid_x + 1, ACS_HLINE, COLS - mid_x);

    // Garis Vertikal Node 4 (Pemisah Services & Containers)
    int node4_height = two_third_y - one_third_y;
    mvvline(one_third_y + 1, mid_x + (COLS - mid_x)/2, ACS_VLINE, node4_height - 1);

    // --- 3. PENEMPATAN KONTEN (NATIVE TEXT) ---
    // Pilar Kiri
    mvprintw(header_height + 1, 2, "[GUIDELINES]");
    mvprintw(mid_y_left + 1, 2, "[TERMINAL]");

    // Pilar Kanan
    mvprintw(header_height + 1, mid_x + 2, "[ZEROTRUST INTEL]");
    mvprintw(one_third_y + 1, mid_x + 2, "[BP SERVICES]");
    mvprintw(one_third_y + 1, mid_x + (COLS - mid_x)/2 + 2, "[CONTAINERS]");
    mvprintw(two_third_y + 1, mid_x + 2, "[ENV INFO]");

    refresh();
    getch();
    endwin();
    return 0;
}
