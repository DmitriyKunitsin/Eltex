
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ncurses.h>

#define MAX_FILES 100
#define MAX_PATH 1024

typedef struct {
    char *files[MAX_FILES];
    int count;
    int selected;
    char path[MAX_PATH];
} Panel;

Panel panels[2];
int currentPanel = 0;

void init_panel(Panel *panel, const char *path) {
    strncpy(panel->path, path, MAX_PATH);
    panel->count = 0;
    panel->selected = 0;

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL && panel->count < MAX_FILES) {
        panel->files[panel->count] = strdup(entry->d_name);
        panel->count++;
    }
    closedir(dir);
}

void free_panel(Panel *panel) {
    for (int i = 0; i < panel->count; i++) {
        free(panel->files[i]);
    }
}

void draw_panel(Panel *panel) {
    for (int i = 0; i < panel->count; i++) {
        if (i == panel->selected) {
            attron(A_REVERSE); // Highlight selected item
        }
        mvprintw(i, (currentPanel == 0 ? 0 : COLS / 2), "%s", panel->files[i]);
        if (i == panel->selected) {
            attroff(A_REVERSE);
        }
    }
}

void switch_panel() {
    currentPanel = !currentPanel;
}

void navigate(Panel *panel, int direction) {
    panel->selected += direction;
    if (panel->selected < 0) {
        panel->selected = 0;
    } else if (panel->selected >= panel->count) {
        panel->selected = panel->count - 1;
    }
}

void change_directory(Panel *panel) {
     char new_path[MAX_PATH];
    // Вычисляем необходимую длину
    size_t path_len = strlen(panel->path);
    size_t file_len = strlen(panel->files[panel->selected]);
    
    // Проверяем, поместится ли новый путь в буфер
    if (path_len + file_len + 2 > sizeof(new_path)) { // +2 для '/' и '\0'
        mvprintw(LINES - 1, 0, "Error: Path is too long");
        refresh();
        return; // Обработка ошибки
    }

    // Формируем новый путь
    snprintf(new_path, sizeof(new_path), "%s/%s", panel->path, panel->files[panel->selected]);

    if (strcmp(panel->files[panel->selected], ".") != 0 && strcmp(panel->files[panel->selected], "..") != 0) {
        free_panel(panel);
        init_panel(panel, new_path);
    }
}

int main() {
    initscr(); // Initialize ncurses
    noecho(); // Do not echo input
    keypad(stdscr, TRUE); // Enable special keys
    curs_set(0); // Hide cursor

    init_panel(&panels[0], "~/.");
    init_panel(&panels[1], "~/.");

    while (1) {
        clear();
        draw_panel(&panels[0]);
        draw_panel(&panels[1]);
        mvprintw(LINES - 1, 0, "Press 'Tab' to switch panels, 'Up'/'Down' to navigate, 'Enter' to open directory, 'q' to quit.");
        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                navigate(&panels[currentPanel], -1);
                break;
            case KEY_DOWN:
                navigate(&panels[currentPanel], 1);
                break;
            case '\t':
                switch_panel();
                break;
            case '\n':
                change_directory(&panels[currentPanel]);
                break;
            case 'q':
                goto end; // Exit the loop
        }
    }

end:
    free_panel(&panels[0]);
    free_panel(&panels[1]);
    endwin(); // End ncurses mode
    return 0;
}
