#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;


//*************************************************************************************************************************************************
struct Number;
struct BinaryOperation;

/*struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};*/

struct Expression
{
    virtual double evaluate() const = 0;
    //virtual void visit(Visitor * vistitor) const = 0;
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

    //void visit(Visitor * visitor) const { visitor->visitNumber(this); }

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

    //void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

/*struct PrintVisitor : Visitor {
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
};*/
//*****************************************************************************************************

struct ScopedPtr
{
    explicit ScopedPtr(Expression *ptr = 0) : ptr_(ptr) {}

    ~ScopedPtr()
    {
        delete ptr_;
    }

    //get — возвращает указатель, сохраненный внутри ScopedPtr (например, чтобы передать его в какую-то функцию);
    Expression* get() const
    {
        return ptr_;
    }

    //release — забирает указатель у ScopedPtr и возвращает значение этого указателя, после вызова release ScopedPtr не должен освобождать память (например,
    //чтобы вернуть этот указатель из функции);
    Expression* release()
    {
        Expression * temp = ptr_;
        ptr_ = 0;
        return temp;
    }

    //reset — метод заставляет ScopedPtr освободить старый указатель, а вместо него захватить новый (например, чтобы переиспользовать ScopedPtr,
    //так как оператор присваивания запрещен).
    void reset(Expression *ptr = 0)
    {
        this->~ScopedPtr();
        ptr_ = ptr;
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
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
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

    //Реализуйте ScopedPtr, который будет работать с указателями на базовый класс Expression. В этом задании вам требуется реализовать методы get, release и reset,
    //операторы * и -> так, как это было описано в предыдущем степе. А также реализуйте конструктор ScopedPtr от указателя на Expression.
    //Подсказка: в качестве признака того, что ScopedPtr не хранит никакого указателя (после вызова release), используйте нулевой указатель, при этом вы можете
    //явно проверить указатель в деструкторе, но делать это не обязательно, так как delete от нулевого указателя ничего не делает.

    return 0;
}

