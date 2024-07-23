#include "Matrix.h"
//последнее обновление 20.11.2012

//конструктор для случая если матрица НЕ квадратная
Matrix::Matrix(int m, int n)
{
	this->M = m;
	this->N = n;

	this->Matr.resize( M );
	for(int i=0; i<this->M; i++)
		this->Matr[i].resize( N );
}

//конструктор для случая если матрица квадратная
Matrix::Matrix(int size)
{
	this->N = this->M = size;

	this->Matr.resize( size );
	for(int i=0; i<size; i++)
		this->Matr[i].resize( size );
}

//получить значение матрицы с индексом (i,j)
double Matrix::Get(int i, int j)
{
	if( i<this->M && i>-1 )
		if( j<this->N && j>-1 )
			return Matr[i][j];
	return -DBL_MAX;
}

//установить значение матрицы с индексом (i,j)
int Matrix::Set(int i, int j, double value)
{
	if( i<this->M && i>-1 )
		if( j<this->N && j>-1 )
		{
			this->Matr[i][j] = value;
			return 1;
		}
	return 0;	//1 - успех, элемент добавлен
				//0 - неудача, элемент не добавлен
}

//оператор сложения двух матриц
Matrix Matrix::operator +(Matrix A)
{
	if( this->M == A._M() && this->N == A._N() )
	{
		Matrix C( A._M(),A._N() );

		for(int i=0; i<A._M(); i++)
			for(int j=0; j<A._N(); j++)
				C.Set( i, j, this->Matr[i][j] + A.Get(i,j) );
		return C;
	}
	return NULL;
}

//оператор вычитания двух матриц
Matrix Matrix::operator -(Matrix A)
{
	if( this->M == A._M() && this->N == A._N() )
	{
		Matrix C( A._M(),A._N() );

		for(int i=0; i<A._M(); i++)
			for(int j=0; j<A._N(); j++)
				C.Set( i, j, this->Matr[i][j] - A.Get(i,j) );
		return C;
	}
	return NULL;
}

//умножение матрицы на матрицу
Matrix Matrix::operator *(Matrix A)
{
	//this * A
	if( this->N == A._M() )
	{
		double t;
		Matrix C( this->M,A._N() );
		for(int i=0; i<C._M(); i++)
			for(int j=0; j<C._N(); j++)
			{
				t = 0.0;
				for(int k=0; k<this->N; k++)
					t += this->Matr[i][k]*A.Get(k,j);
				C.Set( i, j, t);
			}
		return C;
	}
	return NULL;
}

//умножение матрицы на скаляр
Matrix Matrix::operator *(double t)
{
	Matrix C( this->M, this->N );

	for(int i=0; i<this->M; i++)
		for(int j=0; j<this->N; j++)
			C.Set( i, j, this->Matr[i][j]*t );
	return C;
}

//присвоение матрицы одного числа (использовать только для инициализации матриц)
Matrix Matrix::operator =(double t)
{
	Matrix res(this->M, this->N);
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			res.Set(i,j, t );
	return res;
}

//обратная матрица
Matrix Matrix::InverseMatrix()
{
	if(M == N && fabs(this->Determinant())>1e-14)
	{
		Matrix Inverse(M);
		double DetInverse = this->Determinant();

		vector<double> Temp;
		Matrix AlgebraicComplement( M-1 );

		for(int i=0; i<M; i++)
			for(int j=0; j<M; j++)
			{
				Temp.clear();
				for(int ii=0; ii<M; ii++)
					for(int jj=0; jj<M; jj++)
					{
						if(i != ii && j != jj)
							Temp.push_back( this->Get(ii,jj) );
					}

				for(int ii=0; ii<M-1; ii++)
					for(int jj=0; jj<M-1; jj++)
						AlgebraicComplement.Set(ii, jj, Temp[ii*(M-1)+jj] );

				Inverse.Set(j,i, double(pow(-1.0,i+j+2)*AlgebraicComplement.Determinant()/DetInverse) );
			}
		return Inverse;
	}
	else
	{
		Matrix Inverse(M,N);
		for(int i=0; i<M; i++)
			for(int j=0; j<N; j++)
				Inverse.Set(i,j, -DBL_MAX );
		return Inverse;
	}
}

//для рекурсивного вычисления определителя матрицы (по определению по 1й строке)
double Matrix::Det(Matrix *A)
{
	double res = 0;
	if( A->M == 2 )
		return A->Get(0,0)*A->Get(1,1) - A->Get(1,0)*A->Get(0,1);
	else
	{
		for(int i=0; i<A->M; i++)
		{
			Matrix C(A->M-1);

			int j = -1;
			for(int l=0; l<A->_M(); l++)	//по столбцам
			{
				if(i != l)
					j++;

				for(int k=1; k<A->_M(); k++)		//по строкам
				{
					if(j>-1 && i != l)
						C.Set( k-1, j, A->Get(k,l) );
				}
			}

			res += pow(-1, (i+1)+(0+1) )*A->Get(0,i)*Det(&C);
		}
		return res;
	}
}

