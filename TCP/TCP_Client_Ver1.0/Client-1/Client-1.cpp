// Client-1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "iostream"
#include "WinSock2.h"
#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 6000
#define SERVER_IP	"127.0.0.1"

class TCPClient
{
public:
	TCPClient()
		: mConnectSocket(INVALID_SOCKET)
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			// could not find a usable WinSock DLL
			std::cout << "Can't find usable Winsock dll" << std::endl;
			return;
		}

		if (LOBYTE(wsaData.wVersion) != 2 || 
			HIBYTE(wsaData.wVersion) != 2)
		{
			// could not find a usable Winsock DLL
			WSACleanup();
			return;
		}

		// �����׽���
		mConnectSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (mConnectSocket == INVALID_SOCKET)
		{
			int errorCode = GetLastError();
			std::cout << "�����׽���ʧ�� " << "ERR code: " << errorCode << std::endl;
			return;
		}

		// ����������IP�Ͷ˿ں�
		mServerAddr.sin_family = AF_INET;
		mServerAddr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
		mServerAddr.sin_port = htons((u_short)SERVER_PORT);

	}

	~TCPClient()
	{
		::closesocket(mConnectSocket);
		std::cout << "�ر�TCP�������ɹ�" << std::endl;
	}

	void run()
	{
		// Connect to server
		if (connect(mConnectSocket, (SOCKADDR*) &mServerAddr, sizeof(mServerAddr)) == SOCKET_ERROR)
		{
			std::cout << "Failed to connect." << std::endl;
			WSACleanup();
			return;
		}

		std::cout << "����TCP�������ɹ�" << std::endl;
	}
protected:
private:
	SOCKET mConnectSocket;		// �������׽��־��
	sockaddr_in mServerAddr;	// ��������ַ
};

int main()
{
	TCPClient client;
	client.run();

	std::cout << "Press Enter Key to quit." << std::endl;
	getchar();

	return 0;
}
