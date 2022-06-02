#include <iostream>
#include <cmath>
using namespace std;

int Q = 0;

class Vector
{
private:
    double *vctr;
    int len;

    void create()
    {
        vctr = new double[len];
    }

public:
    Vector() : len(2) { create(); }
    Vector(int n) : len(n) { create(); }
    Vector(const Vector &V) : len(V.len)
    {
        create();
        for (int i = 0; i < len; i++)
            vctr[i] = V.vctr[i];
    }
    ~Vector() { delete[] vctr; }
    double &operator[](int i) { return vctr[i]; }
    int getLen() { return len; }
    friend istream &operator>>(istream &istr, Vector &V); //перегрузка оператора ввода
    friend ostream &operator<<(ostream &ostr, Vector &V); //перегрузка оператора вывода
};

istream &operator>>(istream &istr, Vector &V) // перегрузка оператора ввода матрицы
{
    for (int i = 0; i < V.getLen(); i++)
        istr >> V[i];
    return istr;
}

ostream &operator<<(ostream &ostr, Vector &V) //перегрузка оператора вывода матрицы
{
    ostr << "\nVector: ";
    for (int i = 0; i < V.getLen(); i++)
        ostr << V[i] << ' ';
    return ostr;
}

class Matrix
{
    Vector **mtrx;
    int m;
    int n;

    void create()
    {
        mtrx = new Vector *[m];
        for (int i = 0; i < m; i++)
            mtrx[i] = new Vector(n);
    }

    void swap(Matrix &M)
    {
        {
            int tmp = m;
            m = M.m;
            M.m = tmp;
            tmp = n;
            n = M.n;
            M.n = tmp;
        }
        Vector **tmp = mtrx;
        mtrx = M.mtrx;
        M.mtrx = tmp;
    }

public:
    Matrix() : m(2), n(2) { create(); }      //конструктор по умолчанию
    Matrix(int i) : m(i), n(i) { create(); } //конструктор с параметрами, квадратная матрица
    Matrix(int i, int j) : m(i), n(j) { create(); }
    Matrix(const Matrix &M) : m(M.m), n(M.n) //копирующий конструктор - создает копию объекта m
    {
        create();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                (*mtrx[i])[j] = (*M.mtrx[i])[j]; // значения элементов матрицы будут такими же, как у матрицы M
    }
    ~Matrix() //деструктор удаляет из памяти динамический массив, созданный конструктором
    {
        delete[] mtrx;
    }
    int getRow() { return m; } //метод получает значение числа строк
    int getCol() { return n; } //метод получает значение числа столбцов

    double &operator()(int m, int n) //перегрузка круглых скобок для матрицы.
    {                                // Если m - матрица, то m(i,j) будет
        return (*mtrx[m])[n];        //означать i,j-тый элемент матрицы
    }

    Matrix &operator=(const Matrix &m) //перугрузка = для матрц
    {
        Matrix tmp(m);
        swap(tmp);
        return *this;
    }

    friend double determinate(Matrix &m1); //метод ищет определитель матрицы
    friend Matrix getInverse(Matrix &M);   //метод ищет обратную матрицу
    friend void swapRows(Matrix &M, int firstRow, int secondRow);
    friend void remakeToIden(Matrix &M);

    friend istream &operator>>(istream &istr, Matrix &A); //перегрузка оператора ввода
    friend ostream &operator<<(ostream &ostr, Matrix &A); //перегрузка оператора вывода
    friend Matrix operator+(Matrix &m1, Matrix &m2);      //перегрузка оператора плюс (бинарный)
    friend Matrix operator-(Matrix &m1, Matrix &m2);      //перегрузка оператора минус (бинарный)
    friend Matrix operator*(Matrix &m1, Matrix &m2);
};

istream &operator>>(istream &istr, Matrix &A) // перегрузка оператора ввода матрицы
{
    for (int i = 0; i < A.getRow(); i++)
        for (int j = 0; j < A.getCol(); j++)
            istr >> A(i, j);
    return istr;
}

