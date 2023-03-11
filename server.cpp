#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma warning(disable: 4996)


using namespace std;

SOCKET Connections[100];
int Counter = 0;



void ClientHandler(int index)
{

	int msg_size;
	while (true)
	{
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < Counter; ++i)
		{
			if (i == index)
			{
				continue;
			}
			send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[i], msg, msg_size, NULL);
		}
		delete[] msg;
	}
}

int main(int argc, char* argv[])
{


	setlocale(LC_ALL, "ru");
	string _ip;
	cout << "¬веди ip" << endl;
	cin >> _ip;
	const char* ip = _ip.c_str();





	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error!" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int size_of_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(1234);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	for (int i = 0; i < 100; ++i)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);


		if (newConnection == 0)
		{
			std::cout << "Error #2" << std::endl;
		}
		else {
			std::cout << "Client connected!" << std::endl;
			string msg = "Hello:)";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}

	return 0;
}
