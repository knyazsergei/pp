#pragma once
#include <winsock2.h> 
#include <ws2tcpip.h>
#include <stdexcept>
#include <string>
#include <atomic>

#pragma comment(lib, "Ws2_32.lib")

class CServer
{
public:
	CServer(unsigned port, std::atomic<bool> & done);
	void Run();
	~CServer();

private:
	unsigned m_defaultPort = 27015;
	std::atomic<bool> * m_done;
};

