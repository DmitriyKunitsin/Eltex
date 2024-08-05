#include "market.h"

void initialize_shops(Shop *shops) {
  for (int i = 0; i < NUM_SHOPS; ++i) {
    shops[i].stock = rand() % MAX_STOCK + 1;
    pthread_mutex_init(&shops[i].mutex, NULL);
  }
}
void create_loaders(pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops) {
    for(int i = 0; i < NUM_LOADERS; ++i) {
        data[i].loader.id = i + 1;
        data[i].loader.stock_to_add =  LOAD_AMOUNT;
        data[i].shops = shops;
        pthread_create(&loaders[i], NULL, loader, &data[i]);
    }
}

void create_customers(pthread_t *customers, CustomerAndLoaderShopData *data,
                      Shop *shops) {
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    data[i].customer.id = i + 1;
    data[i].customer.need = rand() % MAX_NEED + 1;
    data[i].shops = shops;
    pthread_create(&customers[i], NULL, customer, &data[i]);
  }
}
void attempt_purchase(Customer *customer, Shop *shops) {

  for (int i = 0; i < NUM_SHOPS; ++i) {
    if (pthread_mutex_trylock(&shops[i].mutex) == 0) {
      printf("Покупатель %d заходит в магазин %d с потребностью %d\n",
             customer->id, i, customer->need);
      if (shops[i].stock > 0) {
        int purchase_amount =
            (customer->need > shops[i].stock) ? shops[i].stock : customer->need;
        customer->need -= purchase_amount;
        shops[i].stock -= purchase_amount;
        if (customer->need > 0) {
          printf("Покупатель %d взял %d товара, полностью потребности не "
                 "удовлетворены, идёт в следующий магазин\n",
                 customer->id, purchase_amount);
        } else {
          printf("Покупатель %d взял %d товара, потребности удовлетворены\n",
                 customer->id, purchase_amount);
        }
      } else {
        printf("Магазин %d пуст, покупатель %d идёт в следующий\n", i,
               customer->id);
      }
      printf("Покупатель %d, выходит из магазина, создал очередь на входе...\n", customer->id);
      sleep(2);
      pthread_mutex_unlock(&shops[i].mutex);
    } else {
    //   printf("Магазин %d занят, покупатель %d идёт в следующий\n", i,
    //          customer->id);
    }
  }
}
void *customer(void *arg) {
  CustomerAndLoaderShopData *data = (CustomerAndLoaderShopData *)arg;
  Customer *customer = &data->customer;
  Shop *shops = data->shops;

  while (customer->need > 0) {
    attempt_purchase(customer, shops); // попытка купить
  }
  data->satifaction_customers += 1;
  printf("Покупатель %d удовлетворил свои потребности, уходит с магазинов\n",
         customer->id);
  pthread_exit(NULL);
}

void add_strock_into_shop(Loader *loader, Shop *shops) {
    for(int i = 0; i < NUM_SHOPS; ++i) {
        if(pthread_mutex_trylock(&shops[i].mutex) == 0) {
            if(shops[i].stock < MIN_STOCK) {
            shops[i].stock += loader->stock_to_add;
            printf("Грузчик %d заходит в магазин %d и пополняет его запасы на %d, всего в магазине %d\n",loader->id, i, LOAD_AMOUNT, shops[i].stock);
            printf("Магазин %d, пополнении запасов...\n", i);
            sleep(1);
            }
            pthread_mutex_unlock(&shops[i].mutex);
        } 
    }
}
void *loader(void *arg) {
  CustomerAndLoaderShopData *data = (CustomerAndLoaderShopData *)arg;
  Loader *loader = &data->loader;
  Shop *shops = data->shops;

  while (data->satifaction_customers != NUM_CUSTOMERS) //  пополняют пока магазин не обслужит всех гостей
  {
    add_strock_into_shop(loader, shops);
  }
  printf("Грузчик %d : Все покупатели удовлитворили свои потребности, смена окончаена...\n", loader->id);
  pthread_exit(NULL);
}

void create_threads(pthread_t *customers, pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops) {
    create_loaders(loaders, data, shops);
    create_customers(customers, data, shops);
    data->satifaction_customers = 0;
}

void join_threads(pthread_t *customers, pthread_t *loaders) {
    for (int i = 0; i < NUM_CUSTOMERS; ++i) {
        pthread_join(customers[i], NULL);
    }
    for (int i = 0; i < NUM_LOADERS; ++i) {
        pthread_join(loaders[i], NULL);
    }
}