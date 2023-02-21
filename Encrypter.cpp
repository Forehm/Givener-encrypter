#include <iostream>
#include <string>
#include <vector>

using namespace std;



string alphabet = "abcdefghijklmnopqrstuvwxyz_";


vector<string> square =
{   {"abcdefghijklmnopqrstuvwxyz_"s}, //1
	{"bcdefghijklmnopqrstuvwxyz_a"s}, //2
	{"cdefghijklmnopqrstuvwxyz_ab"s}, //3
	{"defghijklmnopqrstuvwxyz_abc"s}, //4
	{"efghijklmnopqrstuvwxyz_abcd"s}, //5
	{"fghijklmnopqrstuvwxyz_abcde"s}, //6
	{"ghijklmnopqrstuvwxyz_abcdef"s}, //7
	{"hijklmnopqrstuvwxyz_abcdefg"s}, //8
	{"ijklmnopqrstuvwxyz_abcdefgh"s}, //9
	{"jklmnopqrstuvwxyz_abcdefghi"s}, //10
	{"klmnopqrstuvwxyz_abcdefghij"s}, //11
	{"lmnopqrstuvwxyz_abcdefghijk"s}, //12
	{"mnopqrstuvwxyz_abcdefghijkl"s}, //13
	{"nopqrstuvwxyz_abcdefghijklm"s}, //14
	{"opqrstuvwxyz_abcdefghijklmn"s}, //15
	{"pqrstuvwxyz_abcdefghijklmno"s}, //16
	{"qrstuvwxyz_abcdefghijklmnop"s}, //17
	{"rstuvwxyz_abcdefghijklmnopq"s}, //18
	{"stuvwxyz_abcdefghijklmnopqr"s}, //19
	{"tuvwxyz_abcdefghijklmnopqrs"s}, //20
	{"uvwxyz_abcdefghijklmnopqrst"s}, //21
	{"vwxyz_abcdefghijklmnopqrstu"s}, //22
	{"wxyz_abcdefghijklmnopqrstuv"s}, //23
	{"xyz_abcdefghijklmnopqrstuvw"s}, //24
	{"yz_abcdefghijklmnopqrstuvwx"s}, //25
	{"z_abcdefghijklmnopqrstuvwxy"s}, //26
	{"_abcdefghijklmnopqrstuvwxyz"s}, //27
};

string Encrypt(string& message, string key)
{
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

	return returning_message;
}


int main()
{
	setlocale(LC_ALL, "ru");

	
	

	while (true)
	{
		cout << endl;
		cout << endl;
		cout << "Чтобы зашифровать сообщение введите 1"s << endl;
		cout << "Чтобы расшифровать сообщение введите 2"s << endl;
		cout << "Чтобы выйти введите 3"s << endl;

		int option = 0;
		cin >> option;
		
		switch (option)
		{
		case 1:
		{
			cin.ignore();
			cout << "Введите сообщение"s << endl;
			string message = ""s;
			getline(cin, message);

			cin.ignore();
			cout << "Введите ключ-слово"s << endl;
			string key;
			cin >> key;

			cout << Encrypt(message, key);	
			
			break;
		}
		case 2:
		{
			cin.ignore();
			cout << "Введите сообщение"s << endl;
			string message = ""s;
			getline(cin, message);

			cin.ignore();
			cout << "Введите ключ-слово"s << endl;
			string key;
			cin >> key;

			cout << Decrypt(message, key) << endl;
			break;
		}
		case 3:
		{
			cout << "До свидания!"s << endl;
			return 0;
			break;
		}
		default:
		{
			cout << "Я не знаю такого варианта"s << endl;
			break;
		}
		}





	}
	return 0;
}
