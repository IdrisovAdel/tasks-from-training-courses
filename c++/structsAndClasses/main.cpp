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
    //����������� ������, ������� ������� Array ������� size, ����������� ���������� value ���� T. ���� � ������ ��� ������������ �� ���������, �� ������
    //�������� ����� ������������ ����������.


    Array() : arraySize(0), arrayPtr(0)
    {}
    //   ����������� ������, ������� ����� ������� ��� ����������. ������ ��������� ������ Array.

    Array(const Array & other): arraySize(other.arraySize), arrayPtr(static_cast<T*>(operator new[](arraySize * sizeof(T))))
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            new (arrayPtr + temp) T(other.arrayPtr[temp]);
        }
    }
    //����������� �����������, ������� ������� ����� ���������. ��� ���� T �������� ������������ �� ���������.

    ~Array()
    {
        for (size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp].~T();
        }
        operator delete[] (arrayPtr);
    }
    //   ����������, ���� �� ��� ���������.

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

template <typename Type, typename Comp>
Type minimum(Array<Type> const & array, Comp comparator)
{
    Type min = array[0];
    for(size_t iter = 1; iter < array.size(); ++iter)
    {
        if(!comparator(min, array[iter])) min = array[iter];
    }
    return min;
};

bool less(int a, int b)
{
    return a < b;
}

struct Greater
{
    bool operator()(int a, int b) const
    {
        return b < a;
    }
};

int main()
{
    //���������� ��������� ������� minimum, ������� ������� ����������� �������, ������� �������� � ���������� ���������� ������ Array, ��� ���� �������
    //�������� ������� Array ����� ���� ������������. ����� ���������� ������� ������������� ����, �� ���� ������� ����� ����� ������������ ����������,
    //� �������� ����������� ����� ��������� ������� ��� ������ ������ � ������������� ���������� "()". ������� ������ ������� minimum:
    Array<int> ints(3);
    ints[0] = 10;
    ints[1] = 2;
    ints[2] = 15;
    int min = minimum(ints, less); // � min ������ ������� ����� 2
    int max = minimum(ints, Greater()); // � max ������ ������� ����� 15
    std::cout << min << ' ' << max << std::endl;

    return 0;
}

