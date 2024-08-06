#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

// Функция, выполняемая потоками
void* print_thread_index(void* threadid) {
  long tid = (long)threadid;
  printf("Поток #%ld запущен.\n", tid);
  pthread_exit(NULL);
}

int main() {
  pthread_t threads[NUM_THREADS];
  int rc;
  long t;

  for (t = 0; t < NUM_THREADS; t++) {
    printf("Главный поток: создаю поток #%ld\n", t);
    rc = pthread_create(&threads[t], NULL, print_thread_index, (void*)t);
    if (rc) {
      printf("Ошибка: не удалось создать поток %d\n", rc);
      exit(-1);
    }
  }

  for (t = 0; t < NUM_THREADS; t++) {
    pthread_join(threads[t], NULL);
  }

  printf("Все потоки завершены.\n");
  return 0;
}
