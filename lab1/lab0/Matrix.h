#pragma once
#include "Definitions.h"

class CMatrix
{
public:
	CMatrix(Matrix matrix);
	~CMatrix();
	double CalcAlgebraicAddition(size_t iPos, size_t jPos);

	size_t GetSize()const;
private:
	double CalcMinor(size_t iPos, size_t jPos);
	double CalcDet(Matrix matrix);
	void CutMatrix(const Matrix & mas, Matrix & p, size_t i, size_t j);

	Matrix m_matrix;
};