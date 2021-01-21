#include <cstddef>
#include <iostream>
#include <algorithm>
#include <new>
#include <string>

// Параметры функции copy_n идут в следующем
// порядке:
//   1. целевой массив
//   2. массив источник
//   3. количество элементов, которые нужно
//      скопировать

template <typename T, typename U>
void copy_n(T * const to, U const * const from, size_t count)
{
    for(size_t iter = 0; iter < count; ++iter)
    {
        to[iter] = static_cast<T>(from[iter]);
    }
};


int main()
{
    //Реализуйте функцию копирования элементов copy_n из массива источника типа U* в целевой массив типа T*, где T и U произвольные типы, для которых определено
    //преобразование из U в T. На вход функция принимает два указателя и количество элементов, которые необходимо скопировать. Пример вызова функции copy_n:
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4); // теперь в массиве doubles содержатся элементы 1.0, 2.0, 3.0 и 4.0

    return 0;
}

