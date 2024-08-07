#include "../inc/back.h"

void init_panel(Panel *panel, const char *path) {
  int lenght = strlen(path);
  panel->path = (char *)calloc(lenght + 1, sizeof(char));
  strcpy(panel->path, path);
  panel->path[lenght] = '\0';  // Добавляю завершающий нулевой символ
  panel->count = 0;
  panel->selected = 0;

  DIR *dir = opendir(panel->path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
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
  int size_full_path = path_len + file_len;
  char new_path[size_full_path + 1];

  // новый путь
  snprintf(new_path, path_len + file_len + 2, "%s/%s", panel->path,
           panel->files[panel->selected]);
  if (strcmp(panel->files[panel->selected], ".") != 0 &&
      strcmp(panel->files[panel->selected], "..") != 0) {
    free_panel(panel);
    init_panel(panel, new_path);
  }
}

void back_directiry(Panel *panel) {
  int path_len = strlen(panel->path);
  // последний символ '/' в пути
  char *last_slash = strrchr(panel->path, '/');
  if (last_slash != NULL && last_slash != panel->path) {
    int back_path_len = last_slash - panel->path;  // Длина нового пути
    char back_path[back_path_len];
    strncpy(back_path, panel->path, back_path_len);
    back_path[back_path_len] = '\0';

    free_panel(panel);
    init_panel(panel, back_path);
  }
}
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
      back_directiry(panel);
    } else {
      int path_len = strlen(panel->path);
      int file_len = strlen(panel->files[panel->selected]);
      int size_full_path = path_len + file_len;
      char full_path[size_full_path + 1];

      snprintf(full_path, path_len + file_len + 2, "%s/%s", panel->path,
               panel->files[panel->selected]);
      DIR *dir = opendir(full_path);
      if (dir == NULL) {
        read_file(full_path);  // открыть как файл
      } else {
        closedir(dir);
        change_directory(panel);
      }
    }
  }
}

char *get_root_path() {
  char *root_path = malloc(100);
  if (root_path == NULL) {
    perror("Не удалось выделить память");
    return NULL;
  }
  if (getcwd(root_path, 100) == NULL) {
    perror("Не удалось получить текущую директорию");
    free(root_path);
    return NULL;
  }
  return root_path;
}