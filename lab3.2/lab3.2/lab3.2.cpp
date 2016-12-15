// lab3.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <winsock2.h> 
#include <ws2tcpip.h>
#include <iostream>
#include <clocale>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
	//server
	//Русский текст в консоли
	setlocale(LC_CTYPE, "rus");

	//Инициализация WSA
	std::cout << "Инициализация WSA" << std::endl;
	int iResult;

	WSAData d;
	iResult = WSAStartup(MAKEWORD(2, 2), &d);
	if (iResult != 0)
	{
		std::cout << "Error at WSAStartup: " << iResult;
		return 1;
	}

	//Подготовка данных для создания сокета
	std::cout << "Подготовка данных для создания сокета" << std::endl;
	#define DEFAULT_PORT "27015"

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		std::cout << "Ошибка getaddrinfo: " << iResult;
		WSACleanup();
		return 1;
	}


	//Создание сокета
	std::cout << "Создание сокета" << std::endl;
	SOCKET listenSocket = INVALID_SOCKET;
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError();
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	//Связывание сокета с сетвевым адресом
	std::cout << "Связывание сокета с сетвевым адресом" << std::endl;
	iResult = bind(listenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		std::cout << "Bind failed with error: " << WSAGetLastError();
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	//Прослушивание подключений
	std::cout << "Прослушивание подключений" << std::endl;
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Listen failed with error: " << WSAGetLastError();
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	//Обработка запроса на подключение
	std::cout << "Обработка запроса на подключение" << std::endl;
	SOCKET ClientSocket;

	ClientSocket = INVALID_SOCKET;

	ClientSocket = accept(listenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		std::cout << "Accept failed with error: " << WSAGetLastError();
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// Обмен данными
	std::cout << "Обмен данными" << std::endl;
	#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	do
	{
		// Принимаем данные от клиента
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			std::cout << "Принято " << iResult << " байт" << recvbuf << std::endl;

			// Отправляем данные, принтые от клиента, обратно
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				std::cout << "Send failed with error: " << WSAGetLastError();
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			std::cout << "Отправлено " << iSendResult << " байт";
		}
		else if (iResult == 0)
			std::cout << "Соединение закрыто..." << std::endl;
		else
		{
			std::cout << "Ошибка recv " << WSAGetLastError();
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);


    return 0;
}

