#include "stdafx.h"
#include "AlgebraicAdditionsMatrixCalculator.h"


CAlgebraicAdditionsMatrixCalculator::CAlgebraicAdditionsMatrixCalculator()
{
	m_threadCount = std::thread::hardware_concurrency();
}

CAlgebraicAdditionsMatrixCalculator::CAlgebraicAdditionsMatrixCalculator(size_t count)
{
	m_threadCount = count;
}


CAlgebraicAdditionsMatrixCalculator::~CAlgebraicAdditionsMatrixCalculator()
{
}


void threadProcess(CMatrix & matrix, Matrix & result, size_t threadCount, size_t num)
{
	for (size_t i = num * matrix.GetSize() / threadCount; i < (num + 1) * matrix.GetSize() / threadCount; i++)
	{
		for (size_t j = 0; j < matrix.GetSize(); j++)
		{
			result[i][j] = matrix.CalcAlgebraicAddition(i, j);
		}
	}
}

Matrix CAlgebraicAdditionsMatrixCalculator::Calc(CMatrix matrix)
{
	Matrix result(matrix.GetSize(), std::vector<double>(matrix.GetSize()));
	vector<thread> threads(m_threadCount);

	if (m_threadCount == 1)
	{
		for (size_t i = 0; i < matrix.GetSize(); i++)
		{
			for (size_t j = 0; j < matrix.GetSize(); j++)
			{
				result[i][j] = matrix.CalcAlgebraicAddition(i, j);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_threadCount; i++)
		{
			threads[i] = std::thread(threadProcess, matrix, std::ref(result), m_threadCount, i);
			threads[i].join();
		}
	}
	return result;
}
