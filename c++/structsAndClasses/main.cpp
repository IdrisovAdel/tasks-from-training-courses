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

template <typename Type, size_t size>
size_t array_size(Type const (& array)[size])
{
    return sizeof(array) / sizeof(array[0]);
};

int main()
{
    //���������� ������� array_size, ������� ���������� ������ �������, ����������� � �������� ���������. ������� ������ �������� ������ ��� ��������!
    //�. �. ���� ������� �������� ���������, ������ ��������� ������ ����������.
    int ints[] = {1, 2, 3, 4};
    int *iptr = ints;
    double doubles[] = {3.14};
    int size = array_size(ints); // ������ 4
    size = array_size(doubles); // ������ 1
    //size = array_size(iptr); // ��� ������ ��������� ������ ����������*/

    return 0;
}

