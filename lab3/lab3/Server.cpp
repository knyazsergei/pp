#include "stdafx.h"
#include "Server.h"
#include <thread>

CServer::CServer(unsigned port, std::atomic<bool> & done) :m_defaultPort(port), m_done(&done)
{

}

void CServer::Run()
{
	std::thread::id this_id = std::this_thread::get_id();
	std::cout << "Run server " << this_id << "\n" << std::endl;
	//������������� WSA
	#ifndef NDEBUG
	std::cout << "������������� WSA\n" << std::endl;
	#endif

	int iResult;

	WSAData d;
	iResult = WSAStartup(MAKEWORD(2, 2), &d);
	if (iResult != 0)
	{
		throw std::runtime_error("Error at WSAStartup: " + std::to_string(iResult));
	}

	//���������� ������ ��� �������� ������

	#ifndef NDEBUG
	std::cout << "���������� ������ ��� �������� ������\n" << std::endl;
	#endif

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, std::to_string(m_defaultPort).c_str(), &hints, &result);
	if (iResult != 0)
	{
		WSACleanup();
		throw std::runtime_error("������ getaddrinfo: " + std::to_string(iResult));
	}


	//�������� ������
	#ifndef NDEBUG
	std::cout << "�������� ������\n" << std::endl;
	#endif
	SOCKET listenSocket = INVALID_SOCKET;
	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (listenSocket == INVALID_SOCKET)
	{
		freeaddrinfo(result);
		WSACleanup();
		throw std::runtime_error("Error at socket(): " + std::to_string(WSAGetLastError()));
	}

	//���������� ������ � �������� �������
	#ifndef NDEBUG
	std::cout << "���������� ������ � �������� �������\n" << std::endl;
	#endif
	iResult = bind(listenSocket, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		freeaddrinfo(result);
		closesocket(listenSocket);
		WSACleanup();
		throw std::runtime_error("Bind failed with error: " + std::to_string(WSAGetLastError()));
	}

	freeaddrinfo(result);

	//������������� �����������
	#ifndef NDEBUG
	std::cout << "������������� �����������\n" << std::endl;
	#endif
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(listenSocket);
		WSACleanup();
		throw std::runtime_error("Listen failed with error: " + std::to_string(WSAGetLastError()));
	}

	//��������� ������� �� �����������
	#ifndef NDEBUG
	std::cout << "��������� ������� �� �����������\n" << std::endl;
	#endif
	SOCKET ClientSocket;

	ClientSocket = INVALID_SOCKET;

	ClientSocket = accept(listenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET)
	{
		closesocket(listenSocket);
		WSACleanup();
		throw std::runtime_error("Accept failed with error: " + std::to_string(WSAGetLastError()));
	}

	// ����� �������
	#ifndef NDEBUG
	std::cout << "����� �������\n" << std::endl;
	#endif

	#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	do
	{
		std::cout << "wait" << std::endl;
		// ��������� ������ �� �������
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
		{
			#ifndef NDEBUG
			std::cout << "������� " << iResult << " ���� " << recvbuf << '\n'<< std::endl;
			#endif

			// ���������� ������, ������� �� �������, �������
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR)
			{
				closesocket(ClientSocket);
				WSACleanup();
				throw std::runtime_error("Send failed with error:" + std::to_string(WSAGetLastError()));
			}
			#ifndef NDEBUG
			std::cout << "���������� " << iSendResult << " ����\n";
			#endif
		}
		else if (iResult == 0)
		{
			#ifndef NDEBUG
			std::cout << "���������� �������...\n" << std::endl;
			#endif
		}
		else
		{
			closesocket(ClientSocket);
			WSACleanup();
			throw std::runtime_error("������ recv " + std::to_string(WSAGetLastError()));
		}
	} while (iResult > 0);
}

CServer::~CServer()
{
	*m_done = true;
}
