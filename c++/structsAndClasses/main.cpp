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

// ����� �������� ����� ��������������� �������,
// ��������� ��� ���� �������� ��������� flatten,
// �� ��� ���� ��� ������� ������ �� ������� ������
// ��������������� � ��������.
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
    //��������� ����� Array ����� ������� ������� ������ ����, ��� �������� �������� ����������� �����������, � ��� ����� � ������ Array, ��������,
    //Array< Array<int> >. ������� ����������� ����� ���� ������������. �������� ��������� ������� (��� ���������) flatten, ������� ��������� �� ����
    //����� "�����������" Array ����������� ������� ������� ����������� � ������� � ����� out ����� ������ ��� ��������, ���������� �� ����� ������ ������.
    //������� ������ ������� flatten:
    Array<int> ints(4, 0);
    ints[0] = 10;
    ints[1] = 20;
    ints[2] = 30;
    ints[3] = 40;
    flatten(ints, std::cout); // ������� �� ����� ������ "10 20"

    Array< Array<int> > array_of_ints(2, ints);
    flatten(array_of_ints, std::cout); // ������� �� ����� ������ "10 20 10 20"

    Array<double> doubles(10, 0.0);
    flatten(doubles, std::cout); // �������� ������ �� ������ ��� ���� int*/

    /*Array< Array<Array<int> > > array_of_ints1(2, array_of_ints);
    flatten(array_of_ints, std::cout); // ������� �� ����� ������ "10 20 10 20 10 20 10 20"*/


    return 0;
}

