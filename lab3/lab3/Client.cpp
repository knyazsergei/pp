#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"
#include <thread>

CClient::CClient(unsigned port, size_t id) :m_defaultPort(port)
{
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "Run client " << this_id << " " << id  <<  std::endl;
	//Инициализация WSA
	#ifndef NDEBUG
	std::cout << "Инициализация WSA\n" << std::endl;
	#endif
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0)
	{
		throw std::runtime_error("Ошибка WSAStartup: " + std::to_string(result));
	}


	//Создание сокета

	 m_clientSocket = INVALID_SOCKET;
	 m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_clientSocket == INVALID_SOCKET)
	{
		WSACleanup();
		throw std::runtime_error("Ошибка socket() " + std::to_string(result));
	}
}

void CClient::SendData()
{
	//Присоединение к серверу

	#define ip "127.0.0.1"

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr(ip);
	clientService.sin_port = htons(m_defaultPort);

	int result = connect(
		m_clientSocket,
		reinterpret_cast< SOCKADDR* >(&clientService),
		sizeof(clientService)
	);
	if (result != 0)
	{
		WSACleanup();
		auto error = std::to_string(WSAGetLastError());
		throw std::runtime_error("Ошибка в connect(): " + error);
	}


	//Передача данных серверу
	std::thread::id this_id = std::this_thread::get_id();
	std::stringstream ss;
	ss << "Thread client " << std::this_thread::get_id();
	std::string data = ss.str();
	result = send(m_clientSocket, data.c_str(), static_cast< int >(strlen(data.c_str())), 0);
	if (result < 0)
	{
		auto error = std::to_string(WSAGetLastError());
		throw std::runtime_error("Ошибка в connect(): " + error);
	}

	//Прием данных от сервера
	#define bufsize 256

	char buf[bufsize];
	int r;
	do
	{
		r = recv(m_clientSocket, buf, bufsize, 0);
		if (r > 0)
		{
			std::cout;
			std::cout << std::this_thread::get_id << "Приянтно " << r << " байт" << buf << "\n" << std::endl;
		}
		else if (r == 0)
			std::cout << "Соединение разорвано\n" << std::endl;
		else
			std::cout << "Ошибка в recv():\n " << WSAGetLastError() << std::endl;
	} while (r > 0);

	closesocket(m_clientSocket);
	// Если работа с сокетами больше не предполагается вызываем WSACleanup()
	WSACleanup();
}


CClient::~CClient()
{
}
