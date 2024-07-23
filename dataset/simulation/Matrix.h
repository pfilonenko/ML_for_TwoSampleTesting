#include"Sample.h"

#pragma once

class Matrix{
	private:
		int N,M;	//M - кол-во строк, N - столбцов
		vector<vector<double>> Matr;	//сама матрица

		double Det(Matrix *A);	//для рекурсивного вычисления определителя матрицы (по определению по 1й строке)
	public:
		Matrix(int m, int n);	//конструктор для случая если матрица НЕ квадратная
		Matrix(int size);		//конструктор для случая если матрица квадратная
		~Matrix();				//деструктор

		int _M();								//получение кол-ва строк матрицы
		int _N();								//получение кол-ва столбцов матрицы
		double Get(int i, int j);				//получить значение матрицы с индексом (i,j)
		int Set(int i, int j, double value);	//установить значение матрицы с индексом (i,j)

		Matrix operator +(Matrix A);	//оператор сложения двух матриц
		Matrix operator -(Matrix A);	//оператор вычитания двух матриц
		Matrix operator *(Matrix A);	//умножение матрицы на матрицу
		Matrix operator *(double t);	//умножение матрицы на скаляр
		Matrix operator =(double t);	//присвоение матрицы одного числа (использовать только для инициализации матриц)

		
		double Determinant();			//определитель матрицы
		double Trace();					//след матрицы
		double EuclideanNorm();			//вычисление евклидовой нормы матрицы
		double mNorma();			//сумма по строкам
		double lNorma();			//сумма по столбцам
		double pNorma(int p);			//обобщеная евклидова

		vector<double> Eigenvalues();	//собственные значения матрицы
		Matrix InverseMatrix();			//обратная матрица		
		Matrix Transpose();				//транспонирование матрицы
		Matrix TriangularType();		//приведение матрицы к трапецеидальному (нижнетреугольному) виду
		Matrix Matrix::IdentityMatrix(int k); //единичная матрица размерности k

		void print(FILE *out);					//напечатать матрицу
		void RandomMatrix(int left, int right);	//произвольная матрица. rand()%(right+1) + left
};