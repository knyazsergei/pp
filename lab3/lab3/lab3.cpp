// lab3.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <iomanip>
#include <random>
#include <utility>
#include <clocale>
#include "ProcessRunner.h"

long double random(long double A, long double B)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<long double> dist(A, B);
	return dist(mt);
}

bool InsideCircle(std::pair<double, double> circlePoint, double radius, std::pair<double, double> point)
{
	if (pow(point.second - circlePoint.second, 2) + pow(point.first - circlePoint.first, 2) < pow(radius, 2))
	{
		return true;
	}
	return false;
}

long double GetPi(size_t count = 10000 /*����� ����� �����*/)
{
	size_t innerCount = 0;//����� �����, �������� � ����
	std::pair<long double, long double> point;//����������

	long double radius = 1;
	for (size_t i = 0; i < count; i++)
	{
		point = { random(0, radius), random(0, radius) };
		if (InsideCircle({ 0, 0 }, radius, point))
			++innerCount;
	}
	return (long double)4 * innerCount / count;//��������� ��
}

int main(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	if(argc > 1)
	{
		if (argv[1] == L"/?")
		{
			std::cout << "��� ���������� ����� �� ������� �������� ���������� ������� � �������� ���������� ��������" << std::endl;
		}
		else
		{
			CProcessRunner processRunner;
			processRunner.RunServer();
			processRunner.RunClient(4);

		}
	}
	else
	{
		std::cout << "����������� ���������" << std::endl;
		return EXIT_FAILURE;
	}
	/*
	for (size_t i = 10; i < 23; i++)
	{
		std::cout 
			<< std::fixed 
			<< std::setprecision(5) 
			<< pow(2, i) 
			<< " ��������������� ����� �� : " 
			<< GetPi(pow(2, i)) 
			<< std::endl;
	}*/
	return EXIT_SUCCESS;
}