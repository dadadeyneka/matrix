#include <cstdlib>
#include <cstdio>
#include <math.h>

using namespace std;

class Exception {
   public:
      const char* msg;
      Exception(const char* arg) : msg(arg) { };
};


class Matrix
{
public:
    // конструктори
    Matrix()
    {
        // створюємо матрицю без вмісту
        p = NULL;
        rows = 0;
        cols = 0;
    }
    Matrix(const int row_count, const int column_count)
    {
        // створюємо матрицю з заданими рядками і стовпцями
        p = NULL;

        if (row_count > 0 && column_count > 0)
        {
            rows = row_count;
            cols = column_count;

            p = new double*[rows];
            for (int r = 0; r < rows; r++)
            {
                p[r] = new double[rows];

                // обнуляємо всі значення матриці
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

            // копіюємо значення матриці А
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
    }

    //  оператор для індексів значень матриці
  double& operator()(const int r, const int c)
	{
      	if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
      	{
          	return p[r-1][c-1];
        }
      	else
      	{
            throw Exception("ндекс знаходиться за діапазоном матриці");
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
        //перевірка відповідності розмірів матриць
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
            // пьмилка
            throw Exception("Розміри не співпадають");
        }

        //  повертає порожню матрицю
        return Matrix();
    }
    
    //  оператор віднімання
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
            throw Exception("Розміри не співпадають");
        }

        // повертає порожню матрицю
        return Matrix();
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
            //помилка
            throw Exception("Розміри не співпадають");
        }

        //  повертає порожню матрицю
        return Matrix();
    }

    /*
     * повертає мінор матриці, де вибрані значення будуть видалені
     */
    Matrix minor(const int row, const int col)
    {
        Matrix res;
      	if (row > 0 && row <= rows && col > 0 && col <= cols)
      	{
            res = Matrix(rows - 1, cols - 1);

            //  скопіювати значення матриці до мінору, крім вибраних
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
            throw Exception("Індекс знаходиться за діапазоном матриці");
        }

        return res;
    }

    /*
     * повертає i-ий розмір матриці
     * i.e. for i=1 the function returns the number of rows,
     * and for i=2 the function returns the number of columns
     * else the function returns 0
     */
    int size(const int i)
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

    // повертає кількість рядків
    int get_rows()
    {
        return rows;
    }

    // повертає кількість стовпців
    int get_cols()
    {
        return cols;
    }

    // виводить значення матриці
    void print()
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
            // повертає порожню матрицю
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

private:
    int rows;
    int cols;
    double** p;         //вказівник на матрицю
};

/*
 * i.e. for i=1 the function returns the number of rows,
 * and for i=2 the function returns the number of columns
 * else the function returns 0
 */
int size(Matrix& a, const int i)
{
    return a.size(i);
}


// addition of Matrix with double
Matrix operator+ (const Matrix& a, const double b)
{
    Matrix res = a;
    res.add(b);
    return res;
}
// addition of double with Matrix
Matrix operator+ (const double b, const Matrix& a)
{
    Matrix res = a;
    res.add(b);
    return res;
}

// subtraction of Matrix with double
Matrix operator- (const Matrix& a, const double b)
{
    Matrix res = a;
    res.subtract(b);
    return res;
}
// subtraction of double with Matrix
Matrix operator- (const double b, const Matrix& a)
{
    Matrix res = -a;
    res.add(b);
    return res;
}

// multiplication of Matrix with double
Matrix operator* (const Matrix& a, const double b)
{
    Matrix res = a;
    res.multiply(b);
    return res;
}
// multiplication of double with Matrix
Matrix operator* (const double b, const Matrix& a)
{
    Matrix res = a;
    res.multiply(b);
    return res;
}


/*
 * повертає матрицю розміром cols x rows з значеннями 1
 */
Matrix ones(const int rows, const int cols)
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
 * повертає матрицю розміром cols x rows з значеннями 0
 */
Matrix zeros(const int rows, const int cols)
{
    return Matrix(rows, cols);
}


/**
 * returns a diagonal matrix with size n x n with ones at the diagonal
 * @param   v a vector
 * @return  a diagonal matrix with ones on the diagonal
 */
Matrix diag(const int n)
{
    Matrix res = Matrix(n, n);
    for (int i = 1; i <= n; i++)
    {
        res(i, i) = 1;
    }
    return res;
}
/**
 * returns a diagonal matrix
 * @param   v a vector
 * @return  a diagonal matrix with the given vector v on the diagonal
 */
