#include "market.h"

int main() {

   srand(time(NULL)); // Инициализация генератора случайных чисел

    Shop shops[NUM_SHOPS];
    CustomerAndLoaderShopData data[NUM_CUSTOMERS + NUM_LOADERS]; // Объединяем данные для покупателей и грузчиков
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t loaders[NUM_LOADERS];

    initialize_shops(shops); // Инициализация магазинов

    create_threads(customers, loaders, data, shops); // Создание потоков покупателей и грузчиков
    join_threads(customers, loaders); // Ожидание завершения потоков

    printf("Все покупатели обслужены и все потоки завершены.\n");

  return 0;
}