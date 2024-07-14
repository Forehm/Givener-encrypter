#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


string Encrypt(string message, const string key, const vector<string>& square, const string& alphabet)
{
	srand(time(NULL));

	for (char& c : message)
	{
		if (c == ' ')
		{
			c = '_';
		}
	}

	std::string returning_message = "";
	int first_index = 0;
	int second_index = 0;
	int index_of_key = 0;

	for (const char& c : message)
	{
		if (index_of_key == key.size())
		{
			index_of_key = 0;
		}

		for (size_t i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i] == c)
			{
				first_index = i;
			}
		}

		for (size_t i = 0; i < alphabet.size(); ++i)
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

string Decrypt(string& message, const string& key, const vector<string>& square, const string& alphabet)
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


		for (size_t i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i] == key[index_of_key])
			{
				first_index = i;
				break;
			}

		}

		for (size_t i = 0; i < alphabet.size(); ++i)
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


void FillSquare(string alphabet_copy, vector<string>& square)
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
	string alphabet = "qwertyuiopasdfghjklzxcvbnm_,.!():?-+=1234567890%*QWERTYUIOPASDFGHJKLZXCVBNM"s;
	string key = ""s;
	vector<string> square;
	string message;

	FillSquare(alphabet, square);//to start working, it is necessary to fill your alphaber square

	std::cout << "write your key: "s << std::endl;
	getline(std::cin, key);

	while (true)
	{
		int choice = 0;

		std::cout << "1 - decrypt"s << std::endl;
		std::cout << "2 - encrypt"s << std::endl;
		std::cout << "3 - change key"s << std::endl;
		std::cout << "-1 - exit"s << std::endl;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cin.ignore();
			getline(std::cin, message);
			std::cout << Decrypt(message, key, square, alphabet) << std::endl;
			break;
		}
		case 2:
		{
			cin.ignore();
			getline(std::cin, message);
			std::cout << Encrypt(message, key, square, alphabet) << std::endl;
			break;
		}
		case 3:
		{
			std::cout << "write new key: "s;
			cin >> key;
			break;
		}
		case -1:
		{
			std::cout << "good bye)"s << std::endl;
			return 0;
		}
		}
	}

	return 0;
}
