#ifndef MARKET_H_
#define MARKET_H_

/**
 * @file market.h
 * @brief Заголовочный файл для симуляции рынка с магазинами, покупателями и загрузчиками.
 *
 * Этот файл содержит определения необходимых структур, констант и 
 * функций для реализации многопоточной симуляции рынка, где 
 * магазины имеют запасы товаров, а покупатели и загрузчики 
 * взаимодействуют с этими магазинами.
 *
 * @author Дмитрий Куницин
 * @version 1.0
 * @date 2024-08-06
 *
 * @note Данный проект предназначен для изучения основ многопоточного 
 * программирования на языке C с использованием библиотек pthread.
 * 
 * @warning Убедитесь, что у вас достаточно ресурсов системы для 
 * запуска большого количества потоков( указанного вами в макросах ), чтобы избежать проблем с 
 * производительностью.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_SHOPS 5       ///< Количество магазинов
#define NUM_CUSTOMERS 5   ///< Количество покупателей
#define NUM_LOADERS 3     ///< Количество грузчиков
#define MAX_NEED 10       ///< Максимальное количество товаров, необходимое покупателю
#define MAX_STOCK 5       ///< Максимальный запас товаров в магазине
#define MIN_STOCK 3       ///< Минимальный запас товаров в магазине
#define LOAD_AMOUNT 5     ///< Количество товаров, добавляемое грузчиков за раз


/**
 * @brief Структура данных магазина
 * Данная структура содержит информацию о магазине, включая количество 
 * продуктов в наличии и уровень удовлетворенности покупателей.
 * Она также включает мьютекс для обеспечения безопасного доступа к 
 * данным в многопоточной среде.
 *
 * @param stock Количество продуктов в магазине. Это значение указывает 
 * на текущее количество доступных товаров для продажи. 
 * 
 * @param satisfaction Количество покупателей, которые вышли довольными. 
 * Это значение отражает уровень удовлетворенности клиентов, что может 
 * быть полезно для оценки качества обслуживания и управления запасами.
 *
 * @param mutex Мьютекс для синхронизации доступа к полям структуры. 
 * Используется для предотвращения гонок данных при одновременном доступе 
 * из нескольких потоков. Перед чтением или изменением полей структуры 
 * необходимо блокировать мьютекс, а после завершения работы — разблокировать его.
 */
typedef struct {
    int stock;
    int satifaction;
    pthread_mutex_t mutex;
}Shop;
/**
 * @brief Структура данных покупателя
 * Данная структра содержит в себе информацию о конкретном покупателе
 * @param id его индентификатор
 * @param need колличество продуктов за которыми он пошел в магазин
 */
typedef struct {
    int id;
    int need;
}Customer;

/**
 * @brief Структура данных грузчиков
 * Данная структра содержит в себе информацию о конкретном грузчики
 * @param id его индентификатор
 * @param stock_to_add значение, которое он будет добавлять в магазин за один заход
 */
typedef struct
{
    int id;
    int stock_to_add;
}Loader;
/**
 * @brief Структура для хранения данных о покупателе и грузчике в контексте магазинов.
 *
 * Данная структура объединяет информацию о покупателе и грузчике, а также 
 * предоставляет указатель на массив магазинов, с которыми они взаимодействуют. 
 * Это позволяет эффективно управлять данными о клиентах и грузчиках в рамках 
 * системы, а также облегчает доступ к информации о магазинах.
 *
 * @note Используйте эту структуру для передачи данных между различными 
 * компонентами системы, связанными с покупателями и грузчиками.
 */
typedef struct
{
    Loader loader;
    Customer customer; /// Информация о покупателе
    Shop *shops; /// Указатель на массив магазинов
}CustomerAndLoaderShopData;

/**
 * @brief Получение статического счетчика удовлетворенности клиентов.
 *
 * Эта функция отслеживает количество удовлетворенных клиентов 
 * в магазине. Если вызывается от имени покупателя, функция 
 * блокирует мьютекс магазина и увеличивает счетчик. Если вызывается 
 * от имени грузчика, функция пытается получить блокировку мьютекса 
 * с помощью pthread_mutex_trylock, чтобы избежать блокировки, если 
 * мьютекс уже занят.
 *
 * @param is_customer Флаг, указывающий, является ли вызывающий 
 * покупателем (1) или грузчиком (0).
 * @param shop Указатель на структуру Shop, для которой нужно 
 * получить значение счетчика.
 *
 * @return Текущее значение счетчика удовлетворенности клиентов.
 */
