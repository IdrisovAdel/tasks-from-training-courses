#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;


//*************************************************************************************************************************************************
struct Rational
{
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {}

    void add(Rational rational)
    {
        if(this->denominator_ == rational.denominator_)
        {
            this->numerator_ += rational.numerator_;
        }
        else
        {
            this->numerator_ = this->numerator_ * rational.denominator_ + rational.numerator_ * this->denominator_;
            this->denominator_ = this->denominator_ * rational.denominator_;
        }
    }
    void sub(Rational rational)
    {
        if(this->denominator_ == rational.denominator_)
        {
            this->numerator_ -= rational.numerator_;
        }
        else
        {
            this->numerator_ = this->numerator_ * rational.denominator_ - rational.numerator_ * this->denominator_;
            this->denominator_ = this->denominator_ * rational.denominator_;
        }
    }
    void mul(Rational rational)
    {
        this->numerator_ *= rational.numerator_;
        this->denominator_ *= rational.denominator_;
    }
    void div(Rational rational)
    {
        rational.inv();
        this->numerator_ *= rational.numerator_;
        this->denominator_ *= rational.denominator_;
    }
    void neg()
    {
        numerator_ = -numerator_;
    }
    void inv()
    {
        int temp = numerator_;
        numerator_ = denominator_;
        denominator_ = temp;
    }
    double to_double() const
    {
        return (double)numerator_ / denominator_;
    }
    double fromRationalToDouble()const
    {
        return (double)numerator_ / denominator_;
    }
    operator double() const
    {
        return this->to_double();
    }
//--------------------------------------------
    Rational operator-() const
    {
        Rational temp(1);
        temp.numerator_ = (-1) * numerator_;
        temp.denominator_ = denominator_;
        return temp;
    }
    Rational operator+() const
    {
        return *this;
    }
private:
    int numerator_;
    int denominator_;
};
//---------------------------------------------------------------
Rational & operator+=(Rational & rational, Rational const & number)
{
    rational.add(number);
    return rational;
}

Rational & operator-=(Rational & rational, Rational const & number)
{
    rational.sub(number);
    return rational;
}

Rational & operator*=(Rational & rational, Rational const & number)
{
    rational.mul(number);
    return rational;
}

Rational & operator/=(Rational & rational, Rational const & number)
{
    rational.div(number);
    return rational;
}
//-----------------------------------------------------------------
Rational operator+(Rational number, Rational const & rational)
{
    return (number += rational);
}
Rational operator-(Rational number, Rational const & rational)
{
    return (number -= rational);
}
Rational operator*(Rational number, Rational const & rational)
{
    return (number *= rational);
}
Rational operator/(Rational number, Rational const & rational)
{
    return (number /= rational);
}
//-----------------------------------------------------

bool operator==(Rational const & number, Rational const & rational)
{
    return (number.fromRationalToDouble() == rational.fromRationalToDouble() ? true : false);
}

bool operator!=(Rational const & number, Rational const & rational)
{
    return !(number == rational);
}

bool operator<(Rational const & number, Rational const & rational)
{
    return (number.fromRationalToDouble() < rational.fromRationalToDouble() ? true : false);
}

bool operator>(Rational const & number, Rational const & rational)
{
    return (rational < number);
}

bool operator<=(Rational const & number, Rational const & rational)
{
    return ((number < rational) || (number == rational));
}

bool operator>=(Rational const & number, Rational const & rational)
{
    return (!(number < rational) || (number == rational));
}


//*****************************************************************************************************

int main()
{
    //Еще одна важная группа операторов, которые полезно реализовать для класса рациональных чисел — это операторы сравнения. Реализуйте
    //операторы <, <=, >, >=, ==, != для класса Rational так, чтобы можно было сравнивать объекты класса Rational не только друг с другом, но и с целыми числами.
    //При решении задания не используйте метод to_double, он введен в класс, в первую очередь, для удобства тестирования. Вы можете определять любые
    //вспомогательные методы или функции если необходимо.
    /*Rational temp1(2, 4), temp2(3, 4);
    cout << (temp1 > temp2) << endl;*/


    //Добавьте в класс Rational оператор приведения к double. Все операторы из предыдущих заданий отсутствуют и реализовывать их не нужно. Метод to_double
    //можно использовать в этом задании.Важное замечание: добавлять оператор преобразования к double в класс Rational не самая удачная идея, например, потому,
    //что при таком преобразовании может происходить потеря точности. Эта задача дана исключительно с целью ознакомления с правильным порядком перегрузки таких
    //операторов.

    return 0;
}

