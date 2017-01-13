#include "BankClient.h"
#include "Bank.h"
#include "SyncPrimitives.h"

CBankClient::CBankClient(CBank *bank, unsigned id, SyncPrimitives *primitives)
	: m_syncPrimitives(primitives)
	, m_bank(bank)
	, m_id(id)
	, m_handle(CreateThread(NULL, 0, ThreadFunction, this, 0, NULL))
{
}


unsigned CBankClient::GetId()
{
	return m_id;
}

void SomeLongOperation(unsigned time)
{
	Sleep(time);
}

DWORD WINAPI CBankClient::ThreadFunction(LPVOID lpParam)
{
	CBankClient *client = (CBankClient*)lpParam;
	srand(client->m_id);
	while (true)
	{
		SomeLongOperation(GetSleepDuration(client));
		//TODO:: вынести дублирование GetBalanceChangeValue
		switch (client->m_syncPrimitives->type)
		{
		case TypeSyncPrimitives::CRITICAL_SECTION:
			EnterCriticalSection(&client->m_syncPrimitives->critical_section);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			LeaveCriticalSection(&client->m_syncPrimitives->critical_section);
			break;
		case TypeSyncPrimitives::SEMAPHORE:
			WaitForSingleObject(client->m_syncPrimitives->hSemaphore, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			ReleaseSemaphore(client->m_syncPrimitives->hSemaphore, 1, NULL);
			break;
		case TypeSyncPrimitives::MUTEX:
			WaitForSingleObject(client->m_syncPrimitives->hMutex, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			ReleaseMutex(client->m_syncPrimitives->hMutex);
			break;
		case TypeSyncPrimitives::EVENT:
			WaitForSingleObject(client->m_syncPrimitives->hEvent, INFINITE);
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			SetEvent(client->m_syncPrimitives->hEvent);
			break;
		case TypeSyncPrimitives::NOT:
			client->m_bank->UpdateClientBalance(*client, GetBalanceChangeValue());
			break;
		}
	}
	return 0;
}


unsigned CBankClient::GetSleepDuration(CBankClient *client)
{
	return (1000 + rand() % 3000) * (client->m_id + 1);
}


unsigned CBankClient::GetBalanceChangeValue()
{
	// -100 .. 100
	return (rand() % 201 - 100);
}