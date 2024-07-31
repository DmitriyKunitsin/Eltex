#ifndef PLUGIN_H_
#define PLUGIN_H_

#include "mc.h"
#include <dlfcn.h>
// #include <ncurses.h>


void init_ncurses_plugins(void **handle, void (**apply_color_scheme)());
void off_color_sheme();

#endif