#include <iostream>
using namespace std;

class Vector
{
private:
    int *vctr;
    int len;

    void create()
    {
        vctr = new int[len];
    }

public:
    Vector() : len(2) { create(); }
    Vector(int n) : len(n) { create(); }
    ~Vector() { delete[] vctr; }

    int &operator[](int i) { return vctr[i]; }
};

class Matrix
{
    Vector *mtrx;
    int m;
    int n;

    void create()
    {
        mtrx = new Vector[m];
        for (int i = 0; i < m; i++)
            mtrx[i] = *new Vector(n);
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
        Vector *tmp = mtrx;
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
                mtrx[i][j] = M.mtrx[i][j]; // значения элементов матрицы будут такими же, как у матрицы M
    }
    // ~Matrix() //деструктор удаляет из памяти динамический массив, созданный конструктором
    // {
    //     for (int k = 0; k < m; k++)
    //         delete *mtrx[k];
    //     delete[] mtrx;
    // }
    int getRow() { return m; }    //метод получает значение числа строк
    int getCol() { return n; }    //метод получает значение числа столбцов

    int &operator()(int m, int n) //перегрузка круглых скобок для матрицы.
    {                             // Если m - матрица, то m(i,j) будет
        return mtrx[m][n];        //означать i,j-тый элемент матрицы
    }

    Matrix &operator=(const Matrix &m)
    {
        Matrix tmp(m);
        swap(tmp);
        return *this;
    }
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
    return (istr);
}

ostream &operator<<(ostream &ostr, Matrix &A) //перегрузка оператора вывода матрицы
{
    for (int i = 0; i < A.getRow(); i++)
    {
        for (int j = 0; j < A.getCol(); j++)
            ostr << A(i, j) << "\t";
        ostr << "\n";
    }
    return (ostr);
}

Matrix operator+(Matrix &m1, Matrix &m2) //перегрузка оператора плюс (бинарный)
{
    Matrix temp(m1.getRow(), m1.getCol());
    for (int i = 0; i < m1.getRow(); i++)
        for (int j = 0; j < m1.getCol(); j++)
            temp(i, j) = m1(i, j) + m2(i, j);
    return (temp);
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix temp1(m1.getRow(), m1.getCol());
    for (int i = 0; i < m1.getRow(); i++)
        for (int j = 0; j < m1.getCol(); j++)
            temp1(i, j) = m1(i, j) - m2(i, j);
    return (temp1);
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
        return tmp;
    }
    else
    {
        cout << "Cannot be multiplied\n";
        return 1;
    }
}

int main()
{
    Matrix M, N, S;
    /*
    int n1, m1, n2, m2;
    cout<<"enter count of rows1\n";
    cin>>n1;
    cout<<"enter count of colums1\n";
    cin>>m1;
    Matrix K(n1,m1);
    cout<<"enter matrix with "<<n1<<" rows and "<<m1<<" colums\n";
    cin>> K;
    cout<<K;
     cout<<"enter count of rows2\n";
    cin>>n2;
    cout<<"enter count of colums2\n";
    cin>>m2;
    Matrix X(n2,m2);
    cout<<"enter matrix with "<<n2<<" rows and "<<m2<<" colums\n";
    cin>> X;
    cout<<X;
    Matrix S(n1,m2);
    */

    cout << "enter matrix M:\n";
    cin >> M;
    cout << M;
    cout << "enter matrix N:\n";
    cin >> N;
    cout << N;
    // cout<<"jnj";

    // L=M*K;
    S = M * N;
    cout << S;

    // cout<<"dskmcwl";
    // cout<<L;
    return 0;
}
