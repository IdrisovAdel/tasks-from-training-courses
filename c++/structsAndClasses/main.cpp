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

// ��� �����, ������� ��� ����� �����������
class Any
{
public:

    // � ������ Any ������ ���� �����������,
    // ������� ����� ������� ��� ����������,
    // ����� ������� ��������� ���:
    //    Any empty; // empty ������ �� ������
    Any() : valuePtr(nullptr)
    {
    }

    // � ������ Any ������ ���� ���������
    // ����������� �� ������ ���������, �����
    // ����� ���� ��������� ������� ���� Any,
    // ��������, ��������� �������:
    //    Any i(10); // i ������ �������� 10
    template <typename Type>
    Any(Type const & value) : valuePtr(new ValueHolder <Type> (value))
    {
    };

    // �� �������� ��� ����������. ��� ����������
    // ������� ����� ����������.
    ~Any()
    {
        if(valuePtr != nullptr) delete valuePtr;
    }

    // � ������ Any ����� ������ ���� �����������
    // ����������� (��� ������� ����� clone
    // ���������� ICloneable)
    Any(Any const & other) : valuePtr(other.valuePtr ? other.valuePtr->clone() : nullptr)
    {
    }

    // � ������ ������ ���� �������� ������������ �/���
    // ��������� �������� ������������, ����� �������
    // ��������� ���:
    //    Any copy(i); // copy ������ 10, ��� � i
    //    empty = copy; // empty ������ 10, ��� � copy
    //    empty = 0; // � ������ empty ������ 0
    Any & operator=(Any const & other)
    {
        if(this != &other)
        {
            Any temp(other);
            Swap(temp, *this);
        }
        return *this;
    }

    void Swap(Any & first, Any & second)
    {
        ICloneable * temp = first.valuePtr;
        first.valuePtr = second.valuePtr;
        second.valuePtr = temp;
    }

    template <typename T>
    Any &operator=(T const & other)
    {
        Any temp(other);
        Swap(temp, *this);
        return *this;
    }

    // �� � �������, �� ����� ����� �������� ��������
    // ��������, ��� ����� ���������� � ������ Any
    // ��������� ����� cast, ������� ����������
    // ��������� �� �������� ��������, ��� �������
    // ��������� � ������ �������������� ����� ���
    // ���� ������ Any ������ �� ������:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // ������ ��� i ������ int, � �� char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // ��� ���������� ����������� �������� dynamic_cast.
    template <typename T>
    T * cast()
    {
        if(!valuePtr) return 0;
        else
        {
            ValueHolder <T> * temp = dynamic_cast<ValueHolder <T> *>(valuePtr);
            if(!temp) return 0;
            else
            {
                return &(temp->data_);
            }
        }

    }

    // �������� � ��� ���� ��� ���������� ������ Base: Derived1
    // � Derived2. ����� ���� � ��� ���� ������� baseptr
    // ���� Base*. ��� ��������� ��������� �� ���� ��������� ��
    // ����� ���� �� ������ ������ Derived1 ��� �� ������
    // ������ Derived2? ��� ����� ����� ��������������� dynamic_cast-��:
    //
    // Derived1 *derived1ptr = dynamic_cast<Derived1*>(baseptr);
    //
    // ���� derived1ptr �� ����� 0, ��  baseptr �� ����� ����
    // �������� �� ������ ������ Derived1, ���� �� derivedptr ����� 0,
    // �� baseptr �� ����� ���� �������� �� ����� ������-�� �������
    // ������ (��������, Derived2). ��� ����� ��������� ���:
    //
    // Derived2 *derived2ptr = dynamic_cast<Derived2*>(baseptr);
    //
    // dynamic_cast �������� ������, ���� � ������ ���� ���� ��
    // ���� ����������� �����, � � ������� ValueHolder �����
    // ��� ��� �������.
private:
    ICloneable * valuePtr;
};

int main()
{
    /* ���������� ��������� ��������� ValueHolder � ����� ������� ���������� T, �������������� �� ���������� ICloneable. ��������� ICloneable ��������
    ����� ���� ����������� ����� ICloneable* clone() const, ������� ������ ������� ��������� �� ����� �������, �� ������� �� ��� ������ (������ ������ ����
    ������ � ����). ������ ValueHolder, ��� ������� ��� ��������, ������ ����� ���� �������� (�������� ��� data_) ���� T (��� ���� T ��������� �����������
    �����������). �� ������� ���� data_ �������� (������� � ������ ������ �� ���� �����, ��� ValueHolder ������ ���� ����������).*/

    //ICloneable* first = new ValueHolder<int>(1313);
    /*Any empty;
    Any i(10);
    Any copy(i);
    empty = copy; // empty ������ 10, ��� � copy
    empty = 0; // � ������ empty ������ 0

    int *iptr = i.cast<int>(); // *iptr == 10
    char *cptr = i.cast<char>(); // cptr == 0,
    // ������ ��� i ������ int, � �� char
    Any empty2;
    int *p = empty2.cast<int>(); // p == 0
    std::cout << *iptr;*/

    Any *anyd = new Any(3.14);
    Any *anyf = new Any(3.14f);
    Any *anyi = new Any(3);
    Any *anys = new Any(std::string("Hello"));

    std::cout << *anyd->cast<double>() << std::endl;
    std::cout << *anyf->cast<float>() << std::endl;
    std::cout << *anyi->cast<int>() << std::endl;
    std::cout << *anys->cast<std::string>() << std::endl;
    std::cout << anys->cast<int>() << std::endl;

    {
        Any empty;
        Any clone(empty);
        int *p = empty.cast<int>();
        const char *message = p == 0 ? "empty" : "p is not empty";
        std::cout << message << std::endl;

        clone = empty;

        empty = *anyd;
        message = empty.cast<double>() == 0 ? "empty" : "is not empty";
        std::cout << message << std::endl;
        std::cout << *empty.cast<double>() << std::endl;
        std::cout << *anyd->cast<double>() << std::endl;

        delete anyd;
        std::cout << *empty.cast<double>() << std::endl;

        anyd = new Any(empty);
        std::cout << *anyd->cast<double>() << std::endl;
        (void)clone;
    }

    std::cout << *anyd->cast<double>() << std::endl;


    return 0;
}

