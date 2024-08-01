#include "../inc/back.h"

void init_panel(Panel *panel, const char *path) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
  int lenght = strlen(path);
  panel->path = (char *)calloc(lenght + 1, sizeof(char));
  strncpy(panel->path, path, lenght);
  panel->path[lenght] = '\0';  // Добавляю завершающий нулевой символ
  panel->count = 0;
  panel->selected = 0;

  struct dirent *entry;
  int count_files = 1024;
  panel->files = (char **)calloc(count_files, sizeof(char *));
  lenght = strlen("...");
  panel->files[panel->count] = (char *)calloc(lenght + 1, sizeof(char));
  strcpy(panel->files[panel->count++],
         "...");  // TODO кнопка для перехода назад
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      if (count_files <= panel->count) {
        count_files = resize_panel(panel, count_files);
      }
      lenght = strlen(entry->d_name);
      panel->files[panel->count] = (char *)calloc(lenght + 1, sizeof(char));
      strcpy(panel->files[panel->count], entry->d_name);
      panel->count++;
    }
  }
  closedir(dir);
}
int resize_panel(Panel *panel, int count_files) {
  count_files = 2 * count_files;
  char **temp = realloc(panel->files, sizeof(char *) * count_files);
  if (temp == NULL) {
    return panel->count;
  }
  panel->files = temp;
  return count_files;
}

void free_panel(Panel *panel) {
  if (panel != NULL) {
    if (panel->files != NULL) {
      for (int i = 0; i < panel->count; i++) {
        free(panel->files[i]);  // Освобождаем каждую строку
      }
      free(panel->files);  // Освобождаем массив указателей
    }
    free(panel->path);  // Освобождаем путь
  }
}

void navigate_panel(Panel *panel, int dirrection) {
  panel->selected += dirrection;
  if (panel->selected < 0) {
    panel->selected = 0;
  } else if (panel->selected >= panel->count) {
    panel->selected = panel->count - 1;
  }
}
void switch_panel(int *selected_panel) { *selected_panel = !*selected_panel; }
void change_directory(Panel *panel) {
  int path_len = strlen(panel->path);
  int file_len = strlen(panel->files[panel->selected]);
  char *new_path = (char *)calloc((path_len + file_len), sizeof(char));

  // новый путь
  snprintf(new_path, path_len + file_len + 2, "%s/%s", panel->path,
           panel->files[panel->selected]);
  if (strcmp(panel->files[panel->selected], ".") != 0 &&
      strcmp(panel->files[panel->selected], "..") != 0) {
    free_panel(panel);
    init_panel(panel, new_path);
  }
  free(new_path);
}

void back_directiry(Panel *panel) {}
void read_file(const char *selectected_file) {
  FILE *file = fopen(selectected_file, "r");
  if (NULL == file) {
    return;
  }
  print_file(file);
  char ext = '\0';
  while (ext != 'q') {
    ext = getch();
  }
  fclose(file);
  clear();
}
void read_or_change(Panel *panel) {
  if (panel->count > 0) {
    if (0 == panel->selected) {  // выбрана кнопка назад
      int path_len = strlen(panel->path);

      // Находим последний символ '/' в пути
      char *last_slash = strrchr(panel->path, '/');
      if (last_slash != NULL && last_slash != panel->path) {
        // Создаем новый путь к родительской директории
        int back_path_len = last_slash - panel->path;  // Длина нового пути
        char *back_path = (char *)calloc(back_path_len + 1, sizeof(char));
        strncpy(back_path, panel->path, back_path_len);
        back_path[back_path_len] = '\0';  // Завершаем строку

        free_panel(panel);  // Освобождаем ресурсы текущей панели
        init_panel(panel, back_path);  // Инициализируем панель с новым путем

        free(back_path);  // Освобождаем память для back_path
      }
    } else {
      int path_len = strlen(panel->path);
      int file_len = strlen(panel->files[panel->selected]);
      char *full_path = (char *)calloc((path_len + file_len) + 1, sizeof(char));
      snprintf(full_path, path_len + file_len + 2, "%s/%s", panel->path,
               panel->files[panel->selected]);
      DIR *dir = opendir(full_path);
      if (dir == NULL) {
        read_file(full_path);  // открыть как файл
      } else {
        closedir(dir);
        change_directory(panel);
      }
      free(full_path);
    }
  }
}