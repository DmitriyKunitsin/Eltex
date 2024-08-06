#include "market.h"

int main() {
  srand(time(NULL));  // Инициализация генератора случайных чисел

  Shop shops[NUM_SHOPS];
  CustomerAndLoaderShopData data[NUM_CUSTOMERS];
  pthread_t customers[NUM_CUSTOMERS];
  pthread_t loaders[NUM_LOADERS];

  initialize_shops(shops);

  create_threads(customers, loaders, data, shops);
  join_threads(customers, loaders);

  printf("Все покупатели обслужены и все потоки завершены.\n");

  exit_threads(shops);

  return 0;
}