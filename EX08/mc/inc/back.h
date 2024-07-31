#ifndef BACK_H_
#define BACK_H_

#include "mc.h"
#include "../inc/panel.h"

#define MAX_FILES 100
#define MAX_PATH 1024


int resize_panel(Panel *panel, int count_files);
void init_panel(Panel *panel, const char *path);
void free_panel(Panel *panel);

#endif