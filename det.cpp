#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <iostream>

using namespace std;
using std::printf;

class Matrix
{
public:
    // конструктори
    Matrix()
    {
        // створюємо матрицю без змісту
        p = NULL;
        rows = 0;
        cols = 0;
    }
    Matrix(const int row_count, const int column_count)
    {
        // створюємо матрицю із заданим числом стовпців і рядків
        p = NULL;

        if (row_count > 0 && column_count > 0)
        {
            rows = row_count;
            cols = column_count;

            p = new double*[rows];
            for (int r = 0; r < rows; r++)
            {
                p[r] = new double[cols];

                // обнуляємо значення матриці
                for (int c = 0; c < cols; c++)
                {
                    p[r][c] = 0;
                }
            }
        }
    }
    // оператор присвоювання
    Matrix(const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            //копіюємо значення з матриці А
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
    }

    // оператор для індексів значень матриці
           double& operator()(const int r, const int c)
	{
      	if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
      	{
          	return p[r-1][c-1];
        }
      	else
      	{
            prinf("Індекс знаходиться за діапазоном матриці\n");
        }
    }

    // оператор присвоювання
    Matrix& operator= (const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            //копіює значення з матриці А
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
        return *this;
    }

    // оператор суми
    friend Matrix operator+(const Matrix& a, const Matrix& b)
    {
        // перевірка відповідності розмірів матриць
        if (a.rows == b.rows && a.cols == b.cols)
        {
         	Matrix res(a.rows, a.cols);

            for (int r = 0; r < a.rows; r++)
            {
                for (int c = 0; c < a.cols; c++)
                {
                    res.p[r][c] = a.p[r][c] + b.p[r][c];
                }
            }
         	return res;
        }
        else
        {
            // помилка
            printf("Розміри матриць не співпадають\n");
        }
        // повертає порожню матрицю
        return Matrix();
    }
    // оператор віднімання
    friend Matrix operator- (const Matrix& a, const Matrix& b)
    {
        // перевірка відповідності матриць
        if (a.rows == b.rows && a.cols == b.cols)
        {
         	Matrix res(a.rows, a.cols);

            for (int r = 0; r < a.rows; r++)
            {
                for (int c = 0; c < a.cols; c++)
                {
                    res.p[r][c] = a.p[r][c] - b.p[r][c];
                }
            }
         	return res;
        }
        else
        {
            // помилка
            printf("Розміри матриць не співпадають\n");
        }
    // оператор протилежного кожного значення матриці
    friend Matrix operator- (const Matrix& a)
    {
     	Matrix res(a.rows, a.cols);

        for (int r = 0; r < a.rows; r++)
        {
            for (int c = 0; c < a.cols; c++)
            {
                res.p[r][c] = -a.p[r][c];
            }
        }

        return res;
    }

    // оператор множення
    friend Matrix operator* (const Matrix& a, const Matrix& b)
    {
        // перевірка відповідності матриць
        if (a.cols == b.rows)
        {
         	Matrix res(a.rows, b.cols);

            for (int r = 0; r < a.rows; r++)
            {
                for (int c_res = 0; c_res < b.cols; c_res++)
                {
                    for (int c = 0; c < a.cols; c++)
                    {
                        res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
                    }
                }
            }
         	return res;
        }
        else
        {
            // помилка
            printf("Розміри матриць не співпадають\n");
        }
        // повертає порожню матрицю
        return Matrix();
    }

    //  повертає мінор матриці, де вибрані значення будуть видалені
    Matrix Minor(const int row, const int col)
    {
        Matrix res;
      	if (row > 0 && row <= rows && col > 0 && col <= cols)
      	{
            res = Matrix(rows - 1, cols - 1);

            // скопіювати значення матриці до мінору, крім вибраних
            for (int r = 1; r <= (rows - (row >= rows)); r++)
            {
                for (int c = 1; c <= (cols - (col >= cols)); c++)
                {
                    res(r - (r > row), c - (c > col)) = p[r-1][c-1];
                }
            }
        }
        else
        {
            printf("Індекс знаходиться за діапазоном матриці\n");
        }

        return res;
    }

    // повертає i-ий розмір матриці
    //якщо i=1 функція повертає кількість рядків матриці,
    // якщо i=1 функція повертає кількість стовпців матриці,
    //в іншому випадку функція повертає 0
    int Size(const int i)
    {
        if (i == 1)
        {
            return rows;
        }
        else if (i == 2)
        {
            return cols;
        }
        return 0;
    }

    // повертає кількість рядків матриці
    int GetRows()
    {
        return rows;
    }

    //повертає кількість стовпців матриці
    int GetCols()
    {
        return cols;
    }

    // виводить вміст матриці
    void Print()
    {
        if (p != NULL)
        {
            printf("[");
            for (int r = 0; r < rows; r++)
            {
                if (r > 0)
                {
                    printf(" ");
                }
                for (int c = 0; c < cols-1; c++)
                {
                    printf("%.2f, ", p[r][c]);
                }
                if (r < rows-1)
                {
                    printf("%.2f;\n", p[r][cols-1]);
                }
                else
                {
                    printf("%.2f]\n", p[r][cols-1]);
                }
            }
        }
        else
        {
            // порожня  матриця
            printf("[ ]\n");
        }
    }

public:
    // деструктор
    ~Matrix()
    {
        // очищає виділену память
        for (int r = 0; r < rows; r++)
        {
            delete p[r];
        }
        delete p;
        p = NULL;
    }



/*
 * повертає детермінант матриці А
 */
double Det(Matrix& a)
{
    double d = 0;       // значення детермінанта
    int rows = a.GetRows();
    int cols = a.GetCols();

    if (rows == cols)
    {
        // для квадратної матриці
        if (rows == 1)
        {
            // для матриці 1 x 1
            d = a(1, 1);
        }
        else if (rows == 2)
        {
            // для матриці 2 x 2 
            d = a(1, 1) * a(2, 2) - a(2, 1) * a(1, 2);
        }
        else
        {
            // для матриці3 x 3 або більше
            for (int c = 1; c <= cols; c++)
            {
                Matrix M = a.Minor(1, c);
                d += pow(-1, 1+c)  * a(1, c) * Det(M);
            }
        }
    }
    else
    {
        printf("Матриця повинна бути квадратною\n");
    }
    return d;
}

void Transp(Matrix& a)// транспонування матриці
double temp;
int rows = a.GetRows();
int cols = a.GetCols();
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++)
      {
      temp = a.p[r][c];
      a.p[r][c] = a.p[c][r];
      a.p[c][r] = temp;
      }
    }
}

