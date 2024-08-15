#include "front.h"

void init_windows(WINDOW **chat_win, WINDOW **user_win, WINDOW **input_win) {
    *chat_win = newwin(20, 50, 0, 0);
    *user_win = newwin(20, 20, 0, 50);
    *input_win = newwin(3, 70, 20, 0);

    box(*chat_win, 0, 0);
    box(*user_win, 0, 0);
    box(*input_win, 0, 0);

    wrefresh(*chat_win);
    wrefresh(*user_win);
    wrefresh(*input_win);
}

void display_chat(Chat_state *state,WINDOW *chat_win) {
    werase(chat_win);
    box(chat_win, 0, 0);

    for (int i = 0; i < state->chat_line_count; i++) {
        mvwprintw(chat_win, i + 1, 1, "%s", state->chat[i]);
    }

    wrefresh(chat_win);
}

void display_users(Chat_state *state,WINDOW *user_win) {
    werase(user_win);
    box(user_win, 0, 0);

    for (int i = 0; i < state->user_count; i++) {
        mvwprintw(user_win, i + 1, 1, "%s", state->users[i]);
    }

    wrefresh(user_win);
}

void add_chat_message(Chat_state *state,const char *msg) {
    if (state->chat_line_count < MAX_CHAT_LINES) {
        strncpy(state->chat[state->chat_line_count], msg, MAX_MSG_LENGTH - 1);
        state->chat[state->chat_line_count][MAX_MSG_LENGTH - 1] = '\0';  // Завершаем строку
        state->chat_line_count++;
    } else {
        // Сдвигаем сообщения вверх
        for (int i = 1; i < MAX_CHAT_LINES; i++) {
            strncpy(state->chat[i - 1], state->chat[i], MAX_MSG_LENGTH);
        }
        strncpy(state->chat[MAX_CHAT_LINES - 1], msg, MAX_MSG_LENGTH - 1);
        state->chat[MAX_CHAT_LINES - 1][MAX_MSG_LENGTH - 1] =
            '\0';  // Завершаем строку
    }
}

void add_user(Chat_state *state,const char *username) {
    if (state->user_count < MAX_USERS) {
        strncpy(state->users[state->user_count], username, sizeof(state->users[state->user_count]) - 1);
        state->users[state->user_count][sizeof(state->users[state->user_count]) - 1] =
            '\0';  // Завершаем строку
        state->user_count++;
    }
}