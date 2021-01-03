#include <cstddef>
#include <iostream>
#include <algorithm>

//using namespace std;

template <typename T>
class Array
{
public:
    explicit Array(size_t size = 0, const T& value = T()) : arraySize(size), arrayPtr(size ? new T[arraySize]: 0)
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp] = value;
        }
    }
    //   конструктор класса, который создает Array размера size, заполненный значениями value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без параметров, либо он ему не нужен.

    Array(const Array & other)
    {
        arraySize = other.arraySize;
        arrayPtr = new T[arraySize];
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp] = other.arrayPtr[temp];
        }
    }
    //   конструктор копирования, который создает копию параметра. Считайте, что для типа T определен оператор присваивания.

    ~Array()
    {
        delete[] arrayPtr;
    }

    Array& operator=(const Array & other)
    {
        if(this != &other)
        {
            Array temp(other);
            this->Swap(temp);
        }
        return *this;
    }
    //   оператор присваивания.

    void Swap(Array &other)
	{
	    std::swap(this->arraySize, other.arraySize);
	    std::swap(this->arrayPtr, other.arrayPtr);
	}

    size_t size() const
    {
        return arraySize;
    }
    //   возвращает размер массива (количество элементов).

    T& operator[](size_t index)
    {
        return arrayPtr[index];
    }
    const T& operator[](size_t index) const
    {
        return arrayPtr[index];
    }
    //   две версии оператора доступа по индексу.

    void printArray() const
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            std::cout << arrayPtr[temp] << ' ';
        }
        std::cout << std::endl;
    }
private:
    size_t arraySize;
    T * arrayPtr;
};
int main()
{
    Array <int> temp(10, 15);
    Array <int> const temp2(3, 5);
    Array <int> temp3(temp2);
    temp3.printArray();
    std::cout << temp3[0];
    return 0;
}
