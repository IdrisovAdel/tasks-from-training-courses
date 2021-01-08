#include <cstddef>
#include <iostream>
#include <algorithm>
#include <new>
#include <string>

//using namespace std;

struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};
// ������ ValueHolder � ������� ���������� T,
// ������ ��������� ���� �������� ���� data_
// ���� T.
//
// � ������� ValueHolder ������ ���� ���������
// ����������� �� ������ ��������� ���� T,
// ������� �������������� ���� data_.
//
// ������ ValueHolder ������ �������������
// ��������� ICloneable, � ���������� ���������
// �� ����� �������, ��������� � ����, �� ������
// clone.
template <typename T>
struct ValueHolder:ICloneable
{
    ValueHolder(const T & value) : data_(value)
    {}
    ValueHolder * clone() const
    {
        return (new ValueHolder(*this));
    }
    T data_;
};

int main()
{
    /* ���������� ��������� ��������� ValueHolder � ����� ������� ���������� T, �������������� �� ���������� ICloneable. ��������� ICloneable ��������
    ����� ���� ����������� ����� ICloneable* clone() const, ������� ������ ������� ��������� �� ����� �������, �� ������� �� ��� ������ (������ ������ ����
    ������ � ����). ������ ValueHolder, ��� ������� ��� ��������, ������ ����� ���� �������� (�������� ��� data_) ���� T (��� ���� T ��������� �����������
    �����������). �� ������� ���� data_ �������� (������� � ������ ������ �� ���� �����, ��� ValueHolder ������ ���� ����������).*/

    ICloneable* first = new ValueHolder<int>(1313);

    return 0;
}

