#include <iostream>
#include <string>
#include <vector>

using namespace std;


string alphabet = "qwertyuiopasdfghjklzxcvbnm_,.!():?-+=1234567890%*QWERTYUIOPASDFGHJKLZXCVBNM"s;

string key ="";

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


void FillSquare(string alphabet_copy)
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
	FillSquare(alphabet);

	return 0;
}
