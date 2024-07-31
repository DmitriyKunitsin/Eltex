#include "../inc/back.h"

void init_panel(Panel *panel, const char *path) {
  int lenght = strlen(path);
  panel->path = (char *)calloc(lenght + 1, sizeof(char));
  strncpy(panel->path, path, lenght);
  panel->path[lenght] = '\0';  // Добавляю завершающий нулевой символ
  panel->count = 0;
  panel->selected = 0;

  DIR *dir = opendir(path);
  if (dir == NULL) {
    perror("opendir");
    return;
  }
  struct dirent *entry;
  int count_files = 1024;
  panel->files = (char **)calloc(count_files + 1, sizeof(char *));
  while ((entry = readdir(dir)) != NULL) {
    if (count_files <= panel->count) {
      count_files = resize_panel(panel, count_files);
    }
    lenght = strlen(entry->d_name);
    panel->files[panel->count] = (char *)calloc(lenght + 1, sizeof(char));
    strcpy(panel->files[panel->count], entry->d_name);
    panel->count++;
  }
  closedir(dir);
}
int resize_panel(Panel *panel, int count_files) {
  count_files = 2 * count_files;
  panel->files = realloc(panel->files, sizeof(char *) * count_files);
  return count_files;
}

void free_panel(Panel *panel) {
  for (int i = 0; i < panel->count; ++i) {
    free(panel->files[i]);
  }
  free(panel->path);
  free(panel->files);
  free(panel);
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
  snprintf(new_path, sizeof(new_path), "%s/%s", panel->path,
           panel->files[panel->selected]);
  if (strcmp(panel->files[panel->selected], ".") != 0 &&
      strcmp(panel->files[panel->selected], "..") != 0) {
    free_panel(panel);
    init_panel(panel, new_path);
  }
  free(new_path);
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
  DIR *dir = opendir(panel->files[panel->selected]);
  if (NULL == dir) {
    read_file(panel->files[panel->selected]);
  } else {
    change_directory(panel);
    closedir(dir);
  }
}