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

struct Dummy { };
typedef int type;

// ���������� ������ SameType � ����� ��������
// �����������. � ������� ������ ���� ����������
// ���� ����������� ��������� ���� bool � ������
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
    //������������ ����������� ������� ������ SameType. ���� ������ �� �������� ������� �������, � ������ ���� ����������� ����������� ���� ���� bool,
    //� ������ value. ������ ��������� ��� ������� ���������, � ���� ��� ������� ��������� ������� �������� ����� � ��� �� �����, �� ����������� ���� value
    //������ ������� �������� true, � ��������� ������ �������� false.
    std::cout << SameType<int, int>::value << std::endl; // ������� 1, �. �. true
    std::cout << SameType<int, type>::value << std::endl; // 1, type == int
    std::cout << SameType<int, int&>::value << std::endl; // 0, int � ������ �� int - ��������� ����
    std::cout << SameType<Dummy, Dummy>::value << std::endl; // 1
    std::cout << SameType<int, const int>::value << std::endl; // 0, const - ����� ����*/


    return 0;
}

