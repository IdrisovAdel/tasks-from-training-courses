#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;



struct String {

    /* ���������� ���� ����������� */
	String(const char *str = "") : Size(strlen(str)), str(new char [Size + 1])
	{
        strcpy(this->str, str);
	}
	 /* ���������� ���� ����������� */
	String(size_t n, char c) : Size(n), str(new char [Size + 1])
	{
	    unsigned temp = 0;
	    for( ; temp < n; ++temp)
        {
            str[temp] = c;
        }
        str[temp] = '\0';
	}
	/* ���������� ����������� ����������� */
	String(const String &other) : Size(other.Size), str(new char [Size + 1])
	{
	    for(unsigned temp = 0; temp < Size + 1; ++temp)
        {
            str[temp] = other.str[temp];
        }
	}
    /* � ���������� */
	~String()
	{
	    delete[] str;
	}
	/* ���������� ���� �����. */
	/* ���������� �������� ������������ */
	String &operator=(const String &other)
	{
	    if(&other != this)
        {
            String temp(other);
            (*this).Swap(temp);
        }
        return *this;
	}
	void Swap(String &other)
	{
	    swap(this->Size, other.Size);
	    swap(this->str, other.str);
	}
	void append(String &other)
	{
	    char * str1 = new char[Size + other.Size + 1];
	    strcpy(str1, str);
	    strcat(str1, other.str);
        delete[] str;
        str = new char[Size + other.Size + 1];
        Size += other.Size;
        strcpy(str, str1);
        delete[] str1;
	}

	size_t Size;
	char *str;
};


 // ����� Cls ��������� ����� ����� �������:
struct Cls
{
    Cls(char c, double d, int i) : c(c), d(d), i(i) {}
private:
    char c;
    double d;
    int i;
};
struct ClsCopy
{
    ClsCopy(char c, double d, int i) : c(c), d(d), i(i) {}
    char c;
    double d;
    int i;
};
// ��� ������� ������ ������������ ������ � ���� c ������� cls.
// �������� ��������, ��� ������������ ������ �� char, �. �.
// ������ ��������������� �� ������ � ������.
char &get_c(Cls &cls) {
    void * temp = (void *)&cls;
    ClsCopy * myStructCopy = (ClsCopy *)temp;
    return (*myStructCopy).c;
}

// ��� ������� ������ ������������ ������ � ���� d ������� cls.
// �������� ��������, ��� ������������ ������ �� double, �. �.
// ������ ��������������� �� ������ � ������.
double &get_d(Cls &cls) {
    void * temp = (void *)&cls;
    ClsCopy * myStructCopy = (ClsCopy *)temp;
    return (*myStructCopy).d;
}

// ��� ������� ������ ������������ ������ � ���� i ������� cls.
// �������� ��������, ��� ������������ ������ �� int, �. �.
// ������ ��������������� �� ������ � ������.
int &get_i(Cls &cls) {
    void * temp = (void *)&cls;
    ClsCopy * myStructCopy = (ClsCopy *)temp;
    return (*myStructCopy).i;
}


struct Foo
{
    void say() const
    {
        std::cout << "Foo says: " << msg << "\n";
    }
protected:
    Foo(const char *msg) : msg(msg) { }
private:
    const char *msg;
};

struct neededFoo : Foo
{
    neededFoo(const char * message) : Foo(message)
    {
    }
};

void foo_says(const Foo &foo)
{
    foo.say();
}

neededFoo get_foo(const char *msg)
{
    neededFoo temp(msg);
    return temp;
}

//*************************************************************************************************************************************************
struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression(){};
};

struct Number : Expression
{
    Number(double value) : value(value) {}
    virtual ~Number(){}
    virtual double evaluate() const
    {
        return value;
    }
private:
    double value;
};

struct BinaryOperation : Expression
{
    BinaryOperation(Expression const * left, char op, Expression const * right) : left(left), right(right), op(op) {}
    virtual ~BinaryOperation()
    {
        delete left;
        delete right;
    }
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
private:
    Expression const * left;
    Expression const * right;
    char op;
};


//*****************************************************************************************************

int check_equals(Expression const *left, Expression const *right)
{
    void * temp1Left = (void*) left;
    int * temp2Left = (int *) temp1Left;
    void * temp1Right = (void*) right;
    int * temp2Right = (int *) temp1Right;
    return * temp2Left == * temp2Right;
}


