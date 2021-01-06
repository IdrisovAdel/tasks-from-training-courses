#include <cstddef>
#include <iostream>
#include <algorithm>
#include <new>
#include <string>

using namespace std;

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
    //конструктор класса, который создает Array размера size, заполненный значени€ми value типа T. ≈сли у класса нет конструктора по умолчанию, то второй
    //аргумент этого конструктора об€зателен.


    Array() : arraySize(0), arrayPtr(0)
    {}
    //   конструктор класса, который можно вызвать без параметров. ƒолжен создавать пустой Array.

    Array(const Array & other): arraySize(other.arraySize), arrayPtr(static_cast<T*>(operator new[](arraySize * sizeof(T))))
    {
        for(size_t temp = 0; temp < arraySize; ++temp)
        {
            new (arrayPtr + temp) T(other.arrayPtr[temp]);
        }
    }
    //конструктор копировани€, который создает копию параметра. ƒл€ типа T оператор присваивани€ не определен.

    ~Array()
    {
        for (size_t temp = 0; temp < arraySize; ++temp)
        {
            arrayPtr[temp].~T();
        }
        operator delete[] (arrayPtr);
    }
    //   деструктор, если он вам необходим.

    Array& operator=(const Array & other)
    {
        if(this != &other)
        {
            Array temp(other);
            this->Swap(temp);
        }
        return *this;
    }
    //   оператор присваивани€.

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

    void prnt()
    {
        for (size_t i = 0; i < arraySize; ++i)
            cout << *(arrayPtr + i);
        cout << endl;
    }

private:
    size_t arraySize;
    T * arrayPtr;
};


template <typename Tx>
struct X
{
	X()
	{
		this->x_ = new Tx();
		*this->x_ = 1;
	}
	X(const X& inX)
	{
		this->x_ = new Tx();
		*this->x_ = *inX.x_;
	}
	~X() { delete this->x_; }
	friend std::ostream& operator<< (std::ostream& s, const X& obj)
	{
		s << *(obj.x_);
		return s;
	}
	void set(Tx i)
	{
		*(this->x_) = i;
	}
private:
	X& operator=(const X& inX);
	Tx *x_;
};

void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();


int main()
{
    /*¬ предыдущей версии предполагаетс€, что дл€ типа T определены оператор присваивани€ и конструктор по умолчанию. ѕри создании шаблонных классов контейнеров
    (вроде Array и не только) разумно старатьс€ минимизировать требовани€ к типам шаблонных параметров. ѕоэтому усложним задачу, реализуйте класс Array
    не полага€сь на то, что дл€ типа T определен оператор присваивани€ и конструктор по умолчанию.  онструктор копировани€ у типа T есть.
    Hints: используйте placement new и €вный вызов деструктора (смотрите урок 3.4), чтобы создавать и уничтожать объекты, аллоцировать правильно
    выровненную пам€ть можно с помощью new char[N * sizeof(T)], где N - количество элементов массива.(тест из комментариев)*/

    setlocale(LC_ALL, "");
	test0();
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();

    return 0;
}

void test0()
{
	cout << endl << "*****Test 0(primitives)**********" << endl;
	{
		cout << endl << "*****CHAR**********" << endl;
		Array<char> ar(size_t(5), '0');
		Array<char> x(size_t(4), '4');
		ar = x;
		ar.prnt();

		Array<char> x2(size_t(6), '6');
		ar = x2;
		ar.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****STRING**********" << endl;
		Array<string> cr(size_t(5), "0");
		Array<string> cx(size_t(4), "4");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(6), "6");
		cr = cx2;
		cr.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****INT**********" << endl;
		Array<int> ir(size_t(5), 0);
		Array<int> ix(size_t(4), 4);
		ir = ix;
		ir.prnt();

		Array<int> ix2(size_t(6), 6);
		ir = ix2;
		ir.prnt();
	}
	cout << endl;
	{
		cout << endl << "*****DOUBLE**********" << endl;
		Array<double> dr(size_t(5), 0.0);
		Array<double> dx(size_t(4), 4.0);
		dr = dx;
		dx.prnt();

		Array<double> ix2(size_t(6), 6.0);
		dr = ix2;
		dr.prnt();
	}
	cout << endl;
	return;
}


void test1()
{
	{
		cout << endl << "*****Test 1(assigment)**********" << endl;
		Array<char> ar(size_t(100), '0');
		Array<char> x(size_t(0), '1');
		ar = x;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> cr(size_t(100), "Str0");
		Array<string> cx(size_t(0), "Str1");
		cr = cx;
		cr.prnt();

		Array<string> cx2(size_t(2), "Str3");
		cr = cx2;
		cr.prnt();
	}
	{
		cout << "*****INT**********" << endl;
		Array<int> cr(size_t(100), 0);
		Array<int> cx(size_t(0), 15);
		cr = cx;
		cr.prnt();

		Array<int> cx2(size_t(2), 55);
		cr = cx2;
		cr.prnt();
	}
	return;
}

void test2()
{
	cout << endl << "*****Test 2(copy constructor)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> x(size_t(3), '3');
		Array<char> ar(x);
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> x(size_t(3), "333");
		Array<string> ar(x);
		ar.prnt();
	}

	return;
}

void test3()
{
	cout << endl << "*****Test 3(Empty)**********" << endl;
	{
		cout << "*****CHAR**********" << endl;
		Array<char> ar(size_t(0), '0');
		ar = ar;
		ar.prnt();
	}
	{
		cout << "*****STRING**********" << endl;
		Array<string> ar(size_t(0), "0");
		ar = ar;
		ar.prnt();
	}
	return;
}

void test4()
{
	cout << endl << "*****Test 4(assigment A=A) **********" << endl;
	{
		Array<char> ar(size_t(4), '0');
		ar = ar;
		ar.prnt();
	}
	return;
}
void test5()
{
	cout << endl << "*****Test 5(out bound)**********" << endl;
	{
		cout << "*****more**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[10] << endl;
	}
	{
		cout << "*****less**********" << endl;
		Array<char> ar(size_t(4), '0');
		cout << ar[-10] << endl;
	}
	return;
}

void test6()
{
	cout << endl << "*****Test 6(pointer)**********" << endl;
	{
		cout << "*****CHAR(copy)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(4), '4');
		ar->prnt();
		delete ar;
	}
	{
		cout << "*****CHAR(=)**********" << endl;
		Array<char> *ar = new Array<char>(size_t(5), '5');
		ar->prnt();
		Array<char> *xr = ar;
		xr->prnt();
		delete ar;
	}
	return;
}
void test7()
{
	cout << endl << "*****Test 7(X-object)**********" << endl;
	{
		cout << "***** X<INT> **********" << endl;
		X<int> x;
		x.set(4);
		Array<X<int>> *ar = new Array<X<int>>(size_t(4), x);
		ar->prnt();
		delete ar;
	}
	{
		cout << "***** X<CHAR> (new, =, copy) **********" << endl;
		X<char> x;
		x.set('c');
		Array<X<char>> *ar = new Array<X<char>>(size_t(4), x);
		ar->prnt();
		Array<X<char>> *xr = ar;
		xr->prnt();
		Array<X<char>> y(*xr);
		y.prnt();
		delete ar;
	}
	{
		cout << "***** X<STRING> (new, =, copy)**********" << endl;
		X<string> x;
		x.set("There are no tests for this task");
		Array<X<string>> *ar = new Array<X<string>>(size_t(1),x );
		ar->prnt();
		Array<X<string>> *xr = ar;
		xr->prnt();
		Array<X<string>> y(*xr);
		y.prnt();
		delete ar;
	}
	return;
}
