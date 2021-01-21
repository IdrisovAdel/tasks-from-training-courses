#include <cstddef>
#include <iostream>
#include <algorithm>
#include <new>
#include <string>

// ��������� ������� copy_n ���� � ���������
// �������:
//   1. ������� ������
//   2. ������ ��������
//   3. ���������� ���������, ������� �����
//      �����������

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
    //���������� ������� ����������� ��������� copy_n �� ������� ��������� ���� U* � ������� ������ ���� T*, ��� T � U ������������ ����, ��� ������� ����������
    //�������������� �� U � T. �� ���� ������� ��������� ��� ��������� � ���������� ���������, ������� ���������� �����������. ������ ������ ������� copy_n:
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4); // ������ � ������� doubles ���������� �������� 1.0, 2.0, 3.0 � 4.0

    return 0;
}

