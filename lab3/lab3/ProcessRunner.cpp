#include "stdafx.h"
#include "ProcessRunner.h"

CProcessRunner::CProcessRunner()
{
}


CProcessRunner::~CProcessRunner()
{
	while (!serverDone)
	{

	}
	/*m_runnedServer.detach();
	for (size_t i = 0; i < m_runnedClients.size(); ++i)
	{
		m_runnedClients[i].detach();
	}*/
}

bool CProcessRunner::RunServer()
{
	std::cout << "Run server" << std::endl;
	m_server = std::make_unique<CServer>(m_port, serverDone);
	m_runnedServer = std::thread(&CServer::Run, m_server.get());
	m_runnedServer.detach();
	return true;
}

void CProcessRunner::RunClient(size_t count)
{
	std::cout << "Run clients" << std::endl;
	//m_clients.resize(count, std::make_unique<CClient>(m_port));
	//m_runnedClients.resize(count);


	for (size_t i = 0; i < count; ++i)
	{
		m_clients[i] = std::make_unique<CClient>(m_port, i);
		m_runnedClients[i] = std::thread(&CClient::SendData, m_clients[i].get());
		std::cout << m_runnedClients[i].get_id() << std::endl;
		m_runnedClients[i].detach();
	}
}
