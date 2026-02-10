#include <cstdio>
#include <iostream>
#include <string>
#include <pty.h>
#include <utmp.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "../layout.h"

// File Descriptor untuk mengontrol terminal asli
int master_fd;

/**
 * Inisialisasi Modul Terminal Langsung
 * Membelah proses dan menjalankan shell asli di dalam pilar.
 */
void init_terminal_module() {
    struct winsize ws;
    // Set ukuran terminal sesuai dimensi windows[2] di Model 1 Capt
    ws.ws_row = (unsigned short)windows[2].h - 2;
    ws.ws_col = (unsigned short)windows[2].w - 2;
    ws.ws_xpixel = 0;
    ws.ws_ypixel = 0;

    pid_t pid = forkpty(&master_fd, NULL, NULL, &ws);

    if (pid < 0) {
        perror("Forkpty Failed");
        return;
    }

    if (pid == 0) {
        // Proses Anak: Jalankan Shell Bash asli
        setenv("TERM", "xterm-256color", 1);
        execl("/bin/bash", "/bin/bash", NULL);
        _exit(1);
    }

    // Proses Induk: Atur master_fd agar tidak memblokir (Non-blocking)
    int flags = fcntl(master_fd, F_GETFL, 0);
    fcntl(master_fd, F_SETFL, flags | O_NONBLOCK);
}

/**
 * Render Output Terminal (Native Stream)
 * Membaca data langsung dari stream shell dan menampilkannya.
 */
void render_terminal_output() {
    char buffer[1024];
    // Membaca stream data dari master_fd terminal
    ssize_t bytes_read = read(master_fd, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::string raw_output(buffer);

        // Kirim data mentah ke monitor untuk diproses render_safe
        windows[2].render_safe(raw_output);
    }
}

/**
 * Update Input Terminal (Direct Write)
 * Menulis karakter keyboard langsung ke input stream shell.
 */
void update_terminal_input(int ch) {
    if (ch == ERR || ch == 0) return;

    // Menangani tombol khusus secara manual untuk stream PTY
    if (ch == 10) {
        // Enter diterjemahkan ke Line Feed
        char n = '\n';
        write(master_fd, &n, 1);
    }
    else if (ch == KEY_BACKSPACE || ch == 127) {
        // Karakter Backspace
        char b = '\b';
        write(master_fd, &b, 1);
    }
    else {
        // Kirim karakter biasa
        char c = (char)ch;
        write(master_fd, &c, 1);
    }
}
