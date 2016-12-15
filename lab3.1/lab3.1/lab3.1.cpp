// lab3.1.cpp: определяет точку входа для консольного приложения.
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
	//Русский текст в консоли
	setlocale(LC_CTYPE, "rus");

	//Инициализация WSA
	WSADATA wsaData;
	int result;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		std::cout << "Ошибка WSAStartup: " << result << std::endl;
		return 1;
	}

	//Создание сокета

	SOCKET clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "Ошибка socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	//Присоединение к серверу

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
		std::cout << "Ошибка в connect(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	//Передача данных серверу
	char data[] = "Test\0";
	result = send(clientSocket, data, static_cast< int >(strlen(data)), 0);
	if (result < 0)
	{
		std::cout << "Ошибка в send(): " << WSAGetLastError() << std::endl;
		return 1;
	}

	//Прием данных от сервера
	#define bufsize 256

	char buf[bufsize];
	int r;
	do
	{
		r = recv(clientSocket, buf, bufsize, 0);
		if (r > 0)
			std::cout << "Приянтно " << r << " байт" << buf << std::endl;
		else if (r == 0)
			std::cout << "Соединение разорвано" << std::endl;
		else
			std::cout << "Ошибка в recv(): " << WSAGetLastError() << std::endl;
	} while (r > 0);

	closesocket(clientSocket);
	// Если работа с сокетами больше не предполагается вызываем WSACleanup()
	WSACleanup();
	return 0;
}


