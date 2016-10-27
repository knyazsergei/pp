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

	
	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
	start = std::chrono::high_resolution_clock::now();
	matrix.CalcAlgebraicAddition(1, 1);
	stop = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double> diff = (stop-start); 
	cout << "Time: " << diff.count() << endl;
	
	return 0;
}