/*
 * повертає обернену матрицю
 */
Matrix Inv(Matrix& a)
{
    Matrix res;
    double d = 0;       // значення детермінанта
    int rows = a.GetRows();
    int cols = a.GetCols();

    d = Det(a);
    if (rows == cols && d != 0)
    {
        // для квадратної матриці
        if (rows == 1)
        {
            // для матриці 1 x 1
            res = Matrix(rows, cols);
            res(1, 1) = 1 / a(1, 1);
        }
        else 
        {
        //для матриці 2 x 2 ш більше
         Matrix ai = a;        //робить копію матриці А
         int res;
          for (int r = 1; r <= rows; r++)
             { for (int c = 1; c <= cols; c++)
               { Matrix M = a.minor(r, c);
                 res= pow(-1, r+c)  * a(r, c);
                    res[r][c]=a.Transp(res);
                    d=Det(ai);
                    p[r][c]=res[r][c]/d;
                }
         }
    else
    {
        if (rows == cols)
        {
            printf("Матриця повинна бути квадратною\n");
        }
        else
        {
            printf("Детермінант матриці дорівнює 0\n");
        }
    }
    return res;
}


int main(int argc, char *argv[])
{
        // створюємо матрицю 3x3 (з значеннями 0)
        int cols = 3;
        int rows = 3;
        Matrix A = Matrix(cols, rows);

        // надаємо деякого значення матриці А
        int count = 0;
        for (int r = 1; r <= rows; r++)
        {
            for (int c = 1; c <= cols; c++)
            {
                count ++;
                A(r, c) = count;
            }
        }
         // присвоює значення за індексом
        A(2,1) = 4.33;
          // зчитує значення за індексом
        double value = A(1,2);
        printf("Znachennya = %f \n", value);
        printf("\n");
        // виводить матрицю
        printf("A = \n");
        A.Print();
        printf("\n");

        Matrix C;
        C = A + B;
        printf("A + B = \n");
        C.Print();
        printf("\n");

        C = A - B;
        printf("A - B = \n");
        C.Print();
        printf("\n");

        C = A * B;
        printf("A * B2 = \n");
        C.Print();
        printf("\n");

        // обчислює детермінант
        Matrix D = Matrix(2, 2);
        D(1,1) = 2;
        D(1,2) = 4;
        D(2,1) = 1;
        D(2,2) = -2;
        printf("D = \n");
        D.Print();
        printf("Det(D) = %f\n\n", Det(D));

        printf("A = \n");
        A.Print();
        printf("\n");
        printf("Det(A) = %f\n\n", Det(A));
    PAUSE;
    return EXIT_SUCCESS;
}
