#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;


//*************************************************************************************************************************************************
struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * vistitor) const = 0;
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

    void visit(Visitor * visitor) const { visitor->visitNumber(this); }

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

    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

struct PrintVisitor : Visitor {
    void visitNumber(Number const * number)
    {
        cout << number->get_value();
    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        cout << "(";
        bop->get_left()->visit(this);
        cout << " " << bop->get_op() << " ";
        bop->get_right()->visit(this);
        cout << ")";
    }
};


//*****************************************************************************************************



int main()
{

    //Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает true, если оба указателя
    //указывают на самом деле на объекты одного и того же класса, и false в противном случае (т.е. если оба указателя указывают на BinaryOperation, то
    //возвращается true, а если один из них указывает на Number, а второй на BinaryOperation, то false).
    /*Expression * sube1 = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression * sube2 = new BinaryOperation(new Number(4), '+', new Number(9));
    Expression * num1 = new Number(6);
    Expression * num2 = new Number(9);
    cout << "bool = " << check_equals(sube1, sube2) << endl;
    cout << "bool = " << check_equals(sube2, sube1) << endl;
    cout << "bool = " << check_equals(num1, num2) << endl;
    cout << "bool = " << check_equals(num2, num2) << endl;*/

    //*************************************************************************************************************************************************
    //Ваш класс должен печатать (используя std::cout) текстовое представление арифметического выражения. Т.е. для объекта класса Number он должен напечатать число,
    //которое в нем хранится, а для объекта класса BinaryOperation он должен напечатать левый операнд, затем операцию, а затем правый операнд.Учтите, что
    //операции + и - имеют меньший приоритет, чем операции * и /, т. е. возможно вам придется печатать дополнительные круглые скобки, чтобы сохранить правильный
    //порядок операций.
    Expression * num = new Number(5);
    PrintVisitor  visitor;
    num->visit(&visitor);
    cout << endl;
    Expression * expr = new BinaryOperation(new Number(1), '+', new Number(2));
    Expression * expr2 = new BinaryOperation(expr, '*', new Number(3));
    expr2->visit(&visitor);
    cout << " = " << expr2->evaluate();


    return 0;
}

