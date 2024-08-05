#ifndef MARKET_H_
#define MARKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_SHOPS 5
#define NUM_CUSTOMERS 5
#define NUM_LOADERS 3
#define MAX_NEED 1000
#define MAX_STOCK 25000
#define MIN_STOCK 15000
#define LOAD_AMOUNT 5000

/**
 * @brief Структура данных магазина
 */
typedef struct {
    int stock;
    pthread_mutex_t mutex;
}Shop;
/**
 * @brief Структура данных покупателя
 */
typedef struct {
    int id;
    int need;
}Customer;

/**
 * @brief Структура данных грузчиков
 */
typedef struct
{
    int id;
    int stock_to_add;
}Loader;

// typedef struct {
//     Shop *shops;
// }LoaderShopData;

typedef struct
{
    Loader loader;
    Customer customer; /// Информация о покупателе
    Shop *shops; /// Указатель на массив магазинов
    int satifaction_customers;
}CustomerAndLoaderShopData;

/**
 * @brief Инициализация магазинов
 */
void initialize_shops(Shop *shops);
/**
 * @brief Создание потоков покупателей
 */
void create_customers(pthread_t *customers,CustomerAndLoaderShopData *data ,Shop *shops);
/**
 * @brief Попытка покупки товара в магазине
 */
void attempt_purchase(Customer *customer, Shop *shops);
/**
 * @brief Логика покупателя
 */
void *customer(void *arg);
/**
 * @brief Создание потоков грузчиков
 */
void create_loaders(pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops);
/**
 * @brief Пополнение полок магазина
 */
void add_strock_into_shop(Loader *loader, Shop *shops);
/**
 * @brief Логика работы грузчиков
 */
void *loader(void *arg);

/**
 * @brief Создание потоков грузчиков и покупателей
 */
void create_threads(pthread_t *customers, pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops);
/**
 * @brief Ожидание окончания потоков грузчиков и покупателей
 */
void join_threads(pthread_t *customers, pthread_t *loaders);

#endif