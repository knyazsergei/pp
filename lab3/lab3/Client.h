#pragma once
#include <winsock2.h> 
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <sstream>

class CClient
{
public:
	CClient(unsigned port, size_t id);
	void SendData();
	~CClient();
	CClient(const CClient&) = delete;
	CClient& operator=(const CClient&) = delete;
private:
	unsigned m_defaultPort = 27015;
	SOCKET m_clientSocket;
	SOCKET m_listenSocket;
};