ostream &operator<<(ostream &ostr, Matrix &A) //перегрузка оператора вывода матрицы
{
    for (int i = 0; i < A.getRow(); i++)
    {
        for (int j = 0; j < A.getCol(); j++)
            ostr << A(i, j) << "\t";
        ostr << "\n";
    }
    return ostr;
}

Matrix operator+(Matrix &m1, Matrix &m2) //перегрузка оператора плюс (бинарный)
{
    Matrix temp(m1.getRow(), m1.getCol());
    if (m1.getCol() == m2.getCol() && m1.getRow() == m2.getRow())
    {
        for (int i = 0; i < m1.getRow(); i++)
            for (int j = 0; j < m1.getCol(); j++)
                temp(i, j) = m1(i, j) + m2(i, j);
        Q = 1;
        return temp;
    }
    else
    {
        return temp;
    }
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix temp1(m1.getRow(), m1.getCol());
    if (m1.getCol() == m2.getCol() && m1.getRow() == m2.getRow())
    {
        for (int i = 0; i < m1.getRow(); i++)
            for (int j = 0; j < m1.getCol(); j++)
                temp1(i, j) = m1(i, j) - m2(i, j);
        Q = 2; // инициализация глабальной переменной 1, для отслеживания в main
        return temp1;
    }
    else
    {
        return temp1;
    }
}

Matrix operator*(Matrix &m1, Matrix &m2)
{
    Matrix tmp(m1.getRow(), m2.getCol());
    if (m1.getCol() == m2.getRow())
    {
        for (int i = 0; i < m1.getRow(); i++)
        {
            for (int j = 0; j < m2.getCol(); j++)
            {
                for (int k = 0; k < m1.getCol(); k++)
                {
                    tmp(i, j) += m1(i, k) * m2(k, j);
                }
            }
        }
        Q = 3;
        return tmp;
    }
    else
    {
        return tmp;
    }
}
double determinate(Matrix &m1)
{ //Рекурсивная функция вычисления определителя матрицы
    if (m1.getRow() == m1.getCol())
    {
        if (m1.getCol() == 1)
            return m1(0, 0);
        else if (m1.getCol() == 2)
            return m1(0, 0) * m1(1, 1) - m1(0, 1) * m1(1, 0);
        else
        {
            float d = 0;
            for (int k = 0; k < m1.getCol(); k++)//цикл по строке
            {
                Matrix m2(m1.getCol() - 1); //создаём квадратную матрицу меньше на 1 размера начальной матрицы
                for (int i = 1; i < m1.getCol(); i++)
                {
                    int t = 0;
                    for (int j = 0; j < m1.getCol(); j++)
                    {
                        if (j == k)
                            continue;
                        m2(i - 1, t) = m1(i, j);
                        t++;
                    }
                }
                d += pow(-1, k + 2) * m1(0, k) * determinate(m2);//определитель по первой строке
            }
            Q = 4;
            return d; //Возвращаем определитель матрицы
        }
    }
    else
    {
        return -1;
    }
}

Matrix getInverse(Matrix &M)
{
    Matrix Tmp(M), Res(M.getRow(), M.getCol());
    remakeToIden(Res);
    if (Tmp.getCol() != Tmp.getRow())
    {
        Q = 51;
        return Tmp;
    }
    if (determinate(Tmp) == 0)
    {
        Q = 52;
        return Tmp;
    }
    for (int begin = 0; begin < Tmp.getCol(); begin++)
    {
        int i;
        int j = begin;
        bool f = true;
        while (f)
        {
            for (i = begin; i < Tmp.getRow(); i++)
            {
                if (Tmp(i, j) != 0)
                {
                    f = false;
                    break;
                }
            }
            if (f)
            {
                j++;
            }
        }
        if (!f)
        {
            if (Tmp(begin, j) == 0)
            {
                swapRows(Tmp, begin, i);
                swapRows(Res, begin, i);
            }
        }

        double upEl = Tmp(begin, j);
        for (j = 0; j < Tmp.getCol(); j++)
        {
            Tmp(begin, j) /= upEl;
            Res(begin, j) /= upEl;
        }

        for (i = begin + 1; i < Tmp.getRow(); i++)
        {
            double firstEl = Tmp(i, begin);
            for (j = 0; j < Tmp.getCol(); j++)
            {
                Tmp(i, j) -= Tmp(begin, j) * firstEl;
                Res(i, j) -= Res(begin, j) * firstEl;
            }
        }
    }
    for (int i = Tmp.getRow() - 2; i >= 0; i--)
    {
        for (int k = i + 1; k < Tmp.getRow(); k++)
        {
            double v = Tmp(i, k);
            for (int j = 0; j < Tmp.getCol(); j++)
            {
                Tmp(i, j) -= Tmp(k, j) * v;
                Res(i, j) -= Res(k, j) * v;
            }
        }
    }
    Q = 5;
    return Res;
}

