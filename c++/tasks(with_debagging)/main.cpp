#include <iostream>
#include <cstring>
using namespace std;

char *resize(const char *str, unsigned size, unsigned new_size);
char *getline();
int ** transpose(const int * const * m, unsigned rows, unsigned cols);
void print2dMassive(const int * const * m, unsigned rows, unsigned cols);
void swap_min(int *m[], unsigned rows, unsigned cols);
void fill2dMassive(int ** m, unsigned rows, unsigned cols);
int main()
{
    //В этой задаче вам нужно реализовать функцию resize. Функция resize принимает на вход три аргумента: указатель на область памяти, выделенную
    //с помощью оператора new[], размер области (size) и новый размер (new_size). Функция должна выделить память размера new_size, скопировать в нее
    //данные из переданной области памяти, освободить старую область памяти и вернуть выделенную область памяти нового размера со скопированными данными.
    //Обратите внимание, что память, возвращенная из функции, будет освобождена с помощью оператора delete[]. Несмотря на то, что входной тип данных — это
    //const char *, не стоит рассчитывать, что там хранится C-style строка. При выполнении задания также учтите, что new_size может быть меньше size.
    /*unsigned size = 1000, newSize = 1100;
    char * massive = new char[size];
    massive = resize(massive, size, newSize);*/


    //Реализуйте функцию getline, которая считывает поток ввода посимвольно, пока не достигнет конца потока или не встретит символ переноса
    //строки ('\n'), и возвращает C-style строку с прочитанными символами. Обратите внимание, что так как размер ввода заранее неизвестен, то вам
    //нужно будет перевыделять память в процессе чтения, если в потоке ввода оказалось больше символов, чем вы ожидали. Память, возвращенная из функции
    //будет освобождена оператором delete[]. Символ переноса строки ('\n') добавлять в строку не нужно, но не забудьте, что в конце C-style строки должен
    //быть завершающий нулевой символ.
    /*char * massiveChar = 0;
    massiveChar = getline();
    for(uint32_t temp = 0; temp < strlen(massiveChar); ++temp)
    {
        std::cout << massiveChar[temp];
    }
    delete[] massiveChar;*/


    //Напишите функцию, которая принимает на вход целочисленную матрицу M (другими словами, просто двумерный целочисленный массив) размера
    //rows×cols, и возвращает транспонированную матрицу M^T  (тоже двумерный целочисленный массив) размера cols×rows. Если в M на пересечении
    //i-ой строки и j-ого столбца стояло число x, то на пересечении  j-ой строки и i-ого столбца в матрице M^T тоже будет стоять число x, или
    //другими словами M^T[j][i] = M[i][j]. Обратите внимание, что вам неизвестно, каким именно способом выделялась память для
    //массива M. Выделять память под массив M^T можете любым удобным вам способом. Изменять исходную матрицу нельзя.
    /*int ** massive = new int * [3];
    massive[0] = new int[3 * 4];
    for(unsigned temp = 1; temp < 3; ++temp)
    {
        massive[temp] = massive[0] + 4 * temp;
    }
    int fillNumber = 0;
    for(unsigned temp1 = 0; temp1 < 3; ++temp1)
    {
        for(unsigned temp2 = 0; temp2 < 4; ++temp2)
        {
            *(massive[temp1] + temp2) = ++fillNumber;
        }
    }
    int ** transMassive = transpose(massive, 3, 4);
    //output massive
    print2dMassive(massive, 3, 4);
    cout << endl;
    //output transMassive
    print2dMassive(transMassive, 4, 3);
    delete[] transMassive[0];
    delete[] transMassive;
    delete[] massive[0];
    delete[] massive;*/


    //Реализуйте функцию swap_min, которая принимает на вход двумерный массив целых чисел, ищет в этом массиве строку, содержащую наименьшее среди
    //всех элементов массива значение, и меняет эту строку местами с первой строкой массива. Подумайте, как обменять строки массива, не обменивая
    //элементы строк по-отдельности.
    unsigned rows = 3, columns = 4;
    int ** massive = new int * [rows];
    massive[0] = new int [rows * columns];
    for(unsigned temp = 1; temp < rows; ++temp)
    {
        massive[temp] = massive[temp - 1] + columns;
    }
    fill2dMassive(massive, rows, columns);
    print2dMassive(massive, rows, columns);
    cout << endl;
    swap_min(massive, rows, columns);
    print2dMassive(massive, rows, columns);

    delete[] massive[0];
    delete[] massive;






    return 0;
}

void swap_min(int *m[], unsigned rows, unsigned cols)
{
    int minimum = m[0][0];
    unsigned position = 0;
    for(unsigned temp1 = 0; temp1 < rows; ++temp1)
    {
        for(unsigned temp2 = 0; temp2 < cols; ++temp2)
        {

            if(minimum > m[temp1][temp2])
            {
                minimum = m[temp1][temp2];
                position = temp1;
            }
        }
    }
    int * temp = m[0];
    m[0] = m[position];
    m[position] = temp;
}

void fill2dMassive(int ** m, unsigned rows, unsigned cols)
{
    int fillNumber = 0;//rows * cols;
    for(unsigned temp1 = 0; temp1 < rows; ++temp1)
    {
        for(unsigned temp2 = 0; temp2 < cols; ++temp2)
        {
            m[temp1][temp2] = fillNumber++;
        }
    }
}

void print2dMassive(const int * const * m, unsigned rows, unsigned cols)
{
    for(unsigned temp1 = 0; temp1 < rows; ++temp1)
    {
        for(unsigned temp2 = 0; temp2 < cols; ++temp2)
        {
            cout << m[temp1][temp2] << " ";
        }
        cout << endl;
    }
}

int ** transpose(const int * const * m, unsigned rows, unsigned cols)
{
    int ** massive = new int * [cols];
    massive[0] = new int[cols * rows];
    for(unsigned temp = 1; temp < cols; ++temp)
    {
        massive[temp] = massive[temp - 1] + rows;
    }
    for(unsigned temp1 = 0; temp1 < rows; ++temp1)
    {
        for(unsigned temp2 = 0; temp2 < cols; ++ temp2)
        {
            massive[temp2][temp1] = m[temp1][temp2];
        }
    }
    return massive;
}


char *getline()
{
    char byte = 0;
    //scanf("%c", &byte);
    unsigned massiveSize = 25;
    char * massive = new char[massiveSize];
    for(unsigned temp = 0; byte != '\n' && std::cin.get(byte); ++temp)
    {
        //std::cin.get(byte);
        if(temp == massiveSize - 2)
        {
            massive = resize(massive, massiveSize, massiveSize * 2 * sizeof(char));
            massiveSize *= (2 * sizeof(char));
        }
        massive[temp] = byte;
        massive[temp + 1] = '\0';
        //scanf("%c", &byte);
    }
    return massive;
}

char *resize(const char *str, unsigned size, unsigned new_size)
{
    char * newMassive = new char[new_size];
    for(uint32_t temp = 0; temp < new_size; ++temp)
    {
        if(temp < size) newMassive[temp] = str[temp];
        else newMassive[temp] = 0;
    }
    delete[] str;
	return newMassive;
}
