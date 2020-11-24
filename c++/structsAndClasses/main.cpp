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
    //------------------------------------------



    //--------------------------------------------
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




//*****************************************************************************************************



int main()
{
    //Определите для класса Rational операторы сложения, вычитания, умножения и деления, так чтобы объекты типа Rational можно было складывать
    //(вычитать, умножать и делить) не только друг с другом но и с целыми числами.
    Rational var1(2, 4), var2(2, 5), result;
    int temp = 4;
    result = var2 / 2 / 2;
    cout << result.to_double() << endl;
    result = temp / var1;
    cout << result.to_double() << endl;



    return 0;
}

