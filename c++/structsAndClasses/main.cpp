#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;



struct String {

    /* Реализуйте этот конструктор */
	String(const char *str = "") : Size(strlen(str)), str(new char [Size + 1])
	{
        strcpy(this->str, str);
	}
	 /* Реализуйте этот конструктор */
	String(size_t n, char c) : Size(n), str(new char [Size + 1])
	{
	    unsigned temp = 0;
	    for( ; temp < n; ++temp)
        {
            str[temp] = c;
        }
        str[temp] = '\0';
	}
	/* Реализуйте конструктор копирования */
	String(const String &other) : Size(other.Size), str(new char [Size + 1])
	{
	    for(unsigned temp = 0; temp < Size + 1; ++temp)
        {
            str[temp] = other.str[temp];
        }
	}
    /* и деструктор */
	~String()
	{
	    delete[] str;
	}
	/* Реализуйте этот метод. */
	/* Реализуйте оператор присваивания */
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


 // Класс Cls определен точно таким образом:
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
// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    void * temp = (void *)&cls;
    ClsCopy * myStructCopy = (ClsCopy *)temp;
    return (*myStructCopy).c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    void * temp = (void *)&cls;
    ClsCopy * myStructCopy = (ClsCopy *)temp;
    return (*myStructCopy).d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
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
    //В этой задаче вам требуется реализовать конструктор, который принимает на вход C-style строку, вычисляет ее размер (без учета завершающего 0 символа) и
    //сохраняет его в поле size, кроме того, конструктор должен аллоцировать память достаточную для хранения копии переданной строки (вместе с завершающим 0
    //символом), копирует переданную строку в выделенную память и сохраняет указатель на начало этой области памяти в поле str. Т.е. в результате работы конструктора
    //в поле str должен оказаться указатель на C-строку c копией исходной строки, а в поле size — длина строки без учета завершающего нулевого символа.
    /*char word[] = "hello";
    String str(word);
    cout << str.Size << " " << str.str;*/

    //Конструкторов у структуры может быть несколько. Для строки может оказаться полезным заполняющий конструктор (например, чтобы создать строку пробелов).
    //Заполняющий конструктор принимает число и символ, и создает строку с заданным количеством повторений переданного символа. Условия налагаемые на реализацию
    //конструктора те же самые (в поле size размер без учета завершающего 0 символа, в поле str C-style строка, т.е. с завершающим 0 символом). Кроме конструктора
    //в этой задаче вам нужно также реализовать и деструктор, который освободит выделенную память.
    /*String str(5, 'a');
    cout << str.Size << " " << str.str;*/


    //Примером такого метода может послужить метод append — он добавляет копию строки-аргумента в конец текущей строки (т.е. в конец строки, у которой он
    //был вызван). String s1("Hello,");String s2(" world!"); s1.append(s2); // теперь s1 хранит "Hello, world!". Ваша задача реализовать метод append.
    //При выполнении задания будьте аккуратны при работе с памятью — при вызове метода не должно возникать утечек памяти. Кроме того, не забудьте, что size
    //хранит размер без учета завершающего 0 символа.
    /*String s1("Hello,");
    String s2(" world!");
    s1.append(s2);
    cout << s1.Size << " " << s1.str;*/


    //Как видно, все поля этого класса закрытые, ваша задача реализовать несколько функций, которые дают полный доступ к этим полям (см. шаблон кода),
    //несмотря на то, что они закрытые.(функции реализованы сразу после класса Cls)/
    /*char symbol = 'p';
    double pi = 3.14;
    int number = 5;
    Cls myStruct = Cls(symbol, pi, number);
    cout << get_c(myStruct);*/


    //Добавьте в класс String реализацию конструктора копирования. Инвариант класса остается тем же (в size хранится размер строки без завершающего 0 символа,
    //str указывает на C-style строку, т. е. с завершающим нулевым символом).
    /*String word = String("hellow sparrow!");
    String newWord = String(word);
    cout << newWord.Size << " " << newWord.str << endl;
    String otherWord = word;
    cout << otherWord.Size << " " << otherWord.str << endl;*/


    //Завершите класс String, добавив к нему оператор присваивания. Будьте аккуратны при работе с памятью. Инвариант класса остается тем же (в size хранится
    //размер строки без завершающего 0 символа, str указывает на C-style строку, т. е. с завершающим нулевым символом).
    /*String word("hellow sparrow!");
    String newWord("nu privet!");
    newWord = word;
    cout << newWord.Size << " " << newWord.str << endl;*/


    //Вам нужно определить функцию get_foo, как описано в задании, чтобы компилировался и работал как ожидается следующий код: foo_says(get_foo("Hello!"));
    /*foo_says(get_foo("Hello!"));*/


    //В этом задании вам предлагается разработать иерархию классов Expression для представления арифметических выражений. Конкретнее, вам нужно определить
    //три класса: Expression — базовый класс иерархии, Number — для представления чисел и BinaryOperation — класс описывающий бинарную операцию (+, ­-, * или /).
    //Класс Number должен хранить значение типа double. Класс BinaryOperation должен хранить указатель на левый и правый операнды, которые сами являются
    //арифметическими выражениями, а также тип операции (+, ­-, * или /), которую нужно над ними произвести.Во всех классах должен быть метод evaluate,
    //который возвращает значение типа double — значение соответствующего арифметического выражения, например, значение экземпляра типа Number — это число,
    //которое он хранит, а если у вас есть объект BinaryOperation с операцией +, то нужно вычислить значения левого и правого операнда и вернуть их сумму.

    // сначала создаём объекты для подвыражения 4.5 * 5
    /*Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    // потом используем его в выражении для +
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);

    // вычисляем и выводим результат: 25.5
    std::cout << expr->evaluate() << std::endl;

    // тут освобождаются *все* выделенные объекты
    // (например, sube будет правым операндом expr, поэтому его удалять не нужно)
    delete expr;*/


    //Вам требуется реализовать функцию, которая принимает на вход два указателя на базовый класс Expression, и возвращает true, если оба указателя
    //указывают на самом деле на объекты одного и того же класса, и false в противном случае (т.е. если оба указателя указывают на BinaryOperation, то
    //возвращается true, а если один из них указывает на Number, а второй на BinaryOperation, то false).
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
