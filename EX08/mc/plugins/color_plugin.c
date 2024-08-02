#include "../inc/plugin.h"

COLOR_LIST *read_color_with_file() {
  char path[24];
  snprintf(path, sizeof(path), "%s%s", PLAGIN_PATH, FILE_NAME);
  FILE *file = fopen(path, "r");
  COLOR_LIST *color = malloc(2 * sizeof(COLOR_LIST));
  if (file == NULL) {
    color[0] = DEFAULT_ONE_COLOR;
    color[1] = DEFAULT_SECOND_COLOR;
    return color;
  }
  char color_name[20];
  int color_value;
  int i = 0;

  while (fscanf(file, "%s %d", color_name, &color_value) == 2 && i < 2) {
    if (strcmp(color_name, "CYAN") == 0) {
      color[i++] = CYAN;
    } else if (strcmp(color_name, "BLUE") == 0) {
      color[i++] = BLUE;
    } else if (strcmp(color_name, "GREEN") == 0) {
      color[i++] = GREEN;
    } else if (strcmp(color_name, "RED") == 0) {
      color[i++] = RED;
    } else if (strcmp(color_name, "YELLOW") == 0) {
      color[i++] = YELLOW;
    } else if (strcmp(color_name, "BLACK") == 0) {
      color[i++] = BLACK;
    } else if (strcmp(color_name, "WHITE") == 0) {
      color[i++] = WHITE;
    }
  }

  fclose(file);

  // Если не удалось считать два цвета, используем значения по умолчанию
  if (i < 2) {
    color[0] = DEFAULT_ONE_COLOR;
    color[1] = DEFAULT_SECOND_COLOR;
  }

  return color;
}

void on_color_scheme() {
  start_color();
  COLOR_LIST *color_list = read_color_with_file();
  init_pair(1, color_list[0], color_list[1]);
  free(color_list);
  attron(COLOR_PAIR(1));
}
