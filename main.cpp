#include <iostream>
using namespace std;

class Matrix
{
    int **Matr;
    int m;
    int n;

    void Create()
    {
        Matr = new int *[m]; //выделение памяти под матрицу
        for (int i = 0; i < m; i++)
            Matr[i] = new int[n];
    }

    void swap(Matrix& mtx)
    {
        {
            int tmp = m; m = mtx.m; mtx.m = m;
            tmp = n; n = mtx.n; mtx.n = n;
        }
        int ** tmp = Matr; Matr = mtx.Matr; mtx.Matr = tmp;
    }

public:
    Matrix() : m(2), n(2) { Create(); }      //конструктор по умолчанию
    Matrix(int i) : m(i), n(i) { Create(); } //конструктор с параметрами, квадратная матрица
    Matrix(int i, int j) : m(i), n(j) { Create(); }
    Matrix(const Matrix& mtx):m(mtx.m),n(mtx.n) //копирующий конструктор - создает копию объекта m
    {
        Create();
        for (int i=0; i<m; i++)
        {
            for (int j=0; j<n; j++)
                Matr[i][j] = mtx.Matr[i][j];
        } // значения элементов матрицы будут такими же, как у матрицы mtx
    }
    ~Matrix() //деструктор удаляет из памяти динамический массив, созданный конструктором
    {
        for (int k = 0; k < m; k++)
            delete[] Matr[k];
        delete[] Matr;
    }
    int GetRow() { return m; } //метод получает значение числа строк
    int GetCol() { return n; } //метод получает значение числа столбцов
    int& operator()(int m, int n)//перегрузка круглых скобок для матрицы.
    {                             // Если m - матрица, то m(i,j) будет
        return (Matr[m][n]);  //означать i,j-тый элемент матрицы
    }
    
    Matrix& operator=(const Matrix& m)
    {
        Matrix tmp(m);
        swap(tmp);
        return *this;
    }

    friend istream &operator>>(istream &istr, Matrix &A); //перегрузка оператора ввода
    friend ostream &operator<<(ostream &ostr, Matrix &A); //перегрузка оператора вывода
    friend Matrix operator+(Matrix &m1, Matrix &m2);      //перегрузка оператора плюс (бинарный)
    friend Matrix operator-(Matrix &m1, Matrix &m2);     //перегрузка оператора минус (бинарный)
    friend Matrix operator*(Matrix &m1, Matrix &m2);


};

istream &operator>>(istream &istr, Matrix &A) // перегрузка оператора ввода матрицы
{
    for (int i = 0; i < A.GetRow(); i++)
        for (int j = 0; j < A.GetCol(); j++)
            istr >> A(i, j);
    return (istr);
}

ostream &operator<<(ostream &ostr, Matrix &A) //перегрузка оператора вывода матрицы
{
    for (int i=0; i<A.GetRow(); i++)
    {
        for (int j=0; j<A.GetCol(); j++)
            ostr<<A(i,j)<<"\t";
        ostr<<"\n";
    }
    return(ostr);
}

Matrix operator+(Matrix &m1, Matrix &m2) //перегрузка оператора плюс (бинарный)
{
    Matrix temp(m1.GetRow(),m1.GetCol());
    for (int i = 0; i<m1.GetRow(); i++)
        for (int j = 0; j<m1.GetCol(); j++)
            temp(i,j)=m1(i,j)+m2(i,j);
    return(temp);
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix temp1(m1.GetRow(),m1.GetCol());
    for (int i = 0; i<m1.GetRow(); i++)
        for (int j = 0; j<m1.GetCol(); j++)
            temp1(i,j)=m1(i,j)-m2(i,j);
    return(temp1);
}

Matrix operator*(Matrix &m1, Matrix &m2)
{
    Matrix mult(m1.GetRow(), m2.GetCol());
    if((m1.GetCol()==m2.GetRow()))
    {
        for(int i=0; i < m1.GetRow(); i++)
        {
            for(int j=0; j< m2.GetCol(); j++)
            {
                for(int k=0; k < m1.GetCol(); k++)
                {
                    *mult(i,j)+=m1(i,k)*m2(k,j);
                    cout << m1(i,k)*m2(k,j) << ' ';
                }
            }
        }
        return *mult;
    }
    else
    {
        cout<<"Cannot be multiplied\n";
        return 1;
    }

}

int main()
{
    Matrix M, N(2),L(2,3), S(2);
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
    cout<< N;
    
    //cout<<"jnj";
    
    S = M*N;
    //L=M*K;
    cout << S;
    //cout<<"dskmcwl";
    //cout<<L;
    return 0;
}
