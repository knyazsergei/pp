// lab0.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Definitions.h"
#include "Matrix.h"
#include "raw_data.h"
#include <chrono>
#include <thread>
#include <utility>

std::chrono::duration<double> Line(CMatrix matrix, Matrix & result)
{
	Matrix rmatrix(matrix.GetSize(), std::vector<double>(matrix.GetSize()));

	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
	start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < matrix.GetSize(); i++)
	{
		for (size_t j = 0; j < matrix.GetSize(); j++)
		{
			result[i][j] = matrix.CalcAlgebraicAddition(i, j);
		}
	}

	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;
	return diff;
}

void threadProcess(CMatrix & matrix, Matrix & result, size_t threadCount, size_t num)
{
	for (size_t i = num * matrix.GetSize() / threadCount; i < (num+1) * matrix.GetSize() / threadCount; i++)
	{
		for (size_t j = 0; j < matrix.GetSize(); j++)
		{
			result[i][j] = matrix.CalcAlgebraicAddition(i, j);
		}
	}
}

std::chrono::duration<double> Multi(CMatrix matrix, size_t threadCount, Matrix & result)
{
	std::vector<thread> threads(threadCount);
	result.resize(matrix.GetSize(), std::vector<double>(matrix.GetSize()));

	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
	start = std::chrono::high_resolution_clock::now();
	
	for (size_t i = 0; i < threadCount; i++)
	{
		threads[i] = std::thread(threadProcess, matrix, std::ref(result), threadCount, i);
		threads[i].join();
	}

	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = stop - start;
	return diff;
}

int main(int argc, char * argv[])
{
	Matrix matrixResult;
	CMatrix matrix(MATRIX30x30);

	if (argc != 1)
	{
		size_t threadsCount = atoi(argv[1]);
		if (threadsCount > 0)
			cout << Multi(matrix, threadsCount, matrixResult).count();
		else
			cout << Line(matrix, matrixResult).count();
	}
	else
	{
		vector<std::chrono::duration<double>> results(17);
		size_t countTests = 3;
		if (argc == 3)
		{
			results.resize(atoi(argv[1]));
			countTests = atoi(argv[2]);
		}
		

		for (size_t j = 0; j < countTests; j++)
			for (size_t i = 1; i < results.size() + 1; i++)
				results[i - 1] += Multi(matrix, i, matrixResult);

		size_t i = 1;
		for (auto & result : results)
			cout << i++ << ": " << result.count() / countTests << endl;
	}
	return EXIT_SUCCESS;
}