int get_static_count(int is_customer, Shop *shop);

/**
 * @brief Инициализация магазинов.
 *
 * Эта функция инициализирует массив магазинов, задавая каждому 
 * магазину случайное количество запасов в диапазоне от 1 до 
 * MAX_STOCK. Также инициализируются мьютексы для каждого 
 * магазина, чтобы обеспечить безопасный доступ к их запасам 
 * в многопоточной среде.
 *
 * @param shops Указатель на массив структур Shop, который 
 * будет инициализирован.
 */
void initialize_shops(Shop *shops);

/**
 * @brief Создание потоков покупателей.
 *
 * Эта функция создает потоки для покупателей, которые будут 
 * пытаться удовлетворить свои потребности в товарах. Для каждого 
 * покупателя устанавливается уникальный идентификатор и случайное 
 * количество товаров, которое он хочет приобрести. Указатель на 
 * массив магазинов также передается в данные покупателей. 
 * Потоки создаются с помощью функции pthread_create, которая 
 * запускает функцию customer.
 *
 * @param customers Указатель на массив потоков, в который будут 
 * записаны идентификаторы созданных потоков покупателей.
 * @param data Указатель на массив структур CustomerAndLoaderShopData, 
 * содержащий информацию о покупателях и магазинах.
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины, из которых покупатели будут пытаться купить товары.
 */
void create_customers(pthread_t *customers,CustomerAndLoaderShopData *data ,Shop *shops);

/**
 * @brief Попытка покупки товаров покупателем.
 *
 * Эта функция позволяет покупателю попытаться приобрести товары из 
 * различных магазинов. Она перебирает все доступные магазины и 
 * проверяет, есть ли у покупателя потребность в товарах. Если 
 * потребность равна нулю, покупатель не заходит в магазин. 
 * Функция использует мьютексы для безопасного доступа к запасам 
 * магазинов. Если магазин имеет запасы, покупатель может 
 * приобрести товары в пределах своей потребности. После завершения 
 * покупки выводится информация о количестве купленных товаров и 
 * остатках в магазине.
 *
 * @param customer Указатель на структуру Customer, представляющую 
 * покупателя, который пытается совершить покупку.
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины, в которых покупатель будет пытаться купить товары.
 *
 * @note Функция использует pthread_mutex_trylock для попытки 
 * блокировки мьютекса магазина. Если мьютекс занят, покупатель 
 * переходит к следующему магазину.
 */
void attempt_purchase(Customer *customer, Shop *shops);

/**
 * @brief Функция потока покупателя.
 *
 * Эта функция представляет собой основной поток для покупателя. Она 
 * выполняет цикл, в котором покупатель пытается удовлетворить свои 
 * потребности, вызывая функцию attempt_purchase. Если потребность 
 * покупателя становится равной нулю, он завершает свою работу. 
 * Функция также вызывает get_static_count для обновления(итерации(++)) счетчика 
 * удовлетворенности клиентов после завершения всех покупок.
 *
 * @param arg Указатель на структуру CustomerAndLoaderShopData, 
 * содержащую данные о покупателе и информацию о магазинах.
 */
void *customer(void *arg);

/**
 * @brief Создание потоков грузчиков.
 *
 * Эта функция создает потоки для грузчиков, которые будут 
 * добавлять запасы в магазины. Для каждого загрузчика устанавливается 
 * уникальный идентификатор, количество запасов для добавления и 
 * передается указатель на массив магазинов. Потоки создаются с помощью 
 * функции pthread_create, которая запускает функцию loader.
 *
 * @param loaders Указатель на массив потоков, в который будут 
 * записаны идентификаторы созданных потоков грузчиков.
 * @param data Указатель на массив структур CustomerAndLoaderShopData, 
 * содержащий информацию о загрузчиках и магазинах.
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины, в которые будут добавляться запасы.
 */
