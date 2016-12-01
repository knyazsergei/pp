// lab0.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Definitions.h"
#include "Matrix.h"
#include "raw_data.h"
#include "AlgebraicAdditionsMatrixCalculator.h"

int main(int argc, char * argv[])
{
	CMatrix matrix(MATRIX30x30);

	if (argc != 1)
	{
		size_t threadsCount = atoi(argv[1]);
		CAlgebraicAdditionsMatrixCalculator algCalc;
		
		std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
		start = std::chrono::high_resolution_clock::now();

		algCalc.Calc(matrix);

		stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = stop - start;
		cout << diff.count();
	}

	return EXIT_SUCCESS;
}

