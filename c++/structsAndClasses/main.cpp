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

struct Dummy { };
typedef int type;

// Определите шаблон SameType с двумя типовыми
// параметрами. В шаблоне должна быть определена
// одна статическая константа типа bool с именем
// value

template <typename Type, typename Types>
class SameType
{
public:
    bool static const value = false;
};

template <typename Type>
class SameType <Type, Type>
{
public:
    bool static const value = true;
};

int main()
{
    //предлагается реализовать простой шаблон SameType. Этот шаблон не содержит никаких методов, а только одно статическое константное поле типа bool,
    //с именем value. Шаблон принимает два типовых параметра, и если два типовых параметра шаблона являются одним и тем же типом, то статическое поле value
    //должно хранить значение true, в противном случае значение false.
    std::cout << SameType<int, int>::value << std::endl; // выведет 1, т. е. true
    std::cout << SameType<int, type>::value << std::endl; // 1, type == int
    std::cout << SameType<int, int&>::value << std::endl; // 0, int и ссылка на int - различные типы
    std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
    std::cout << SameType<int, const int>::value << std::endl; // 0, const - часть типа*/


    return 0;
}

