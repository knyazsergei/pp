#include "stdafx.h"
#include "Bank.h"
#include "BankClient.h"
#include "SyncPrimitives.h"
#include <iostream>
#include <string>
#include <sstream>

void PrintHelp()
{
	std::cout << "::::::::A reminder to use the program with the key::::::::\n\n\n" << std::endl;
	std::cout << "when using the program with a data synchronization program \n will work properly without it - no" << std::endl;
	std::cout << "WARNINGS!!!!! Use with key !!!!! Use without a key \nfor informational purposes only !!!!! \n\n" << std::endl;
}

TypeSyncPrimitives EnterTypeSyncPrimitives()
{
	std::string keyValue;
	while (true)
	{
		std::cout << "Please enter whether you want to use synchronization primitives or not"
			<< " (critical section / mutex / semaphore / event / not use / /?) : ";
		std::getline(std::cin, keyValue);
		if (keyValue == "critical section")
		{
			return TypeSyncPrimitives::CRITICAL_SECTION;
		}
		else if (keyValue == "mutex")
		{
			return TypeSyncPrimitives::MUTEX;
		}
		else if (keyValue == "semaphore")
		{
			return TypeSyncPrimitives::SEMAPHORE;
		}
		else if (keyValue == "event")
		{
			return TypeSyncPrimitives::EVENT;
		}
		else if (keyValue == "not use")
		{
			return TypeSyncPrimitives::NOT;
		}
		else if (keyValue == "/?")
		{
			PrintHelp();
		}
		else
		{
			std::cout << "You enter an incorrect key value. Try again" << std::endl;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error! Usage program.exe <client number> " << std::endl;
		return EXIT_FAILURE;
	}
	std::stringstream ss;
	ss << argv[1];
	std::string argm;
	ss >> argm;
			 
	if (argm == "/?")
	{
		PrintHelp();
		return EXIT_FAILURE;
	}
	TypeSyncPrimitives key;
	key = EnterTypeSyncPrimitives();
	size_t clientNumber = atoi(argv[1]);



	CBank* bank = new CBank(key);

	std::vector<CBankClient*> clients;

	for (size_t i = 0; i != clientNumber; ++i)
	{
		clients.push_back(bank->CreateClient());
	}


	WaitForMultipleObjects(static_cast<DWORD>(bank->GetClientsCount()), bank->GetClientsHandles(), TRUE, INFINITE);
	

	return EXIT_SUCCESS;
}