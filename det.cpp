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
        // ñòâîðþºìî ìàòðèöþ áåç çì³ñòó
        p = NULL;
        rows = 0;
        cols = 0;
    }
    Matrix(const int row_count, const int column_count)
    {
        // ñòâîðþºìî ìàòðèöþ ³ç çàäàíèì ÷èñëîì ñòîâïö³â ³ ðÿäê³â
        p = NULL;

        if (row_count > 0 && column_count > 0)
        {
            rows = row_count;
            cols = column_count;

            p = new double*[rows];
            for (int r = 0; r < rows; r++)
            {
                p[r] = new double[cols];

                // îáíóëÿºìî çíà÷åííÿ ìàòðèö³
                for (int c = 0; c < cols; c++)
                {
                    p[r][c] = 0;
                }
            }
        }
    }
    // îïåðàòîð ïðèñâîþâàííÿ
    Matrix(const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            // êîï³þºìî çíà÷åííÿ ç ìàòðèö³ À
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
    }

    // îïåðàòîð äëÿ ³íäåêñ³â çíà÷åíü ìàòðèö³
	double& operator()(const int r, const int c)
	{
      	if (p != NULL && r > 0 && r <= rows && c > 0 && c <= cols)
      	{
          	return p[r-1][c-1];
        }
      	else
      	{
             printf("²íäåêñ çíàõîäèòüñÿ çà ä³àïàçîíîì ìàòðèö³\n");
        }
    }

    // îïåðàòîð ïðèñâîþâàííÿ
    Matrix& operator= (const Matrix& a)
    {
        rows = a.rows;
        cols = a.cols;
        p = new double*[a.rows];
        for (int r = 0; r < a.rows; r++)
        {
            p[r] = new double[a.cols];

            // êîï³þº çíà÷åííÿ ç ìàòðèö³ À
            for (int c = 0; c < a.cols; c++)
            {
                p[r][c] = a.p[r][c];
            }
        }
        return *this;
    }

    // îïåðàòîð ñóìè
    friend Matrix operator+(const Matrix& a, const Matrix& b)
    {
        // ïåðåâ³ðêà â³äïîâ³äíîñò³ ðîçì³ð³â ìàòðèöü
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
            // ïîìèëêà
            printf("Ðîçì³ðè ìàòðèöü íå ñï³âïàäàþòü\n");
        }

        // ïîâåðòàº ïîðîæíþ ìàòðèöþ
        return Matrix();
    }

    // îïåðàòîð â³äí³ìàííÿ
    friend Matrix operator- (const Matrix& a, const Matrix& b)
    {
        // ïåðåâ³ðêà â³äïîâ³äíîñò³ ìàòðèöü
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
            // ïîìèëêà
           printf("Ðîçì³ðè ìàòðèöü íå ñï³âïàäàþòü\n");
        }

        // ïîâåðòàº ïîðîæíþ ìàòðèöþ
        return Matrix();
    }
    // îïåðàòîð ïðîòèëåæíîãî êîæíîãî çíà÷åííÿ ìàòðèö³
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

    // îïåðàòîð ìíîæåííÿ
    friend Matrix operator* (const Matrix& a, const Matrix& b)
    {
        // ïåðåâ³ðêà â³äïîâ³äíîñò³ ìàòðèöü
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
            // ïîìèëêà
            printf("Ðîçì³ðè ìàòðèöü íå ñï³âïàäàþòü\n");
        }

        //  ïîâåðòàº ïîðîæíþ ìàòðèöþ
        return Matrix();
    }

    //ïîâåðòàº ì³íîð ìàòðèö³, äå âèáðàí³ çíà÷åííÿ áóäóòü âèäàëåí³
    Matrix Minor(const int row, const int col)
    {
        Matrix res;
      	if (row > 0 && row <= rows && col > 0 && col <= cols)
      	{
            res = Matrix(rows - 1, cols - 1);

            // ñêîï³þâàòè çíà÷åííÿ ìàòðèö³ äî ì³íîðó, êð³ì âèáðàíèõ
            for (int r = 1; r <= (rows - (row >= rows)); r++)
            {
                for (int c = 1; c <= (cols - (col >= cols)); c++)
                {
                    //printf("r=%i, c=%i, value=%f, rr=%i, cc=%i \n", r, c, p[r-1][c-1], r - (r > row), c - (c > col));
                    res(r - (r > row), c - (c > col)) = p[r-1][c-1];
                }
            }
        }
        else
        {
           printf("²íäåêñ çíàõîäèòüñÿ çà ä³àïàçîíîì ìàòðèö³\n");
        }

        return res;
    }

    // ïîâåðòàº i-èé ðîçì³ð ìàòðèö³
    //ÿêùî i=1 ôóíêö³ÿ ïîâåðòàº ê³ëüê³ñòü ðÿäê³â ìàòðèö³,
    // ÿêùî i=1 ôóíêö³ÿ ïîâåðòàº ê³ëüê³ñòü ñòîâïö³â ìàòðèö³,
    //â ³íøîìó âèïàäêó ôóíêö³ÿ ïîâåðòàº 0
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

    // ïîâåðòàº ê³ëüê³ñòü ðÿäê³â ìàòðèö³
    int GetRows()
    {
        return rows;
    }

    // ïîâåðòàº ê³ëüê³ñòü ñòîâïö³â ìàòðèö³
    int GetCols()
    {
        return cols;
    }

