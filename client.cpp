#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <vector>
#pragma warning(disable: 4996)

using namespace std;


SOCKET Connection;

string name;

string key;

string alphabet = "qwertyuiopasdfghjklzxcvbnm_,.!():?-+=1234567890%*QWERTYUIOPASDFGHJKLZXCVBNM"s;

vector<string> square;



string Encrypt(string& message, string key)
{
	srand(time(NULL));

	for (char& c : message)
	{
		if (c == ' ')
		{
			c = '_';
		}
	}

	string returning_message;
	int first_index = 0;
	int second_index = 0;

	int index_of_key = 0;

	for (const char& c : message)
	{
		if (index_of_key == key.size())
		{
			index_of_key = 0;
		}

		for (int i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i] == c)
			{
				first_index = i;
			}
		}

		for (int i = 0; i < alphabet.size(); ++i)
		{
			if (square[0][i] == key[index_of_key])
			{
				second_index = i;
			}
		}


		returning_message += square[first_index][second_index];


		++index_of_key;
	}


	return returning_message;

}

string Decrypt(string& message, string key)
{


	string returning_message = "";
	int first_index = 0;
	int second_index = 0;

	int index_of_key = 0;

	for (const char& c : message)
	{
		if (index_of_key == key.size())
		{
			index_of_key = 0;
		}


		for (int i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i] == key[index_of_key])
			{
				first_index = i;
				break;
			}

		}

		for (int i = 0; i < alphabet.size(); ++i)
		{
			if (square[i][first_index] == c)
			{
				second_index = i;
			}

		}

		returning_message += alphabet[second_index];
		++index_of_key;
	}

	for (char& c : returning_message)
	{
		if (c == '_')
		{
			c = ' ';
		}
	}

	return returning_message;
}


void Fill_square(string alphabet_copy)
{
	square.push_back(alphabet_copy);

	char last_symbol = alphabet_copy[alphabet_copy.size() - 1];

	while (alphabet_copy[0] != last_symbol)
	{
		char symbol_to_shift = alphabet_copy[0];
		auto it = alphabet_copy.begin();
		alphabet_copy.erase(it);
		alphabet_copy.push_back(symbol_to_shift);
		square.push_back(alphabet_copy);
	}
}


void ClientHandler()
{
	int msg_size;


	while (true)
	{
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		string a = msg;

		std::cout << Decrypt(a, key) << std::endl;
		delete[] msg;
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "ru");

	Fill_square(alphabet);

	string _ip;
	cout << "Введи ip" << endl;
	cin >> _ip;
	const char* ip = _ip.c_str();

	cout << "введи имя" << endl;
	cin >> name;

	cout << "Введите ключ" << endl;
	cin >> key;

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


	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server" << std::endl;
		return 1;
	}
	else {
		std::cout << "Connected!" << std::endl;
	}


	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	string msg1;
	while (true)
	{
		getline(cin, msg1);
		msg1 = name + ": " + msg1;
		int msg_size = msg1.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, Encrypt(msg1, key).c_str(), msg_size, NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}