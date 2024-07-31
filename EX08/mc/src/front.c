#include "../inc/front.h"

void printTwoDir(Panel *panel, Panel *panelDouble) {
  clear();
  for (int i = 0; i < panel->count; ++i) {
    mvprintw(i + 1, 1, "%s", panel->files[i]);
    mvprintw(i + 1, SCREEN_SIZE_ALL_WIGHT / 2, "%s", panelDouble->files[i]);
  }
  refresh();
}