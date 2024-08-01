#include "string.h"

int main() {

    write_file();
    char *string = read_file();
    if (string != NULL) {
        printf("%s", string);
        free(string);
    }
    return 0;
}

void write_file() {
    FILE *file = fopen(FILE_NAME, "w");
     if (file == NULL) {
        perror("Ошибка открытия файла");
    }

    fprintf(file, "String from file");

    fclose(file);


}

int realloc_string(char *string, int *size) {
    *size *= 2;
    char *temp = realloc(string, *size);
    if (temp == NULL) {
        perror("Ошибка realloc");
        return 0;
    }
    string = temp;
    free(temp);
    return *size; 
}
char *read_file() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return NULL; 
    }

    int size = 100;
    char *string = (char *)calloc(size, sizeof(char));
     if (string == NULL) {
        perror("Ошибка выделения памяти");
        fclose(file);
        return NULL; 
    }

    int ch; 
    int i = 0;
    
    while((ch = fgetc(file)) != EOF) {
        if (i >= size - 1) { // Проверка на переполнение
            size = realloc_string(string, &size);
            if (size == 0) {
                free(string); // Освобождаем память в случае ошибки
                fclose(file);
                return NULL; // Возвращаем NULL в случае ошибки
            }
        }
        string[i++] = ch; // Записываем символ в строку
    }
    
    string[i] = '\0';
    fclose(file);
    return string;
}