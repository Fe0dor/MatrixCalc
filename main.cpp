#include <iostream>
#include <cmath>
#include <utility>
using namespace std;


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
                mtrx[i][j] = M.mtrx[i][j]; // значения элементов матрицы будут такими же, как у матрицы M
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

std::pair<int, Matrix> foo(int a, Matrix b) 
{
    return {a, b};
}
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
    if(m1.getCol()==m2.getCol() && m1.getRow()==m2.getRow())
    {
        for (int i = 0; i < m1.getRow(); i++)
            for (int j = 0; j < m1.getCol(); j++)
                temp(i, j) = m1(i, j) + m2(i, j);
        return temp;
    }
    else 
    {
        cout<<"Can`t find sum\n";
        return temp;
    }
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix temp1(m1.getRow(), m1.getCol());
    int flag;
    std::pair<int,Matrix> n(flag, temp1);
    if(m1.getCol()==m2.getCol() && m1.getRow()==m2.getRow())
    {
        for (int i = 0; i < m1.getRow(); i++)
            for (int j = 0; j < m1.getCol(); j++)
                temp1(i, j) = m1(i, j) - m2(i, j);
        n.first=1;
        n.second=temp1;
        cout<<"struct"<<n.second<<endl;
        return n.first, n.second;
    }
    else 
    {
        cout<<"Can`t find difference\n";
        n.first=-1;
        n.second=temp1;
        cout<<"struct"<<n.first<<endl;
        return n.first, n.second;
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
        return tmp;
    }
    else
    {
        cout << "Cannot be multiplied\n";
        return 1;
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
            for (int k = 0; k < m1.getCol(); k++)
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
                d += pow(-1, k + 2) * m1(0, k) * determinate(m2);
            }
            return d; //Возвращаем определитель матрицы
        }
    }
    else
    {
        cout << "Can`t count determinate\n";
        return 0, 2331;
    }
}

Matrix getInverse(Matrix &M)
{
    Matrix Tmp(M), Res(M.getRow(), M.getCol());
    remakeToIden(Res);
    if (Tmp.getCol() != Tmp.getRow())
    {
        cout << "Matrix not square!";
        return Tmp;
    }
    if (determinate(Tmp) == 0)
    {
        cout << "inverse matrix not exist";
        return Tmp;
    }
    for (int begin = 0; begin < Tmp.getCol() - 1; begin++)
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
                cout << "123";
            }
        }
        // cout << i << " " << j << " " << begin << "|\n";
        double upEl = Tmp(begin, j);
        double IupEl = Res(begin, j);
        // cout << "!" << j << " " << upEl << "!";
        for (j = begin; j < Tmp.getCol(); j++)
        {
            Tmp(begin, j) /= upEl;
            Tmp(begin, j) /= IupEl;
        }
        // cout << "!" << j << "!";
        for (i = begin + 1; i < Tmp.getRow(); i++)
        {
            double firstEl = Tmp(i, begin);
            double IfirstEl = Res(i, begin);
            for (j = begin; j < Tmp.getCol(); j++)
            {
                Tmp(i, j) -= Tmp(begin, j) * firstEl;
                Res(i, j) -= Res(begin, j) * IfirstEl;
            }
        }
        // cout << "!!!" << begin;
    }
    cout << Res;
    return Tmp;
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
    for (int i = 0; i < M.getRow(); i++) {
        for (int j = 0; j < M.getCol(); j++) {
            if (i == j) {
                M(i, j) = 1;
            } else {
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
    Matrix A,B,C; 
    cout<<"What do you want to do?\n";
    cout<<"Press\n 1-sum matrices\n 2-subtract matrices\n 3-multiply matrices\n 4-find matrix determinant\n 5-find inverse matrix\n";
    cin>>n1;
    switch (n1)
    {
    case 1:
       
        cout<<"Enter the desired values for the first matrix A\n";
        A=input();
        cout<<"Enter the desired values for the second matrix B\n";
        B=input();
        C=A+B;
        cout<<"Result A-B";
        cout<<C;
        break;
    case 2:
        cout<<"Enter the desired values for the first matrix A\n";
        A=input();
        cout<<"Enter the desired values for the second matrix B\n";
        B=input();
        C=A-B;
        
        cout<<"Result A-B\n";
        cout<<C;
        break;
    case 3:
        cout<<"Enter the desired values for the first matrix A\n";
        A=input();
        cout<<"Enter the desired values for the second matrix B\n";
        B=input();
        C=A*B;
        cout<<"Result A*B";
        cout<<C;
        break;
    case 4:
        double Det; 
        cout<<"Enter the desired values for the first matrix A\n";
        A=input();
        Det = determinate(A);
        cout<<"Determitate is "<<Det<<endl;
    case 5:
        cout<<"Enter the desired values for the first matrix A\n";
        A=input();
        B=getInverse(A);
        cout<<"Result A^-1";
        cout<<B;
        break;

    default:
        cout<<"Enter right number\n";
        break;
    }
    


    
    /*
    cout << "enter count of rows1\n";
    cin >> n1;
    cout << "enter count of colums1\n";
    cin >> m1;
    Matrix K(n1, m1);
    cout << "enter matrix with " << n1 << " rows and " << m1 << " colums\n";
    cin >> K;
    cout << K;
   
    float w;
   

    w = determinate(K);
    cout << "Determinate = " << w << endl;
    K = getInverse(K);
    cout << K;
    */
    
    return 0;
}