//определитель матрицы
double Matrix::Determinant()
{
	//чтоб матрица была квадратной
	if( this->M == this->N )
	{
		//если матрица небольшая
		if( this->M < 10 )
		{
			return Det(this);
		}
		else
		{
			//для случая,если матрица огромная
			if(this->M == 1)
				return this->Matr[0][0];
			if(this->M == 2)
				return (Matr[0][0]*Matr[1][1] - Matr[1][0]*Matr[0][1]);
			if(this->M == 3)
				return (Matr[0][0]*Matr[1][1]*Matr[2][2] + Matr[1][0]*Matr[2][1]*Matr[0][2] + Matr[0][1]*Matr[1][2]*Matr[2][0] 
						- Matr[2][0]*Matr[1][1]*Matr[0][2] - Matr[2][1]*Matr[1][2]*Matr[0][0] - Matr[1][0]*Matr[0][1]*Matr[2][2]);
			if(this->M > 3)
			{
				double s;
				vector<vector<double>> Temp;
				Temp = Matr;
				for(int i=0; i<M; i++)
				{
					for(int j=i+1; j<M; j++)
					{
						s = -Temp[j][i]/Temp[i][i];
						for(int k=0; k<M; k++)
							Temp[j][k] = Temp[i][k]*s + Temp[j][k];
					}
				}

				s = 1.0;
				for(int i=0; i<M; i++)
					s *= Temp[i][i];
				return s;
			}
		}
	}
	else
		return -DBL_MAX;
}

//приведение матрицы к трапецеидальному (нижнетреугольному) виду
Matrix Matrix::TriangularType()
{
	Matrix Res(this->M, this->N);

	double s;
	vector<vector<double>> Temp;
	Temp = Matr;
	for(int i=0; i<M; i++)
	{
		for(int j=i+1; j<M; j++)
		{
			s = -Temp[j][i]/Temp[i][i];
			for(int k=0; k<M; k++)
				Temp[j][k] = Temp[i][k]*s + Temp[j][k];
		}
	}

	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			Res.Set(i,j, Temp[i][j]);

	return Res;
}

//транспонирование матрицы
Matrix Matrix::Transpose()
{
	Matrix Res(this->N, this->M);

	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			Res.Set( i, j, this->Matr[j][i] );

	return Res;
}

//собственные значения матрицы
vector<double> Matrix::Eigenvalues()
{
	if(M == N)
	{
		double s;
		vector<vector<double>> Temp;
		Temp = Matr;
		for(int i=0; i<M; i++)
		{
			for(int j=i+1; j<M; j++)
			{
				s = -Temp[j][i]/Temp[i][i];
				for(int k=0; k<M; k++)
					Temp[j][k] = Temp[i][k]*s + Temp[j][k];
			}
		}

		vector<double> res( M );
		for(int i=0; i<M; i++)
			res[i] = Temp[i][i];
		return res;
	}
	vector<double> res( max(M,N) );
	for(int i=0; i<max(M,N); i++)
		res[i] = -DBL_MAX;
	return res;
}

//вычисление евклидовой нормы матрицы
double Matrix::EuclideanNorm()
{
	double res = 0.0;
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			res += Matr[i][j]*Matr[i][j];
	return sqrt( res );
}

//след матрицы
double Matrix::Trace()
{
	if(this->M == this->N)
	{
		double res = 0.0;
		for(int i=0; i<M; i++)
			res += Matr[i][i];
		return res;
	}
	return -DBL_MAX;
}

//получение кол-ва строк матрицы
int Matrix::_M()
{
	return this->M;
}

//получение кол-ва столбцов матрицы
int Matrix::_N()
{
	return this->N;
}

//сумма по строкам
double Matrix::mNorma()
{
	vector<double> mas( this->M );
	for(int i=0; i<M; i++)
	{
		mas[i] = 0.0;
		for(int j=0; j<N; j++)
			mas[i] += Matr[i][j];
	}
	return *std::max(mas.begin(), mas.end() );
}

//сумма по столбцам
double Matrix::lNorma()
{
	vector<double> mas( this->N );
	for(int i=0; i<N; i++)
	{
		mas[i] = 0.0;
		for(int j=0; j<M; j++)
			mas[i] += Matr[j][i];
	}
	return *std::max(mas.begin(), mas.end() );
}

//обобщеная евклидова
double Matrix::pNorma(int p)
{
	double res = 0.0;
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			res += pow( Matr[i][j], p );
	return pow( res, double(1/p) );
}

//напечатать матрицу
void Matrix::print(FILE *out)
{
	if(out != NULL)
	{
		for(int i=0; i<M; i++)
		{
			for(int j=0; j<N; j++)
				fprintf(out,"%.15lf\t",Matr[i][j]);
			fprintf(out,"\n");
		}
	}

	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
			printf("%lf\t",Matr[i][j]);
		printf("\n");
	}
}

//произвольная матрица. rand()%(right+1) + left
void Matrix::RandomMatrix(int left, int right)
{
	for(int i=0; i<M; i++)
		for(int j=0; j<N; j++)
			Matr[i][j] = rand()%(right+1) + left;
}

//единичная матрица размерности k
Matrix Matrix::IdentityMatrix(int k)
{
	Matrix C(k);
	for(int i=0; i<k; i++)
		for(int j=0; j<k; j++)
			if(i==j)
				C.Set(i,j, 1);
			else
				C.Set(i,j, 0);
	return C;
}

//деструктор
Matrix::~Matrix()
{
	this->Matr.clear();
}
