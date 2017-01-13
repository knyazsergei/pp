#pragma once
#include <Windows.h>
#include "SyncPrimitives.h"

class CBank;

class CBankClient
{
public:
	unsigned GetId();
	~CBankClient() = default;
	CBank *m_bank;
	unsigned m_id;
	CBankClient(CBank *bank, unsigned id, SyncPrimitives *typeSync);

private:
	static unsigned GetSleepDuration(CBankClient *client);
	static unsigned GetBalanceChangeValue();
	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

private:
	friend CBank;
	HANDLE m_handle;
	SyncPrimitives *m_syncPrimitives = nullptr;
};