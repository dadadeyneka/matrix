#include <cstdlib>
#include <cstdio>
#include <math.h>

using namespace std;

class Matrix
{
public:
    //  конструктори
    Matrix()
    {
        // створюємо матрицю без вмісту
        p = NULL;
        rows = 0;
        cols = 0;
    }
    Matrix(const int row_count, const int column_count)
    {
        // ñстворюємо матрицю із заданим числом стовпчиків і рядків
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

            // копіюємо значення з матриці А
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
    }

    // опеатор для індексів значень матриці
	double& operator()(const int r, const int c)
	{
      	if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
      	{
          	return p[r-1][c-1];
        }
      	else
      	{
             printf("Індекс матриці знаходиться поза діапазоном\n");
        }
    }

    // оператор присвоювання значень елементам матриці
    Matrix& operator= (const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            // копіюємо значення з матриці А
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

    // оператор різниці
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

        // повертає порожню матрицю
        return Matrix();
    }
    // оператор протилежного знаку кожного елемента матриці
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

    // оператор добутку
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

        //  повертає порожню матрицю
        return Matrix();
    }

    // повертає мінор матриці, де вибрані елементи будуть видалені
    Matrix Minor(const int row, const int col)
    {
        Matrix res;
      	if (row > 0 && row <= rows && col > 0 && col <= cols)
      	{
            res = Matrix(rows - 1, cols - 1);

            // скопіюємо значення  матриці
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
           printf(" Індекс знаходиться поза діапазоном матриці\n");
        }

        return res;
    }

    // повертає і-ий розмір матриці
    // якщо і=1 функція повертає кількість рядків
    // якщо і=2 функція повертає кількість стовпців
    // в іншому випадку функція повертає 0
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

    // повертає кількість стовпців матриці
    int GetCols()
    {
        return cols;
    }

// транспортування матриці
void Transp(Matrix& a)
{
double temp;
int rows = a.GetRows();
int cols = a.GetCols();
    for (int r = 0; r < rows; r++)
    {
      for (int c = 0; c < cols; c++)
      {
      temp = p[r][c];
      p[r][c] = p[c][r];
      p[c][r] = temp;
      }
    }
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
                    printf("%.2f ", p[r][c]);
                }
                if (r < rows-1)
                {
                    printf("%.2f \n", p[r][cols-1]);
                }
                else
                {
                    printf("%.2f] \n", p[r][cols-1]);
                }
            }
        }
        else
        {
            // порожня матриця
            printf("[ ]\n");
        }
    }

public:
    // деструктор
    ~Matrix()
    {
        // очищає виділену пам'ять
        for (int r = 0; r < rows; r++)
        {
            delete p[r];
        }
        delete p;
        p = NULL;
    }

private:
    int rows;
    int cols;
    double** p;         // вказівник на матрицю з double
};

/*
 * 
 */
int Size(Matrix& a, const int i)
{
    return a.Size(i);
}

/*
 * повертає матрицю розміром cols x rows з значеннями 1
 */
Matrix Ones(const int rows, const int cols)
{
    Matrix res = Matrix(rows, cols);

    for (int r = 1; r <= rows; r++)
    {
        for (int c = 1; c <= cols; c++)
        {
            res(r, c) = 1;
        }
    }
    return res;
}

/*
 *  повертає матрицю розміром cols x rows з значеннями 0
 */
Matrix Zeros(const int rows, const int cols)
{
    return Matrix(rows, cols);
}


Matrix Diag(const int n)
{
    Matrix res = Matrix(n, n);
    for (int i = 1; i <= n; i++)
    {
        res(i, i) = 1;
    }
    return res;
}
/**
 * повертає діагональну матрицю
 */
Matrix Diag(Matrix& v)
{
    Matrix res;
    if (v.GetCols() == 1)
    {
        // отримана матриця є вектором n x 1
        int rows = v.GetRows();
        res = Matrix(rows, rows);

        // копіюємо значення вектора до матриці
        for (int r=1; r <= rows; r++)
        {
            res(r, r) = v(r, 1);
        }
    }
    else if (v.GetRows() == 1)
    {
        // отримана матриця є вектором n x 1
        int cols = v.GetCols();
        res = Matrix(cols, cols);

        // копіюємо значення вектора до матриці
        for (int c=1; c <= cols; c++)
        {
            res(c, c) = v(1, c);
        }
    }
    else
    {
        printf("Параматр для діагоналі має бути вектором\n");
    }
    return res;
}

/*
 * повертає детермінант матриці А
 */
double Det(Matrix& a)
{
    double d = 0;       // значення детермінанта
    int rows = a.GetRows();
    int cols = a.GetRows();

    if (rows == cols)
    {
        // для квадратної матриці
        if (rows == 1)
        {
            //  для матриці 1 x 1
            d = a(1, 1);
        }
        else if (rows == 2)
        {
            // для матриці 2 x 2
            d = a(1, 1) * a(2, 2) - a(2, 1) * a(1, 2);
        }
        else
        {
            // для матриці 3 x 3 або більше
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


/*
 * повертає обернену матрицю
 */
Matrix inv(Matrix& a)
{
    Matrix res;
    double d = 0;       //значення детермінанту
    int rows = a.GetRows();
    int cols = a.GetCols();

    d = Det(a);
    if (rows == cols && d != 0)
    {
        // ??? ?????????? ???????
        if (rows == 1)
        {
            // ??? ??????? 1 x 1 
            res = Matrix(rows, cols);
            res(1, 1) = 1 / a(1, 1);
        }
        else
        {
            // ??? ??????? 3 x 3 ??? ??????
            Matrix ai = a;        // ?????? ???????? ??????? ?
            int res;
      for (int r = 1; r <= rows; r++)
      {for (int c = 1; c <= cols; c++)
                Matrix M = a.Minor(r,c);
                res(r,c)=pow(-1, r+c)*Det(M);
                    // ??????????? ???????? ???????
                    res=a.Transp(res)/Det(ai);
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

        // надаємо деякого значення елементам матриці А
        int count = 0;
        for (int r = 1; r <= rows; r++)
        {
            for (int c = 1; c <= cols; c++)
            {
                count ++;
                A(r, c) = count;
            }
        }

        // присвоюємо значення елементу матриці за індексом
        A(2,1) = 3.45;

        // зчитує значення елементу матриці за індексом
        double value = A(2,2);
        printf("Znachennya = %f \n", value);
        printf("\n");

        // виводить матрицю
        printf("A = \n");
        A.Print();
        printf("\n");

        Matrix B = Ones(rows, cols) + Diag(rows);
        printf("B = \n");
        B.Print();
        printf("\n");

        Matrix B2 = Matrix(rows, 1);        // вектор
        count = 1;
        for (int r = 1; r <= rows; r++)
        {
            count ++;
            B2(r, 1) = count * 2;
        }
        printf("B2 = \n");
        B2.Print();
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

        C = A * B2;
        printf("A * B2 = \n");
        C.Print();
        printf("\n");

        // створюємо діагональну матрицю
        Matrix E = Diag(B2);
        printf("E = \n");
        E.Print();
        printf("\n");

        // обчислюємо детермінант
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
    printf("\n");
    system("PAUSE");
    return EXIT_SUCCESS;
}
