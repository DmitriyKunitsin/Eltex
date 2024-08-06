#include "market.h"

void initialize_shops(Shop *shops) {
  for (int i = 0; i < NUM_SHOPS; ++i) {
    shops[i].stock = rand() % MAX_STOCK + 1;
    pthread_mutex_init(&shops[i].mutex, NULL);
  }
}
void create_loaders(pthread_t *loaders, CustomerAndLoaderShopData *data,
                    Shop *shops) {
  for (int i = 0; i < NUM_LOADERS; ++i) {
    data[i].loader.id = i + 1;
    data[i].loader.stock_to_add = LOAD_AMOUNT;
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
    if (customer->need <= 0) {
      printf("Покупатель %d с нулевой потребностью не заходит в магазин\n",
             customer->id);
      return;
    }
    if (pthread_mutex_trylock(&shops[i].mutex) == 0) {
      printf("Покупатель %d заходит в магазин %d с потребностью %d\n",
             customer->id, i, customer->need);
      if (shops[i].stock > 0) {
        int purchase_amount =
            (customer->need > shops[i].stock) ? shops[i].stock : customer->need;
        customer->need -= purchase_amount;
        shops[i].stock -= purchase_amount;
        printf("Остаток магазина %d = %d\n", i, shops[i].stock);
        if (customer->need > 0) {
          printf(
              "Покупатель %d взял %d товара, полностью потребности не "
              "удовлетворены, идёт в следующий магазин\n",
              customer->id, purchase_amount);
        } else {
          printf(
              "\033[35mПокупатель %d взял %d товара, потребности "
              "удовлетворены\n\033[0m",
              customer->id, purchase_amount);
        }
      } else {
        printf("Магазин %d пуст, покупатель %d идёт в следующий\n", i,
               customer->id);
      }
      printf(
          "Покупатель %d, выходит из магазина %d, создал очередь на входе...\n",
          customer->id, i);
      sleep(2);
      pthread_mutex_unlock(&shops[i].mutex);
    }
  }
}
void *customer(void *arg) {
  CustomerAndLoaderShopData *data = (CustomerAndLoaderShopData *)arg;
  Customer *customer = &data->customer;
  Shop *shops = data->shops;

  while (customer->need > 0) {
    if (customer->need > 0) {
      attempt_purchase(customer, shops);  /// попытка купить
    } else {
      break;
    }
  }
  get_static_count(1, shops);

  printf("Покупатель %d удовлетворил свои потребности, уходит с магазинов\n",
         customer->id);
  pthread_exit(NULL);
}

void add_strock_into_shop(Loader *loader, Shop *shops) {
  for (int i = 0; i < NUM_SHOPS; ++i) {
    if (shops[i].stock < MIN_STOCK) {
      if (pthread_mutex_lock(&shops[i].mutex) == 0) {
        shops[i].stock += loader->stock_to_add;
        printf(
            "\033[36mГрузчик %d заходит в магазин %d и пополняет его запасы на "
            "%d, "
            "всего в магазине %d\n\033[0m",
            loader->id, i, LOAD_AMOUNT, shops[i].stock);
        printf("Магазин %d, пополнении запасов...\n", i);
        sleep(1);
        pthread_mutex_unlock(&shops[i].mutex);
      }
    } else {
      // printf("Грузчик %d Магазин %d не нужно пополнять, перекур...\n",
      //        loader->id, i);
    }
  }
}

int get_static_count(int is_customer, Shop *shop) {
  static int count_satifaction_customer = 0;
  int current_val = 0;
  if (is_customer) {  /// если покупатель
    pthread_mutex_lock(&shop->mutex);
    count_satifaction_customer += 1;
    current_val = count_satifaction_customer;
    pthread_mutex_unlock(&shop->mutex);
  } else {                                           /// если грузчик
    if (pthread_mutex_trylock(&shop->mutex) == 0) {  /// если не занято
      current_val = count_satifaction_customer;
      pthread_mutex_unlock(&shop->mutex);
    }
  }
  return current_val;
}
void *loader(void *arg) {
  CustomerAndLoaderShopData *data = (CustomerAndLoaderShopData *)arg;
  Loader *loader = &data->loader;
  Shop *shops = data->shops;
  int stifaction_customer = get_static_count(0, shops);
  while (1) {
    if (stifaction_customer >= NUM_CUSTOMERS) {
      printf(
          "Грузчик %d : Все покупатели удовлетворили свои потребности, смена "
          "окончена...\n",
          loader->id);
      break;
    }
    stifaction_customer = get_static_count(0, shops);
    if (stifaction_customer < NUM_CUSTOMERS) {
      add_strock_into_shop(loader, shops);
    }
  }
  pthread_exit(NULL);
}

void exit_threads(Shop *shops) {
  for (int i = 0; i < NUM_SHOPS; ++i) {
    pthread_mutex_destroy(&shops[i].mutex);
  }
}

void create_threads(pthread_t *customers, pthread_t *loaders,
                    CustomerAndLoaderShopData *data, Shop *shops) {
  create_loaders(loaders, data, shops);
  create_customers(customers, data, shops);
}

void join_threads(pthread_t *customers, pthread_t *loaders) {
  for (int i = 0; i < NUM_CUSTOMERS; ++i) {
    pthread_join(customers[i], NULL);
  }
  for (int i = 0; i < NUM_LOADERS; ++i) {
    pthread_join(loaders[i], NULL);
  }
}