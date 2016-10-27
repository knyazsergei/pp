// lab0.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include "Matrix.h"

using namespace std;

int main()
{
	CMatrix matrix({
		{1, 3, 2},
		{3, 45, 1},
		{2, 4, 2}
	});
	cout << matrix.CalcMinor(1, 1);
	//1x1 = 86
	/*
	for (size_t i = 0;i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			matrix[i][j] = i + pow(j, 2);
		}
	}
	
	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
	start = std::chrono::high_resolution_clock::now();

	auto newMatrix = matrix;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix.size(); ++j)
		{
			newMatrix[i][j] = pow(-1, i+j) * GetDet(matrix, i, j);
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = (stop-start); 
	cout << diff.count() << endl;
	//printMatrix(matrix);
	*/
	return 0;
}

