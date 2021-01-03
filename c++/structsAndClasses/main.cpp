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
    //   ����������� ������, ������� ������� Array ������� size, ����������� ���������� value ���� T. �������� ��� � ���� T ����
    //   �����������, ������� ����� ������� ��� ����������, ���� �� ��� �� �����.

    Array(const Array & other)
    {
        arraySize = other.arraySize;
        arrayPtr = new T[arraySize];
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp] = other.arrayPtr[temp];
        }
    }
    //   ����������� �����������, ������� ������� ����� ���������. ��������, ��� ��� ���� T ��������� �������� ������������.

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
    //   �������� ������������.

    void Swap(Array &other)
	{
	    std::swap(this->arraySize, other.arraySize);
	    std::swap(this->arrayPtr, other.arrayPtr);
	}

    size_t size() const
    {
        return arraySize;
    }
    //   ���������� ������ ������� (���������� ���������).

    T& operator[](size_t index)
    {
        return arrayPtr[index];
    }
    const T& operator[](size_t index) const
    {
        return arrayPtr[index];
    }
    //   ��� ������ ��������� ������� �� �������.

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
