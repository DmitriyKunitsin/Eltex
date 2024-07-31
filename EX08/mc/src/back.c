#include "../inc/back.h"

void init_panel(Panel *panel, const char *path) {

  int lenght = strlen(path);
  panel->path = (char *)calloc(lenght + 1, sizeof(char));
  strncpy(panel->path, path, lenght);
  panel->path[lenght] = '\0'; // Добавляю завершающий нулевой символ
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
    // panel->files[panel->count] = strdup(entry->d_name);
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
