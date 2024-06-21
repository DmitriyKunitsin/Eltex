#include <stdio.h>

/*Вывести двоичное представление целого положительного числа,
используя битовые операции (число вводится с клавиатуры). */

int main() {
    int val = 0;
    printf("input value :");
    scanf("%d", &val);
    int size = (int)(sizeof(int) * 8);
    for(int i = size; i >= 0; --i) {
        printf("%d", (val >> i) & 1); 
        if (i % 8 == 0 && i != 0) {
            printf(",");
        }
    }
    printf("\n");

    return 0;
}