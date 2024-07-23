#include"Sample.h"

#pragma once

class Matrix{
	private:
		int N,M;	//M - ���-�� �����, N - ��������
		vector<vector<double>> Matr;	//���� �������

		double Det(Matrix *A);	//��� ������������ ���������� ������������ ������� (�� ����������� �� 1� ������)
	public:
		Matrix(int m, int n);	//����������� ��� ������ ���� ������� �� ����������
		Matrix(int size);		//����������� ��� ������ ���� ������� ����������
		~Matrix();				//����������

		int _M();								//��������� ���-�� ����� �������
		int _N();								//��������� ���-�� �������� �������
		double Get(int i, int j);				//�������� �������� ������� � �������� (i,j)
		int Set(int i, int j, double value);	//���������� �������� ������� � �������� (i,j)

		Matrix operator +(Matrix A);	//�������� �������� ���� ������
		Matrix operator -(Matrix A);	//�������� ��������� ���� ������
		Matrix operator *(Matrix A);	//��������� ������� �� �������
		Matrix operator *(double t);	//��������� ������� �� ������
		Matrix operator =(double t);	//���������� ������� ������ ����� (������������ ������ ��� ������������� ������)

		
		double Determinant();			//������������ �������
		double Trace();					//���� �������
		double EuclideanNorm();			//���������� ���������� ����� �������
		double mNorma();			//����� �� �������
		double lNorma();			//����� �� ��������
		double pNorma(int p);			//��������� ���������

		vector<double> Eigenvalues();	//����������� �������� �������
		Matrix InverseMatrix();			//�������� �������		
		Matrix Transpose();				//���������������� �������
		Matrix TriangularType();		//���������� ������� � ���������������� (�����������������) ����
		Matrix Matrix::IdentityMatrix(int k); //��������� ������� ����������� k

		void print(FILE *out);					//���������� �������
		void RandomMatrix(int left, int right);	//������������ �������. rand()%(right+1) + left
};