#include "stdafx.h"
#include "Matrix.h"


CMatrix::CMatrix(Matrix && matrix) :
	m_matrix(std::move(matrix))
{
}


CMatrix::~CMatrix()
{
}

double CMatrix::CalcAlgebraicAddition(size_t iPos, size_t jPos)
{
	auto det = CalcMinor(iPos, jPos);
	return static_cast<double>(std::pow(-1, iPos + jPos + 2));
}

double CMatrix::CalcMinor(size_t iPos, size_t jPos)
{
	auto matrixSize = m_matrix.size();
	Matrix newMatrix(matrixSize - 1, std::vector<double>(matrixSize - 1));
	CutMatrix(m_matrix, newMatrix, iPos, jPos);
	auto det = CalcDet(newMatrix);
	return det;
}

double CMatrix::CalcDet(Matrix matrix)
{
	//Методом гаусса
	size_t i, j, k;
	double det = 1;
	double b = 0;

	for (i = 0; i < matrix.size(); i++)
	{
		for (j = i + 1; j < matrix[0].size(); j++)
		{
			if (matrix[i][i] == 0)
			{
				if (matrix[i][j] == 0)
				{
					b = 0;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				b = matrix[j][i] / matrix[i][i];
			}
			for (k = i; k < matrix.size(); k++)
			{
				matrix[j][k] = matrix[j][k] - matrix[i][k] * b;
			}
		}
		det *= matrix[i][i];
	}
	return det;
}

void CMatrix::CutMatrix(const Matrix & matrix, Matrix & newMatrix, size_t i, size_t j)
{
	auto matrixSize = matrix.size();
	size_t ki, kj;
	size_t di, dj;

	di = 0;
	for (ki = 0; ki < matrixSize - 1; ki++)
	{
		if (di == i)
		{
			di++;
		}
		dj = 0;
		for (kj = 0; kj < matrixSize - 1; kj++)
		{
			if (dj == j)
			{
				dj++;
			}
			newMatrix[ki][kj] = matrix[di][dj];
			dj++;
		}
		di++;
	}
}