// òðàíñïîðòóâàííÿ ìàòðèö³
void Transp(Matrix& a)// òðàíñïîíóâàííÿ ìàòðèö³
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

    // âèâîäèòü âì³ñò ìàòðèö³
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
            // ïîðîæíÿ  ìàòðèöÿ
            printf("[ ]\n");
        }
    }

public:
    // äåñòðóêòîð
    ~Matrix()
    {
        // î÷èùàº âèä³ëåíó ïàìÿòü
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
    double** p;         // âêàç³âíèê íà ìàòðèöþ ç çíà÷åííÿìè double
};

/*
 * 
 */
int Size(Matrix& a, const int i)
{
    return a.Size(i);
}

/*
 * ïîâåðòàº ìàòðèöþ ðîçì³ðîì cols x rows ç çíà÷åííÿìè îäèíèöÿ
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
 *  ïîâåðòàº ìàòðèöþ ðîçì³ðîì cols x rows ç çíà÷åííÿìè 0
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
        // îòðèìàíà ìàòðèöÿ º âåêòîðîì n x 1
        int rows = v.GetRows();
        res = Matrix(rows, rows);

        // êîï³þºìî çíà÷åííÿ âåêòîðà äî ìàòðèö³
        for (int r=1; r <= rows; r++)
        {
            res(r, r) = v(r, 1);
        }
    }
    else if (v.GetRows() == 1)
    {
        // îòðèìàíà ìàòðèöÿ º âåêòîðîì n x 1
        int cols = v.GetCols();
        res = Matrix(cols, cols);

        // êîï³þºìî çíà÷åííÿ âåêòîðà äî ìàòðèö³
        for (int c=1; c <= cols; c++)
        {
            res(c, c) = v(1, c);
        }
    }
    else
    {
        printf("Ïàðàìåòð äëÿ ä³àãîíàë³ ìàº áóòè âåêòîð\n");
    }
    return res;
}

/*
 * ïîâåðòàº äåòåðì³íàíò ìàòðèö³ À
 */
double Det(Matrix& a)
{
    double d = 0;       // çíà÷åííÿ äåòåðì³íàíòà
    int rows = a.GetRows();
    int cols = a.GetRows();

    if (rows == cols)
    {
        // äëÿ êâàäðàòíî¿ ìàòðèö³
        if (rows == 1)
        {
            //  äëÿ ìàòðèö³ 1 x 1
            d = a(1, 1);
        }
        else if (rows == 2)
        {
            // äëÿ ìàòðèö³ 2 x 2
            d = a(1, 1) * a(2, 2) - a(2, 1) * a(1, 2);
        }
        else
        {
            // äëÿ ìàòðèö³3 x 3 àáî á³ëüøå
            for (int c = 1; c <= cols; c++)
            {
                Matrix M = a.Minor(1, c);
                d += pow(-1, 1+c)  * a(1, c) * Det(M);
            }
        }
    }
    else
    {
        printf("Ìàòðèöÿ ïîâèííà áóòè êâàäðàòíîþ\n");
    }
    return d;
}


/*
 * ïîâåðòàº îáåðíåíó ìàòðèöþ
 */
Matrix inv(Matrix& a)
{
    Matrix res;
    double d = 0;       //???????? ????????????
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
        // ñòâîðþºìî ìàòðèöþ 3x3 (ç çíà÷åííÿìè 0)
        int cols = 3;
        int rows = 3;
        Matrix A = Matrix(cols, rows);

        // íàäàºìî äåÿêîãî çíà÷åííÿ ìàòðèö³ À
        int count = 0;
        for (int r = 1; r <= rows; r++)
        {
            for (int c = 1; c <= cols; c++)
            {
                count ++;
                A(r, c) = count;
            }
        }

        // ïðèñâîºííÿ çíà÷åííÿ åëåìåíòó ìàòðèö³ çà ³íäåêñîì
        A(2,1) = 3.45;

        // ç÷èòóº çíà÷åííÿ åëåìåíòà ìàòðèö³ çà ³íäåêñîì
        double value = A(2,2);
        printf("Znachennya = %f \n", value);
        printf("\n");

        // âèâîäèòü ìàòðèöþ
        printf("A = \n");
        A.Print();
        printf("\n");

        Matrix B = Ones(rows, cols) + Diag(rows);
        printf("B = \n");
        B.Print();
        printf("\n");

        Matrix B2 = Matrix(rows, 1);        // âåêòîð
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

        // ñòâîðþº ä³àãîíàëüíó ìàòðèöþ
        Matrix E = Diag(B2);
        printf("E = \n");
        E.Print();
        printf("\n");

        // îá÷èñëþº äåòåðì³íàíò
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