void swapRows(Matrix &M, int firstRow, int secondRow)
{
    for (int j = 0; j < M.getCol(); j++)
    {
        int tmp = M(firstRow, j);
        M(firstRow, j) = M(secondRow, j);
        M(secondRow, j) = tmp;
    }
}

void remakeToIden(Matrix &M)
{
    for (int i = 0; i < M.getRow(); i++)
    {
        for (int j = 0; j < M.getCol(); j++)
        {
            if (i == j)
            {
                M(i, j) = 1;
            }
            else
            {
                M(i, j) = 0;
            }
        }
    }
}

Matrix input()
{
    int n2, m2;
    cout << "enter count of rows\n";
    cin >> n2;
    cout << "enter count of colums\n";
    cin >> m2;
    Matrix K(n2, m2);
    cout << "enter matrix with " << n2 << " rows and " << m2 << " colums\n";
    cin >> K;
    return K;
}

int main()
{
    int n1;
    int n2, m2;
    Matrix A, B, C, T;
    cout << "What do you want to do?\n";

    while (n1 != 6)
    {
        Q = 0;
        cout << "Press\n 1-sum matrices\n 2-subtract matrices\n 3-multiply matrices\n 4-find matrix determinant\n 5-find inverse matrix\n 6-finish the process\n";
        cin >> n1;
        switch (n1)
        {
        case 1:
            cout << "Enter the desired values for the first matrix A\n";
            A = input();
            cout << "Enter the desired values for the second matrix B\n";
            B = input();
            C = A + B;
            if (Q == 1)
            {
                cout << "Result A+B\n";
                cout << C;
                break;
            }
            else
            {
                cout << "Can`t find sum\n";
                break;
            }
            break;
        case 2:
            cout << "Enter the desired values for the first matrix A\n";
            A = input();
            cout << "Enter the desired values for the second matrix B\n";
            B = input();
            C = A - B;
            if (Q == 2)
            {
                cout << "Result A-B\n";
                cout << C;
                break;
            }
            else
            {
                cout << "Can`t find difference\n";
                break;
            }

        case 3:
            cout << "Enter the desired values for the first matrix A\n";
            A = input();
            cout << "Enter the desired values for the second matrix B\n";
            B = input();
            C = A * B;
            if (Q == 3)
            {
                cout << "Result A-B\n";
                cout << C;
                break;
            }
            else
            {
                cout << "Сannot be multiplied\n";
                break;
            }
        case 4:
            double Det;
            cout << "Enter the desired values for the first matrix A\n";
            A = input();
            Det = determinate(A);
            if (Q == 4)
            {
                cout << "Determitate is " << Det << endl;
                break;
            }
            else
            {
                cout << "Сan`t find determinate\n";
                break;
            }
        case 5:
            cout << "Enter the desired values for the first matrix A\n";
            A = input();
            B = getInverse(A);
            if (Q == 51)
            {
                cout << "Matrix not square!\n";
                break;
            }
            if (Q == 52)
            {
                cout << "inverse matrix not exist\n";
                break;
            }
            if (Q == 5)
            {
                cout << "Result A^-1\n";
                cout << B;
                break;
            }
        case 6:
            cout << "You finish this program\n";
            break;
        default:
            cout << "Enter right number\n";
            break;
        }
    }
    return 0;
}
