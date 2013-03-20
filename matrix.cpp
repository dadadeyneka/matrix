//заголовочый код
#ifndef MATRIX_H
#define MATRIX_H
 
#include "array.h"
 
class Matrix
{
    friend ostream &operator<< (ostream &, const Matrix &); // перегруженный оператор вывода
    friend istream &operator>> (istream &, Matrix &); // перегруженный оператор ввода
private:
    Array *memory; // указатель на матрицу типа Array
    int size; // размер матрицы
 
public:
    Matrix();// конструктор по умолчанию
    Matrix(int, int ); // конструктор с параметрами
    Matrix( Matrix &matrixToCopy ); // конструктор копии
    ~Matrix(); // десструктор класса Matrix
 
    int getSize() const; // возвратить количество объектов типа Array
    Array *getMemory() const; // вернуть указатель на объект типа Array
    void setMatrix(); // заполнение матрицы
    void getMatrix(); // вывод матрицы
    Matrix operator+ (const Matrix &a);
    Matrix operator+= (const Matrix &a);
    Matrix operator- (const Matrix &a);
    const Matrix &operator= (const Matrix &a); // оператор присваивания
    bool operator== (const Matrix &a) const;// оператор сравнени
    
};
#endif // MATRIX_H


//исходный код
#include "matrix.h"
 
#include "array.h"
 
#include <iostream>
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin
 
#include <iomanip> // для манипулятора setw
using std::setw;   // пространство имен std для setw
 
#include <cstdlib>
 
Matrix::Matrix() // конструктор по умолчанию
{
    size = 10; // по умолчанию размер матрицы = 10 объектам типа Array
    memory = new Array [size]; // выделить место в памяти для матрицы
    for (int ix = 0; ix < size; ix++) // обнуляем матрицу
        for (int jx = 0; jx < 10; jx++)
            memory[ix][jx] = 0;
}
 
Matrix::Matrix(int matrixSize, int arraySize) // конструктор с параметрами
{
    size = (matrixSize > 0 & matrixSize : 10); // количество строк
 
    memory = new Array [size]; // выделить место в памяти для матрицы
 
    for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
        memory[ix].setSize(arraySize > 0 & arraySize : 10); // количество столбцов
 
    for (int ix = 0; ix < size; ix++) // обнуляем матрицу
        for (int jx = 0; jx < memory->getSize(); jx++)
            memory[ix][jx] = 0;
}
 
Matrix::Matrix(  Matrix &matrixToCopy ) // конструктор копии
    :size(matrixToCopy.size)              // инициализатор размера массива
{
    memory = new Array [size]; // выделить место в памяти для матрицы
 
    for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
        memory[ix].setSize(size); // количество столбцов
 
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            memory[ix][jx] = matrixToCopy[ix][jx];// заполняем матрицу значениями матрицы matrixToCopy
}
 
Matrix::~Matrix() // десструктор класса Matrix
{
   delete  [] memory; // освободить память, удалив матрицу
}
 
int Matrix::getSize() const // возвратить количество элементов матрицы
{
    return size;
}
 
Array *Matrix::getMemory() const
{
    return memory;
}
 
// перегруженный оператор вывода для класса Array (вывод элементов массива на экран)
ostream &operator<< (ostream &output, const Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
    {
        for (int jx = 0; jx < obj.memory->getSize(); jx++)
        {
            output << setw(3) // под каждое число выделяетя 3 позиций
                   << obj.memory[ix][jx];
        }
        cout << std::endl;
    }
 
    output << std::endl; // перенос маркера на новую строку
 
    return output; // позволяет множественный вывод, типа cout << x << y << z << ...
}
 
// перегруженный оператор ввода, для заполнения матрицы с клавиатуры
istream &operator>> (istream & input, Matrix &obj)
{
    for (int ix = 0; ix < obj.size; ix++)
        for (int jx = 0; jx < obj.memory->getSize(); jx++)
            input >> obj.memory[ix][jx]; // заполняем матрицу
 
    return input; // позволяет множественный ввод, типа cin >> x >> y >> z >> ...
}
 
void Matrix::setMatrix() // заполнение массива
{
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            cin >> memory[ix][jx]; // ввод элементов матрицы с клавиатуры
}
 
void Matrix::getMatrix() // вывод массива
{
    for (int ix = 0; ix < size; ix++)
    {
        for (int jx = 0; jx < memory->getSize(); jx++)
            cout << setw(5) << memory[ix][jx]; // вывод элементов матрицы на экран
        cout << std::endl;
    }
 
    cout << std::endl; // новая строка
}
 
Matrix Matrix::operator+ (const Matrix &a)
{
    if (size != a.size || memory->getSize() != a.getMemory()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
    Matrix result(size, memory->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            result.memory[ix][jx] = memory[ix][jx] + a.memory[ix][jx];
 
    return result; // вернуть сумму
}
 
Matrix Matrix::operator+= (const Matrix &a)
{
    if (size != a.size || memory->getSize() != a.getMemory()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
//    Matrix result(size, memory->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            memory[ix][jx] = memory[ix][jx] + a.memory[ix][jx];
 
    return *this; // вернуть сумму
}
 
Matrix Matrix::operator- (const Matrix &right)
{
    if (size != a.size || memory->getSize() != a.getMemory()->getSize())
    {
        cout << "Массивы разного размера!\n";
        exit(1); // завершить работу программы
    }
 
    Matrix result(size, memory->getSize());
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            result.memory[ix][jx] = memory[ix][jx] - a.memory[ix][jx];
 
    return result; // вернуть сумму
}
 
const Matrix &Matrix::operator= (const Matrix &a) // оператор присваивания
{
    if (&a != this) // чтобы не выполнялось самоприсваивание
    {
        if (size != a.size || memory->getSize() != a.getMemory()->getSize())
        {
            delete [] memory; // освободить пространство
            size = a.size; // установить нужный размер матрицы
            memory = new Array [size]; // выделить память под копируемый массив
 
            for (int ix = 0; ix < size; ix++) // перераспределяем выделенную память
                memory[ix].setSize(a.getMemory()->getSize()); // количество столбцов
        }
 
        for (int ix = 0; ix < size; ix++)
            for (int jx = 0; jx < memory->getSize(); jx++)
                memory[ix][jx] = a.memory[ix][jx]; // скопировать массив
    }
 
    return *this; // разрешает множественное присваивание, например x = t = e
}
 
bool Matrix::operator== (const Matrix &a) const// оператор сравнения
{
    if (size != a.size || memory->getSize() != a.getMemory()->getSize())
        return false; // матрицы с разным количеством элементов
 
    for (int ix = 0; ix < size; ix++)
        for (int jx = 0; jx < memory->getSize(); jx++)
            if (memory[ix][jx] != a.memory[ix][jx])
                return false; // матрицы не равны
                
    return true; // матрицы равны
}
