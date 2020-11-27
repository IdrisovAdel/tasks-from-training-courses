#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <algorithm>
using namespace std;


struct String
{
    String(const char *str = "") : Size(strlen(str)), str(new char [Size + 1])
    {
        strcpy(this->str, str);
    }

    String(size_t n, char c) : Size(n), str(new char [Size + 1])
    {
        unsigned temp = 0;
        for( ; temp < n; ++temp)
        {
            str[temp] = c;
        }
        str[temp] = '\0';
    }

    String(const String &other) : Size(other.Size), str(new char [Size + 1])
    {
        for(unsigned temp = 0; temp < Size + 1; ++temp)
        {
            str[temp] = other.str[temp];
        }
    }

    ~String()
    {
        delete[] str;
    }

    String & operator=(const String &other)
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
    class Proxy
    {
    public:
        Proxy(String const & line, int const from) : var1(line), from(from)
        {
        }

        String operator[](int to)
        {
            String substring(to - from, ' ');
            int i = 0;
            for(int iter = from; iter < to; ++iter)
            {
                substring.str[i++] = var1.str[iter];
            }
            substring.Size = to - from;
            return substring;
        }
        const String & var1;
        int from;
    };
    Proxy operator[](int from) const
    {
        Proxy temp1(*this, from);
        return temp1;
    }
    size_t Size;
    char *str;
};




int main()
{
    //� ���� ������ ��� ��������� ����������� �������� [] ��� ��� ���������� ��� ������ String. ������ �� ���� ��� �������� ������ ������������� �������������
    //���������: �������� ����� ����������� ����� �������, ����� ��� ������� str ������ String ����� ���� ������ str[i][j] � ��� ��������� ���������� ���������
    //������������ � ������� i (������ � 0) � ��������������� � ������� j (�� �������). ��������: String const hello("hello"); String const hell = hello[0][4];
    // ������ � hell �������� ��������� "hell". String const ell  = hello[1][4]; // ������ � ell �������� ��������� "ell". �������� ��������, ��� i �����
    //��������� j, � ���� ������ ����������� ������ ���� ������ ������. �������������, ��� i ������� �� ����� ������ j, � ��� �� ����� �������� �� �������
    //����� ������.
    String hello = "hello", var2;
    var2 = hello[1][5];
    String const hell = hello[0][4];
    cout << hell.Size << ' ' << hell.str << endl;




    return 0;
}