Matrix diag(Matrix& v)
{
    Matrix res;
    if (v.get_cols() == 1)
    {
        // the given matrix is a vector n x 1
        int rows = v.get_rows();
        res = Matrix(rows, rows);

        // copy the values of the vector to the matrix
        for (int r=1; r <= rows; r++)
        {
            res(r, r) = v(r, 1);
        }
    }
    else if (v.get_rows() == 1)
    {
        // the given matrix is a vector 1 x n
        int cols = v.get_cols();
        res = Matrix(cols, cols);

        // copy the values of the vector to the matrix
        for (int c=1; c <= cols; c++)
        {
            res(c, c) = v(1, c);
        }
    }
    else
    {
        throw Exception("Parameter for diag must be a vector");
    }
    return res;
}

/*
 * повертає детермінант матриці А
 */
double det(Matrix& a)
{
    double d = 0;       // значення детермінанта
    int rows = a.get_rows();
    int cols = a.get_cols();

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
            // для матриці  3 x 3 або більшої розмірності
            for (int c = 1; c <= cols; c++)
            {
                Matrix M = a.minor(1, c);
                d += (c%2 + c%2 - 1) * a(1, c) * det(M);  
            }
        }
    }
    else
    {
        throw Exception("Матриця повинна бути квадратною");
    }
    return d;
}

/*
 * повертає обернену матрицю до матриці А
 */
Matrix inv(Matrix& a)
{
    Matrix res;
    double d = 0;       // значення детермінанта
    int rows = a.get_rows();
    int cols = a.get_cols();

    d = det(a);
    if (rows == cols && d != 0)
    {
        // для квадратної матриці
        if (rows == 1)
        {
            // для матриці 1 x 1 
            res = Matrix(rows, cols);
            res(1, 1) = 1 / a(1, 1);
        }
        else if (rows == 2)
        {
            // для матриці 2 x 2 
            res = Matrix(rows, cols);
            res(1, 1) = a(2, 2);
            res(1, 2) = -a(1, 2);
            res(2, 1) = -a(2, 1);
            res(2, 2) = a(1, 1);
            res = (1/d) * res;
        }
    else
    {
        if (rows == cols)
        {
            throw Exception("Матриця повинна бути квадратною");
        }
        else
        {
            throw Exception("Детермінант матриці дорівнює нулю");
        }
    }
    return res;
}


int main(int argc, char *argv[])
{
    try
    {
        // створює порожню матрицю 3x3 
        int cols = 3;
        int rows = 3;
        Matrix A = Matrix(cols, rows);

        // заповнює елементи матриці
        int count = 0;
        for (int r = 1; r <= rows; r++)
        {
            for (int c = 1; c <= cols; c++)
            {
                count ++;
                A(r, c) = count;
            }
        }

        // adjust a value in the matrix  (indexes are one-based)
        A(2,1) = 1.23;

        // считує значення матриці
        double value = A(2,2);
        printf("Значення = %f \n", value);
        printf("\n");

        // виводить цілу матрицю
        printf("A = \n");
        A.print();
        printf("\n");

        Matrix B = ones(rows, cols) + diag(rows);
        printf("B = \n");
        B.print();
        printf("\n");

        Matrix B2 = Matrix(rows, 1);        // вектор
        count = 1;
        for (int r = 1; r <= rows; r++)
        {
            count ++;
            B2(r, 1) = count * 2;
        }
        printf("B2 = \n");
        B2.print();
        printf("\n");

        Matrix C;
        C = A + B;
        printf("A + B = \n");
        C.print();
        printf("\n");

        C = A - B;
        printf("A - B = \n");
        C.print();
        printf("\n");

        C = A * B2;
        printf("A * B2 = \n");
        C.print();
        printf("\n");

        //створює діагональну матрицю
        Matrix E = diag(B2);
        printf("E = \n");
        E.print();
        printf("\n");

        // обчислює детермінант
        Matrix D = Matrix(2, 2);
        D(1,1) = 2;
        D(1,2) = 4;
        D(2,1) = 1;
        D(2,2) = -2;
        printf("D = \n");
        D.print();
        printf("det(D) = %f\n\n", det(D));

        printf("A = \n");
        A.print();
        printf("\n");
        printf("det(A) = %f\n\n", det(A));

        Matrix F;
        F = 3 - A ;
        printf("3 - A = \n");
        F.print();
        printf("\n");

        // тестування оберненої матриці
        Matrix G = Matrix(2, 2);
        G(1, 1) = 1;
        G(1, 2) = 2;
        G(2, 1) = 3;
        G(2, 2) = 4;
        printf("G = \n");
        G.print();
        printf("\n");
        Matrix G_inv = inv(G);
        printf("inv(G) = \n");
        G_inv.print();
        printf("\n");

        Matrix A_inv = inv(A);
        printf("inv(A) = \n");
        A_inv.print();
        printf("\n");
    }
    catch (Exception err)
    {
        printf("Error: %s\n", err.msg);
    }
    catch (...)
    {
        printf("An error occured...\n");
    }

    printf("\n");
    system("PAUSE");
    return EXIT_SUCCESS;
}