int main()
{
    //� ���� ������ ��� ��������� ����������� �����������, ������� ��������� �� ���� C-style ������, ��������� �� ������ (��� ����� ������������ 0 �������) �
    //��������� ��� � ���� size, ����� ����, ����������� ������ ������������ ������ ����������� ��� �������� ����� ���������� ������ (������ � ����������� 0
    //��������), �������� ���������� ������ � ���������� ������ � ��������� ��������� �� ������ ���� ������� ������ � ���� str. �.�. � ���������� ������ ������������
    //� ���� str ������ ��������� ��������� �� C-������ c ������ �������� ������, � � ���� size � ����� ������ ��� ����� ������������ �������� �������.
    /*char word[] = "hello";
    String str(word);
    cout << str.Size << " " << str.str;*/

    //������������� � ��������� ����� ���� ���������. ��� ������ ����� ��������� �������� ����������� ����������� (��������, ����� ������� ������ ��������).
    //����������� ����������� ��������� ����� � ������, � ������� ������ � �������� ����������� ���������� ����������� �������. ������� ���������� �� ����������
    //������������ �� �� ����� (� ���� size ������ ��� ����� ������������ 0 �������, � ���� str C-style ������, �.�. � ����������� 0 ��������). ����� ������������
    //� ���� ������ ��� ����� ����� ����������� � ����������, ������� ��������� ���������� ������.
    /*String str(5, 'a');
    cout << str.Size << " " << str.str;*/


    //�������� ������ ������ ����� ��������� ����� append � �� ��������� ����� ������-��������� � ����� ������� ������ (�.�. � ����� ������, � ������� ��
    //��� ������). String s1("Hello,");String s2(" world!"); s1.append(s2); // ������ s1 ������ "Hello, world!". ���� ������ ����������� ����� append.
    //��� ���������� ������� ������ ��������� ��� ������ � ������� � ��� ������ ������ �� ������ ��������� ������ ������. ����� ����, �� ��������, ��� size
    //������ ������ ��� ����� ������������ 0 �������.
    /*String s1("Hello,");
    String s2(" world!");
    s1.append(s2);
    cout << s1.Size << " " << s1.str;*/


    //��� �����, ��� ���� ����� ������ ��������, ���� ������ ����������� ��������� �������, ������� ���� ������ ������ � ���� ����� (��. ������ ����),
    //�������� �� ��, ��� ��� ��������.(������� ����������� ����� ����� ������ Cls)/
    /*char symbol = 'p';
    double pi = 3.14;
    int number = 5;
    Cls myStruct = Cls(symbol, pi, number);
    cout << get_c(myStruct);*/


    //�������� � ����� String ���������� ������������ �����������. ��������� ������ �������� ��� �� (� size �������� ������ ������ ��� ������������ 0 �������,
    //str ��������� �� C-style ������, �. �. � ����������� ������� ��������).
    /*String word = String("hellow sparrow!");
    String newWord = String(word);
    cout << newWord.Size << " " << newWord.str << endl;
    String otherWord = word;
    cout << otherWord.Size << " " << otherWord.str << endl;*/


    //��������� ����� String, ������� � ���� �������� ������������. ������ ��������� ��� ������ � �������. ��������� ������ �������� ��� �� (� size ��������
    //������ ������ ��� ������������ 0 �������, str ��������� �� C-style ������, �. �. � ����������� ������� ��������).
    /*String word("hellow sparrow!");
    String newWord("nu privet!");
    newWord = word;
    cout << newWord.Size << " " << newWord.str << endl;*/


    //��� ����� ���������� ������� get_foo, ��� ������� � �������, ����� �������������� � ������� ��� ��������� ��������� ���: foo_says(get_foo("Hello!"));
    /*foo_says(get_foo("Hello!"));*/


    //� ���� ������� ��� ������������ ����������� �������� ������� Expression ��� ������������� �������������� ���������. ����������, ��� ����� ����������
    //��� ������: Expression � ������� ����� ��������, Number � ��� ������������� ����� � BinaryOperation � ����� ����������� �������� �������� (+, �-, * ��� /).
    //����� Number ������ ������� �������� ���� double. ����� BinaryOperation ������ ������� ��������� �� ����� � ������ ��������, ������� ���� ��������
    //��������������� �����������, � ����� ��� �������� (+, �-, * ��� /), ������� ����� ��� ���� ����������.�� ���� ������� ������ ���� ����� evaluate,
    //������� ���������� �������� ���� double � �������� ���������������� ��������������� ���������, ��������, �������� ���������� ���� Number � ��� �����,
    //������� �� ������, � ���� � ��� ���� ������ BinaryOperation � ��������� +, �� ����� ��������� �������� ������ � ������� �������� � ������� �� �����.

    // ������� ������ ������� ��� ������������ 4.5 * 5
    /*Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    // ����� ���������� ��� � ��������� ��� +
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);

    // ��������� � ������� ���������: 25.5
    std::cout << expr->evaluate() << std::endl;

    // ��� ������������� *���* ���������� �������
    // (��������, sube ����� ������ ��������� expr, ������� ��� ������� �� �����)
    delete expr;*/


    //��� ��������� ����������� �������, ������� ��������� �� ���� ��� ��������� �� ������� ����� Expression, � ���������� true, ���� ��� ���������
    //��������� �� ����� ���� �� ������� ������ � ���� �� ������, � false � ��������� ������ (�.�. ���� ��� ��������� ��������� �� BinaryOperation, ��
    //������������ true, � ���� ���� �� ��� ��������� �� Number, � ������ �� BinaryOperation, �� false).
    Expression * sube1 = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression * sube2 = new BinaryOperation(new Number(4), '+', new Number(9));
    Expression * num1 = new Number(6);
    Expression * num2 = new Number(9);
    cout << "bool = " << check_equals(sube1, sube2) << endl;
    cout << "bool = " << check_equals(sube2, sube1) << endl;
    cout << "bool = " << check_equals(num1, num2) << endl;
    cout << "bool = " << check_equals(num2, num2) << endl;

    return 0;
}
