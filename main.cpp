#include <iostream>
using namespace std;

 class Matrix
{
        int **Matr;
        int m;
        int n;
 
        void Create()
        {
            Matr = new int*[m];//выделение памяти под матрицу
            for (int i=0; i<m; i++)
                Matr[i] = new int[n];
        }
 
    public:
        Matrix(): m(2), n(2) { Create(); }//конструктор по умолчанию
        Matrix(int i): m(i), n(i) { Create(); }//конструктор с параметрами, квадратная матрица
        Matrix(int i, int j): m(i), n(j) { Create(); }
        ~Matrix()//деструктор удаляет из памяти динамический массив, созданный конструктором
        {
            for (int k=0; k<m; k++)
                delete[] Matr[k];
            delete[] Matr;
        }
        int GetRow() {return m;} //метод получает значение числа строк
        int GetCol() {return n;} //метод получает значение числа столбцов
        int& Element(int i, int j)//возврат элемента i,j матрицы
        {
            if (i<m && j<n)
                return Matr[i][j];
            else
                cout << "Error: 1";
        }
 
        friend istream& operator>>(istream &istr, Matrix &A);//перегрузка оператора ввода
        friend ostream& operator<<(ostream &ostr, Matrix &A);//перегрузка оператора вывода
        friend Matrix operator+(Matrix &m1, Matrix &m2);//перегрузка оператора плюс (бинарный)
        friend Matrix operator-(Matrix &m1, Matrix &m2);//перегрузка оператора минус (бинарный)
};

istream& operator>>(istream& istr, Matrix &A) // перегрузка оператора ввода матрицы
{
    for (int i=0; i<A.GetRow(); i++)
        for (int j=0; j<A.GetCol(); j++)
            istr>>A.Element(i,j);
    return(istr);
}

ostream& operator<<(ostream& ostr, Matrix &A) //перегрузка оператора вывода матрицы
{
    for (int i=0; i<A.GetRow(); i++)
    {
        for (int j=0; j<A.GetCol(); j++)
            ostr<<A.Element(i,j)<<"\t";
        ostr<<"\n";
    }
    return(ostr);
}

Matrix operator+(Matrix &m1, Matrix &m2) //перегрузка оператора плюс (бинарный)
{
    Matrix sum(m1.GetRow(),m1.GetCol());
    for (int i = 0; i<m1.GetRow(); i++)
        for (int j = 0; j<m1.GetCol(); j++)
            sum.Element(i,j)=m1.Element(i,j)+m2.Element(i,j);
    return(sum);
}

Matrix operator-(Matrix &m1, Matrix &m2) //перегрузка оператора минус (бинарный)
{
    Matrix diff(m1.GetRow(),m1.GetCol());
    for (int i = 0; i<m1.GetRow(); i++)
        for (int j = 0; j<m1.GetCol(); j++)
            diff.Element(i,j)=m1.Element(i,j)-m2.Element(i,j);
    return(diff);
}
 
int main()
{
    //что-то не так с конструктором по умолчанию, выдаёт ошибки
    Matrix M(2),N(2),S(2);
    cout<<"enter matrix M:\n";  cin>>M;
    cout<<"enter matrix N:\n";  cin>>N;
    S=M+N;
    cout<<M;//не выводит матрицы
    cout<<S;
    return 0;
}