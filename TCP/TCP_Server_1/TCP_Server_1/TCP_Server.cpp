#include "iostream"
#include "WinSock2.h"
#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 6000
#define SEND_STRING "TCP Server"

class TCPServer
{
public:
	TCPServer()
		: mServerSocket(INVALID_SOCKET)
	{
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;

		wVersionRequested = MAKEWORD(2, 2);

		err = WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			// could not find a usable WinSock DLL
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
		mServerSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (mServerSocket == INVALID_SOCKET)
		{
			int errorCode = GetLastError();
			std::cout << "�����׽���ʧ�� " << "ERR code: " << errorCode << std::endl;
			return;
		}

		// ����������IP�Ͷ˿ں�
		mServerAddr.sin_family = AF_INET;
		mServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		mServerAddr.sin_port = htons((u_short)SERVER_PORT);

		// ��IP�Ͷ˿�
		if (::bind(mServerSocket, (sockaddr*)&mServerAddr, sizeof(mServerAddr)) == SOCKET_ERROR)
		{
			std::cout << "��IP�Ͷ˿�ʧ��" << std::endl;
			return;
		}

		// �����ͻ����������ͬʱ����������Ϊ10
		if (::listen(mServerSocket, SOMAXCONN) == SOCKET_ERROR)
		{
			std::cout << "�����˿�ʧ��" << std::endl;
			return;
		}

		std::cout << "����TCP�������ɹ�" << std::endl;
	}

	~TCPServer()
	{
		::closesocket(mServerSocket);
		std::cout << "�ر�TCP�������ɹ�" << std::endl;
	}

	void run()
	{
		int nAcceptAddrLen = sizeof(mAcceptAddr);

		for (;;)
		{
			// ��������ʽ���ȴ����տͻ�������
			mAcceptSocket = ::accept(mServerSocket, (struct sockaddr*)&mAcceptAddr, &nAcceptAddrLen);
			std::cout << "���ܿͻ���IP: " << inet_ntoa(mAcceptAddr.sin_addr) << std::endl;

			// ������Ϣ
			int ret = ::send(mAcceptSocket, SEND_STRING, (int)strlen(SEND_STRING), 0);
			if (ret != 0)
			{
				std::cout << "������Ϣ�ɹ�" << std::endl;
			}

			// �رտͻ����׽���
			::closesocket(mAcceptSocket);
			std::cout << "�Ͽ��ͻ��˳ɹ�" << std::endl;
		}
	}
protected:
private:
	SOCKET mServerSocket;		// �������׽��־��
	sockaddr_in mServerAddr;	// ��������ַ

	SOCKET mAcceptSocket;		// �ͻ����׽��־��
	sockaddr_in mAcceptAddr;	// ���յĿͻ��˵�ַ
};

int main()
{
	TCPServer server;
	server.run();

	return 0;
}