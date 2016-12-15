// lab3.1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <winsock2.h> 
#include <ws2tcpip.h>
#include <iostream>
#include <clocale>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	//client
	//������� ����� � �������
	setlocale(LC_CTYPE, "rus");

	//������������� WSA
	WSADATA wsaData;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		std::cout << "������ WSAStartup: " << result << std::endl;
		return 1;
	}

	//�������� ������

	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "������ socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	//������������� � �������

	#define ip "127.0.0.1"
	#define port 27015

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(ip);
	clientService.sin_port = htons(port);

	result = connect(
		clientSocket,
		reinterpret_cast< SOCKADDR* >(&clientService),
		sizeof(clientService)
	);
	if (result != 0)
	{
		std::cout << "������ � connect(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	//�������� ������ �������
	char data[] = "Test\0";
	result = send(clientSocket, data, static_cast< int >(strlen(data)), 0);
	if (result < 0)
	{
		std::cout << "������ � send(): " << WSAGetLastError() << std::endl;
		return 1;
	}

	//����� ������ �� �������
	#define bufsize 256

	char buf[bufsize];
	int r;
	do
	{
		r = recv(clientSocket, buf, bufsize, 0);
		if (r > 0)
			std::cout << "�������� " << r << " ����" << buf << std::endl;
		else if (r == 0)
			std::cout << "���������� ���������" << std::endl;
		else
			std::cout << "������ � recv(): " << WSAGetLastError() << std::endl;
	} while (r > 0);

	closesocket(clientSocket);
	// ���� ������ � �������� ������ �� �������������� �������� WSACleanup()
	WSACleanup();
	return 0;
}


