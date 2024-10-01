# s21_containers

Реализация библиотеки s21_containers.h.


## Containers

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора g++
- Классы реализованы внутри пространства имен `s21`
- Полное покрытие unit-тестами методов контейнерных классов c помощью библиотеки GTest

### Part 1. Реализация библиотеки s21_containers.h

Реализация классов библиотеки `s21_containers.h`: \
Список классов: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек), `vector` (вектор).
- Решение оформилено в виде заголовочного файла `s21_containers.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_list.h`, `s21_map.h` и т.д.)

### Part 2. Дополнительно. Реализация библиотеки s21_containersplus.h

Дополниетельная реализация контейнерами: \
 `array` (массив), `multiset` (мультимножество).
- Оформлены в виде заголовочного файла `s21_containersplus.h`, который включает в себя другие заголовочные файлы с реализациями необходимых контейнеров (`s21_array.h`, `s21_multiset.h`)

### Part 3. Дополнительно. Реализация методов `insert_many`

Классы дополненые соответствующими методами:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | inserts new elements into the container directly before `pos`  | List, Vector |
| `void insert_many_back(Args&&... args)`          | appends new elements to the end of the container  | List, Vector, Queue |
| `void insert_many_front(Args&&... args)`          | appends new elements to the top of the container  | List, Stack |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | inserts new elements into the container  | Map, Set, Multiset |