void create_loaders(pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops);

/**
 * @brief Добавление запасов в магазины.
 *
 * Эта функция позволяет грузчику добавлять запасы в магазины, 
 * если их количество ниже минимального порога. Она перебирает 
 * все магазины и, если запасы в магазине меньше MIN_STOCK, 
 * блокирует мьютекс соответствующего магазина для безопасного 
 * обновления его запасов. После добавления запасов выводится 
 * информация о действии грузчика.
 *
 * @param loader Указатель на структуру Loader, представляющую 
 * грузчика, который выполняет операцию пополнения запасов.
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины, в которые будут добавляться запасы.
 *
 * @note Важно, если запас магазина меньше MIN_STOCK, то заблокирует мюнтекс
 * до тех пор пока не пополнит запасы магазина на LOAD_AMOUNT.
 */
void add_strock_into_shop(Loader *loader, Shop *shops);

/**
 * @brief Функция потока грузчика.
 *
 * Эта функция представляет собой основной поток для грузчика. Она 
 * выполняет цикл, в котором проверяет уровень удовлетворенности клиентов 
 * и добавляет запасы в магазины при необходимости. Если все клиенты 
 * удовлетворены, поток завершает свою работу. Функция использует 
 * get_static_count для получения текущего значения счетчика 
 * удовлетворенности.
 *
 * @param arg Указатель на структуру CustomerAndLoaderShopData, 
 * содержащую данные для работы грузчика и информацию о магазинах.
 */
void *loader(void *arg);

/**
 * @brief Создание потоков для клиентов и грузчиков.
 *
 * Данная функция создает потоки, которые будут выполнять задачи клиентов 
 * и грузчиков в рамках работы магазина. Она вызывает две вспомогательные 
 * функции: create_loaders, которая отвечает за создание потоков 
 * грузчиков, и create_customers, которая создает потоки клиентов.
 *
 * @param customers Указатель на массив потоков клиентов (pthread_t), 
 * который будет заполнен идентификаторами созданных потоков клиентов.
 * @param loaders Указатель на массив потоков грузчиков (pthread_t), 
 * который будет заполнен идентификаторами созданных потоков грузчиков.
 * @param data Указатель на структуру CustomerAndLoaderShopData, 
 * содержащую данные, необходимые для работы потоков.
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины, с которыми будут взаимодействовать потоки.
 */
void create_threads(pthread_t *customers, pthread_t *loaders, CustomerAndLoaderShopData *data, Shop *shops);

/**
 * @brief Ожидание завершения работы потоков клиентов и грузчиков.
 *
 * Эта функция ожидает завершения всех потоков клиентов и грузчиков, 
 * созданных в программе. Она использует функцию pthread_join для 
 * каждого потока в массивах customers и loaders, обеспечивая 
 * корректное завершение программы после выполнения всех задач.
 *
 * @param customers Указатель на массив потоков клиентов (pthread_t), 
 * для которых будет выполнено ожидание завершения.
 * @param loaders Указатель на массив потоков грузчиков (pthread_t), 
 * для которых также будет выполнено ожидание завершения.
 *
 * @note Важно вызывать эту функцию после создания потоков с помощью 
 * create_threads, чтобы гарантировать, что все потоки завершили свою работу 
 * перед выходом из программы.
 */
void join_threads(pthread_t *customers, pthread_t *loaders);

/**
 * @brief Освобождение ресурсов и завершение работы потоков магазина.
 *
 * Данная функция отвечает за корректное завершение работы потоков, 
 * связанных с магазинами, путем уничтожения мьютексов, используемых 
 * в структуре Shop. Уничтожение мьютексов необходимо для предотвращения 
 * утечек ресурсов и обеспечения корректной работы программы при завершении.
 *
 * @param shops Указатель на массив структур Shop, представляющих 
 * магазины. Функция проходит по каждому элементу массива и 
 * уничтожает соответствующий мьютекс.
 *
 * @note Эта функция должна вызываться после завершения всех потоков, 
 * использующих мьютексы, чтобы избежать неопределенного поведения.
 */
void exit_threads(Shop *shops);

#endif