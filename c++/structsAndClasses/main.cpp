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
// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
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

// Это класс, который вам нужно реализовать
class Any
{
public:

    // В классе Any должен быть конструктор,
    // который можно вызвать без параметров,
    // чтобы работал следующий код:
    //    Any empty; // empty ничего не хранит
    Any() : valuePtr(nullptr)
    {
    }

    // В классе Any должен быть шаблонный
    // конструктор от одного параметра, чтобы
    // можно было создавать объекты типа Any,
    // например, следующим образом:
    //    Any i(10); // i хранит значение 10
    template <typename Type>
    Any(Type const & value) : valuePtr(new ValueHolder <Type> (value))
    {
    };

    // Не забудьте про деструктор. Все выделенные
    // ресурсы нужно освободить.
    ~Any()
    {
        if(valuePtr != nullptr) delete valuePtr;
    }

    // В классе Any также должен быть конструктор
    // копирования (вам поможет метод clone
    // интерфейса ICloneable)
    Any(Any const & other) : valuePtr(other.valuePtr ? other.valuePtr->clone() : nullptr)
    {
    }

    // В классе должен быть оператор присваивания и/или
    // шаблонный оператор присваивания, чтобы работал
    // следующий код:
    //    Any copy(i); // copy хранит 10, как и i
    //    empty = copy; // empty хранит 10, как и copy
    //    empty = 0; // а теперь empty хранит 0
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

    // Ну и наконец, мы хотим уметь получать хранимое
    // значение, для этого определите в классе Any
    // шаблонный метод cast, который возвращает
    // указатель на хранимое значение, или нулевой
    // указатель в случае несоответствия типов или
    // если объект Any ничего не хранит:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // При реализации используйте оператор dynamic_cast.
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

    // Допустим у вас есть два наследника класса Base: Derived1
    // и Derived2. Кроме того у вас есть указать baseptr
    // типа Base*. Как проверить указывает ли этот указатель на
    // самом деле на объект класса Derived1 или на объект
    // класса Derived2? Для этого можно воспользоваться dynamic_cast-ом:
    //
    // Derived1 *derived1ptr = dynamic_cast<Derived1*>(baseptr);
    //
    // Если derived1ptr не равен 0, то  baseptr на самом деле
    // указывал на объект класса Derived1, если же derivedptr равен 0,
    // то baseptr на самом деле указывал на объкт какого-то другого
    // класса (например, Derived2). Это можно проверить так:
    //
    // Derived2 *derived2ptr = dynamic_cast<Derived2*>(baseptr);
    //
    // dynamic_cast работает только, если в классе есть хотя бы
    // один виртуальный метод, и в шаблоне ValueHolder такой
    // как раз имеется.
private:
    ICloneable * valuePtr;
};

int main()
{
    /* Реализуйте шаблонную структуру ValueHolder с одним типовым параметром T, унаследованную от интерфейса ICloneable. Интерфейс ICloneable содержит
    всего один виртуальный метод ICloneable* clone() const, который должен вернуть указатель на копию объекта, на котором он был вызван (объект должен быть
    создан в куче). Шаблон ValueHolder, как говорит его название, хранит всего одно значение (назовите его data_) типа T (для типа T определен конструктор
    копирования). Не делайте поле data_ закрытым (поэтому в данном случае мы явно пишем, что ValueHolder должна быть структурой).*/

    //ICloneable* first = new ValueHolder<int>(1313);
    /*Any empty;
    Any i(10);
    Any copy(i);
    empty = copy; // empty хранит 10, как и copy
    empty = 0; // а теперь empty хранит 0

    int *iptr = i.cast<int>(); // *iptr == 10
    char *cptr = i.cast<char>(); // cptr == 0,
    // потому что i хранит int, а не char
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

