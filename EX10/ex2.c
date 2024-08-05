#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTS 1000

int counter = 0;

pthread_mutex_t counter_mutex;

void* increment_counter(void* threadid) {
    long tid = (long)threadid;
    
    for (int i = 0; i < INCREMENTS; i++) {
        pthread_mutex_lock(&counter_mutex);
        counter++; 
        pthread_mutex_unlock(&counter_mutex);
    }

    printf("Поток #%ld завершил инкременты.\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    // Инициализация мьютекса
    pthread_mutex_init(&counter_mutex, NULL);

    // Создание потоков
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Главный поток: создаю поток #%ld\n", t);
        rc = pthread_create(&threads[t], NULL, increment_counter, (void*)t);
        if (rc) {
            printf("Ошибка: не удалось создать поток %d\n", rc);
            exit(-1);
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Финальный счетчик: %d\n", counter);

    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
