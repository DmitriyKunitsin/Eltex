#include "../inc/plugin.h"

void on_color_scheme() {
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE);
     attron(COLOR_PAIR(1));
}