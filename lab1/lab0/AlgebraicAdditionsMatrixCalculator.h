#pragma once
#include "Definitions.h"
#include "Matrix.h"
#include <thread>

class CAlgebraicAdditionsMatrixCalculator
{
public:
	CAlgebraicAdditionsMatrixCalculator();
	CAlgebraicAdditionsMatrixCalculator(size_t count);
	Matrix Calc(CMatrix matrix);

	~CAlgebraicAdditionsMatrixCalculator();

private:
	size_t m_threadCount = 1;
};

