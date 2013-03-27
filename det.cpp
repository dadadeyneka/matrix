#include <cstdlib>
#include <cstdio>
#include <math.h>

using namespace std;

class Matrix
{public: 
Matrix()
           p=NULL;
           rows=0;
           cols=0;
           }
Matrix(const int row_zm,const int col_zm)
{ p = NULL;

        if (row_zm> 0 && column_zm > 0)
        {
            rows = row_zm;
            cols = column_zm;

            p = new double*[rows];
            for (int r = 0; r < rows; r++)
            {
                p[r] = new double[rows];

                // обнуляємо значення матриці
                for (int c = 0; c < cols; c++)
                {
                    p[r][c] = 0;
// оператор присвоювання
    Matrix(const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            // копіюємо значення матриці
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
    }
           
}   

      

