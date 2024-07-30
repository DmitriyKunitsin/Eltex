#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_FILES 100
#define MAX_PATH 1024


int main() {
    initscr();/// Инициализация ncrses 
    noecho(); /// Отключить ввод в командную строку
    keypad(stdscr, TRUE); /// Включить специальные клавиши
    curs_set(0); /// спрятать курсор

    int ch = 'W';
    while (ch != 'q')
    {
        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            /// TODO : выделить вверх
            clear();
            mvprintw(10,10, "HELLO WORLD KEY_UP");

            break;
        case KEY_DOWN:
            /// TODO : выделить вниз
            clear();
            mvprintw(10,10, "BAY WORLD KEY_DOWN");

            break;
        case '\n':
            /// TODO : выбор, действие
            break;
        case '\t':
            /// TODO : TAB
            break;
        }
        refresh();
    }
    

    endwin();
    return 0;
}