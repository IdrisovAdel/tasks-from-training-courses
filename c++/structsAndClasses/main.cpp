#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;


//*************************************************************************************************************************************************
struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {}
};

struct Number : Expression
{
    Number(double value) : value(value) {}
    virtual ~Number() {}
    double evaluate() const
    {
        return value;
    }

    double get_value() const { return value; }
private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right) : left(left), right(right), op(op) {}
    ~BinaryOperation()
    {
        delete left;
        delete right;
    };
    double evaluate() const
    {
        switch(op)
        {
        case '+':
            return left->evaluate() + right->evaluate();
        case '-':
            return left->evaluate() - right->evaluate();
        case '*':
            return left->evaluate() * right->evaluate();
        case '/':
            return left->evaluate() / right->evaluate();
        }
        return 0;
    }

    Expression const * get_left() const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }
private:
    Expression const * left;
    Expression const * right;
    char op;
};

//*****************************************************************************************************
struct SharedPtr
{
    explicit SharedPtr(Expression *ptr = 0) : ptr_(ptr)
    {
        if(ptr != nullptr)
        {
            counter = new int;
            *counter = 1;
        }
        else
        {
            counter = nullptr;
        }
    }

    ~SharedPtr()
    {
        clearPtr();
    }

    SharedPtr(const SharedPtr & other) : ptr_(other.ptr_)
    {
        if(ptr_ != nullptr)
        {
            counter = other.counter;
            ++(*counter);
        }
        else
        {
            counter = nullptr;
        }
    }

    SharedPtr& operator=(const SharedPtr & other)
    {
        if(this != &other)
        {
            clearPtr();
            counter = other.counter;
            if(counter != nullptr)
            {
                ++(*counter);
            }
            ptr_ = other.ptr_;

        }
        return *this;
    }
    Expression* get() const
    {
        return ptr_;
    }

    void reset(Expression *ptr = 0)
    {
        *this = SharedPtr(ptr);
    }
    Expression& operator*() const
    {
        return *ptr_;
    }
    Expression* operator->() const
    {
        return ptr_;
    }
private:

    void clearPtr()
    {
        if(counter != nullptr)
        {
            --(*counter);
            if(*counter <= 0)
            {
                delete counter;
                delete ptr_;
            }
        }
    }
    Expression * ptr_;
    int * counter;
};


int main()
{

    //*************************************************************************************************************************************************
    //Ваш класс должен печатать (используя std::cout) текстовое представление арифметического выражения. Т.е. для объекта класса Number он должен напечатать число,
    //которое в нем хранится, а для объекта класса BinaryOperation он должен напечатать левый операнд, затем операцию, а затем правый операнд.Учтите, что
    //операции + и - имеют меньший приоритет, чем операции * и /, т. е. возможно вам придется печатать дополнительные круглые скобки, чтобы сохранить правильный
    //порядок операций.
    /*Expression * num = new Number(5);
    PrintVisitor  visitor;
    num->visit(&visitor);
    cout << endl;
    Expression * expr = new BinaryOperation(new Number(1), '+', new Number(2));
    Expression * expr2 = new BinaryOperation(expr, '*', new Number(3));
    expr2->visit(&visitor);
    cout << " = " << expr2->evaluate();*/

    //Реализуйте класс SharedPtr как описано ранее. Задание немного сложнее, чем кажется на первый взгляд. Уделите особое внимание "граничным случаям" — нулевой
    //указатель, присваивание самому себе, вызов reset на нулевом SharedPtr и прочее. Подсказка: возможно, вам понадобится завести вспомогательную структуру.
    SharedPtr p1;
    SharedPtr p2(new Number(6));
    //SharedPtr p2(new BinaryOperation(new Number(5), '+', new Number(2)));
    SharedPtr p3(new BinaryOperation(new Number(1), '+', new Number(2)));
    SharedPtr p4(p2);
    SharedPtr p5;
    p5 = p2;
    p5 = p4;
    p1 = p5;
    p3.reset(NULL);
    p3 = p5;
    p5.reset(NULL);
    SharedPtr p6;
    SharedPtr p7;
    p7 = p7;
    p7.reset(NULL);
    p7.reset(new BinaryOperation(new Number(2), '+', new Number(3)));
    SharedPtr p8(new BinaryOperation(new Number(4), '+', new Number(5)));
    p8.reset(NULL);
    p1 = p1;
    return 0;
}

