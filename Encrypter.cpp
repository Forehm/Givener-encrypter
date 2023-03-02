#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <ctime>

using namespace std;



string alphabet = "abcdefghijklmnopqrstuvwxyz_123456789!,.?()[]{}:QWERTYUIOPASDFGHJKLZXCVBNM";


vector<string> square;

string Encrypt(string& message, const string& key)
{
	
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

	
	int number = (key.size() - 1) * 2;

	for (int i = 0; i < number; ++i)
	{
		returning_message += alphabet[rand() % 89];
	}
	
	return returning_message;

}

string Decrypt(string& message, const string& key)
{
	string new_msg = "";
	int number = (key.size() - 1) * 2;

	for (int i = 0; i < message.size() - number; ++i)
	{
		new_msg += message[i];
	}
	message = new_msg;
	
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

int main()
{
	Fill_square(alphabet);


	while (true)
	{
		cout << endl;
		cout << endl;
		cout << "print 1 to encrypt a message"s << endl;
		cout << "print 2 to decrypt the message"s << endl;
		cout << "print 3 to quit"s << endl;

		int option = 0;
		cin >> option;
		
		switch (option)
		{
		case 1:
		{
			cin.ignore();
			cout << "print your message"s << endl;
			string message = ""s;
			getline(cin, message);

			cin.ignore();
			cout << "print your keyword"s << endl;
			string key;
			cin >> key;

			cout << Encrypt(message, key);	
			
			break;
		}
		case 2:
		{
			cin.ignore();
			cout << "print your message"s << endl;
			string message = ""s;
			getline(cin, message);

			cin.ignore();
			cout << "print your keyword"s << endl;
			string key;
			cin >> key;

			cout << Decrypt(message, key) << endl;
			break;
		}
		case 3:
		{
			cout << "good bye!"s << endl;
			return 0;
			break;
		}
		default:
		{
			cout << "I don't know such an option"s << endl;
			break;
		}
		}





	}
	return 0;
}
