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


//*****************************************************************************************************



int main()
{
    //Вам дан класс Rational, который описывает рациональное число. В нем определены методы add, sub, mul и div, которые прибавляют к нему число, отнимают
    //число, умножают на число и делят на число соответственно. Кроме того в нем определен метод neg, который меняет знак на противоположный.
    //Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли принимать в качестве аргументов и объекты типа Rational и целые
    //числа. Кроме того вам необходимо определить операторы унарного минуса и плюса для класса Rational.
    Rational var1(2, 4);
    Rational var2(2, 5);
    var1.add(var2);
    cout << var1.to_double() << endl;
    Rational var3(3, 4);
    Rational var4(1, 4);
    var4.sub(var3);
    cout << var4.to_double() << endl;
    Rational var5(2, 4);
    Rational var6(3, 4);
    var5.mul(var6);
    cout << var5.to_double() << endl;
    Rational var7(5, 6);
    Rational var8(5, 3);
    var7.div(var8);
    cout << var7.to_double() << endl;
    Rational a(1, 4);
    if ((-a).to_double() != 1.0 / 4.0) cout << (-a).to_double();


    return 0;
}

