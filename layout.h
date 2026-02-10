#ifndef LAYOUT_H
#define LAYOUT_H

#include <ncurses.h>
#include <string>

struct Node {
    int y, x, h, w;
    std::string label;
    void render_safe(std::string data);
};

extern Node windows[6];

void draw_layout_structure(int tab);
void init_terminal_module();
void update_terminal_input(int ch);
void render_terminal_output();

#endif
