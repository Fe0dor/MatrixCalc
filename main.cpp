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

public:
    Matrix() : m(2), n(2) { Create(); }      //конструктор по умолчанию
    Matrix(int i) : m(i), n(i) { Create(); } //конструктор с параметрами, квадратная матрица
    Matrix(int i, int j) : m(i), n(j) { Create(); }
    ~Matrix() //деструктор удаляет из памяти динамический массив, созданный конструктором
    {
        for (int k = 0; k < m; k++)
            delete[] Matr[k];
        delete[] Matr;
    }
    int GetRow() { return m; } //метод получает значение числа строк
    int GetCol() { return n; } //метод получает значение числа столбцов
    int &Element(int i, int j) //возврат элемента i,j матрицы
    {
        if (i < m && j < n)
            return Matr[i][j];
        else
            cout << "Error: 1";
    }

    friend istream &operator>>(istream &istr, Matrix &A); //перегрузка оператора ввода
    friend ostream &operator<<(ostream &ostr, Matrix &A); //перегрузка оператора вывода
    friend Matrix operator+(Matrix &m1, Matrix &m2);      //перегрузка оператора плюс (бинарный)
    friend Matrix operator-(Matrix &m1, Matrix &m2);      //перегрузка оператора минус (бинарный)
    friend Matrix operator*(Matrix &m1, Matrix &m2);
};

istream &operator>>(istream &istr, Matrix &A) // перегрузка оператора ввода матрицы
{
    for (int i = 0; i < A.GetRow(); i++)
        for (int j = 0; j < A.GetCol(); j++)
            istr >> A.Element(i, j);
    return (istr);
}

ostream &operator<<(ostream &ostr, Matrix &A) //перегрузка оператора вывода матрицы
{
    for (int i = 0; i < A.GetRow(); i++)
    {
        for (int j = 0; j < A.GetCol(); j++)
            ostr << A.Element(i, j) << "\t";
        ostr << "\n";
    }
    return (ostr);
}

Matrix operator+(Matrix &m1, Matrix &m2) //перегрузка оператора плюс (бинарный)
{
    Matrix sum(m1.GetRow(), m1.GetCol());
    if(m1.GetRow()==m2.GetRow() && m1.GetCol() == m2.GetCol())
    {
    for (int i = 0; i < m1.GetRow(); i++)
        for (int j = 0; j < m1.GetCol(); j++)
            sum.Element(i, j) = m1.Element(i, j) + m2.Element(i, j);
    return (sum);
    }
    else 
    {
        cout<<"Enter right mathix\n";
    }
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix diff(m1.GetRow(), m1.GetCol());
    if(m1.GetRow()==m2.GetRow() && m1.GetCol() == m2.GetCol())
    {
    for (int i = 0; i < m1.GetRow(); i++)
        for (int j = 0; j < m1.GetCol(); j++)
            diff.Element(i, j) = m1.Element(i, j) - m2.Element(i, j);
    return (diff);
    }
    else 
    {
        cout<<"Enter right mathix\n";
    }
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
                    mult.Element(i,j)+=m1.Element(i,k)*m2.Element(k,j);
                }
            }
        }
        return mult;
    }
    else
    {
        cout<<"Cannot be multiplied\n";
    }

}

int main()
{
    
    Matrix M, N(3), S(2), L(2,3);
    int n, m;
    cout<<"enter count of rows\n";
    cin>>n;
    cout<<"enter count of colums\n";
    cin>>m;
    Matrix K(n,m);
    cout<<"enter matrix with "<<n<<" rows and "<<m<<" colums\n";
    cin>> K;
    cout<<K;
    cout << "enter matrix M:\n";
    cin >> M;
    cout << M; 
    //cout << "enter matrix N:\n";
    //cin >> N;
    //cout<< N;
    //S = M + N;
    L=M*K;
    //cout << S;
    cout<<L;
    return 0;
}