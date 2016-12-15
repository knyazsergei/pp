#pragma once
#include <memory>
#include <thread>
#include <array>
#include "Server.h"
#include "Client.h"
#include <atomic>

class CProcessRunner
{
public:
	CProcessRunner();
	~CProcessRunner();
	bool RunServer();

	void RunClient(size_t count);

private:
	std::unique_ptr<CServer> m_server;
	std::thread m_runnedServer;
	unsigned m_port = 27015;

	std::array<std::unique_ptr<CClient>, 4> m_clients;
	std::array<std::thread, 4> m_runnedClients;

	std::atomic<bool> serverDone = false;
};

