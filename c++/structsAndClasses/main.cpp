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
    //конструктор класса, который создает Array размера size, заполненный значени€ми value типа T. ≈сли у класса нет конструктора по умолчанию, то второй
    //аргумент этого конструктора об€зателен.


    Array() : arraySize(0), arrayPtr(0)
    {}
    //   конструктор класса, который можно вызвать без параметров. ƒолжен создавать пустой Array.

    Array(const Array & other): arraySize(other.arraySize), arrayPtr(static_cast<T*>(operator new[](arraySize * sizeof(T))))
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            new (arrayPtr + temp) T(other.arrayPtr[temp]);
        }
    }
    //конструктор копировани€, который создает копию параметра. ƒл€ типа T оператор присваивани€ не определен.

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

// ћожно заводить любые вспомогательные функции,
// структуры или даже измен€ть сигнатуру flatten,
// но при этом все примеры вызова из задани€ должны
// компилироватьс€ и работать.
template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{
    for(size_t iter1 = 0; iter1 < array.size(); ++iter1)
    {
        out << array[iter1] << ' ';
    }
}

template <typename T>
void flatten(const Array<Array<T> >& array, std::ostream& out)
{
    for(size_t iter = 0; iter < array.size(); ++iter)
    {
        flatten(array[iter], out);
    }
}


int main()
{
    //Ўаблонный класс Array может хранить объекты любого типа, дл€ которого определЄн конструктор копировани€, в том числе и другой Array, например,
    //Array< Array<int> >. √лубина вложенности может быть произвольной. Ќапишите шаблонную функцию (или несколько) flatten, котора€ принимает на вход
    //такой "многомерный" Array неизвестной заранее глубины вложенности и выводит в поток out через пробел все элементы, хран€щиес€ на самом нижнем уровне.
    //ѕримеры работы функции flatten:
    Array<int> ints(4, 0);
    ints[0] = 10;
    ints[1] = 20;
    ints[2] = 30;
    ints[3] = 40;
    flatten(ints, std::cout); // выводит на экран строку "10 20"

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"

    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout); // работать должно не только дл€ типа int*/

    /*Array< Array<Array<int> > > array_of_ints1(2, array_of_ints);
    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20 10 20 10 20"*/


    return 0;
}

