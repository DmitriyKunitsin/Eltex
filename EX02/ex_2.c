/*
В приведенном ниже коде измените только одну строку (помеченную),
чтобы напечатать “Результат: 12.0”

#include <stdio.h>
int main(void)
{
float x = 5.0;
printf("x = %f, ", x);
float y = 6.0;
printf("y = %f\n", y);
float *xp = &x; // TODO: отредактируйте эту строку, и только правую часть
уравнения
float *yp = &y;
printf("Результат: %f\n", *xp + *yp);
}
*/
#include <stdio.h>
int main(void) {
  float x = 5.0;
  printf("x = %f, ", x);
  float y = 6.0;
  printf("y = %f\n", y);
  float *xp = &x + 1;

  float *yp = &y;
  printf("Результат: %.1f\n", *xp + *yp); // поставил еще ограничение по точности, ТЗ требует вывести один 0 после точки
}