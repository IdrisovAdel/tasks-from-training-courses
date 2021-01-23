#include <cstddef>
#include <iostream>
#include <algorithm>
#include <new>
#include <string>

template <typename T>
class Array
{
public:
    explicit Array(size_t size, const T& value = T()) : arraySize(size), arrayPtr(static_cast<T*>(operator new[](arraySize * sizeof(T))))
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            new (arrayPtr + temp) T(value);
        }
    }
    //конструктор класса, который создает Array размера size, заполненный значениями value типа T. Если у класса нет конструктора по умолчанию, то второй
    //аргумент этого конструктора обязателен.


    Array() : arraySize(0), arrayPtr(0)
    {}
    //   конструктор класса, который можно вызвать без параметров. Должен создавать пустой Array.

    Array(const Array & other): arraySize(other.arraySize), arrayPtr(static_cast<T*>(operator new[](arraySize * sizeof(T))))
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            new (arrayPtr + temp) T(other.arrayPtr[temp]);
        }
    }
    //конструктор копирования, который создает копию параметра. Для типа T оператор присваивания не определен.

    ~Array()
    {
        for (size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp].~T();
        }
        operator delete[] (arrayPtr);
    }
    //   деструктор, если он вам необходим.

    Array& operator=(const Array & other)
    {
        std::swap(this->arrayPtr, other.arrayPtr);
    }

    size_t size() const
    {
        return arraySize;
    }
    T& operator[](size_t index)
    {
        return arrayPtr[index];
    }

    const T& operator[](size_t index) const
    {
        return arrayPtr[index];
    }


private:
    size_t arraySize;
    T * arrayPtr;
};

template <typename Type, size_t size>
size_t array_size(Type const (& array)[size])
{
    return sizeof(array) / sizeof(array[0]);
};

int main()
{
    //Реализуйте функцию array_size, которая возвращает размер массива, переданного в качестве параметра. Функция должна работать только для массивов!
    //Т. е. если функции передать указатель, должна произойти ошибка компиляции.
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    int size = array_size(ints); // вернет 4
    size = array_size(doubles); // вернет 1
    //size = array_size(iptr); // тут должна произойти ошибка компиляции*/

    return 0;
}

