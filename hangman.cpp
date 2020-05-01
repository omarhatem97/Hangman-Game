#include <cstdio>
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

bool is_in_word(string secretword,char c)
{
	// checks if the guessed char is in the secret word

	int counter =0;
	for (char c1 : secretword)
	{
		if (c1 == c)
		{
			return true;
			break;
		}
		else counter++;
	}
	if (counter == secretword.size()) return false;
}


bool isWordGuessed(string secretWord, string lettersGuessed)
{
	// check if the letters guessed are the secret word

	int counter = 0;
	for (char c : lettersGuessed)
	{
		for (char l : secretWord)
		{
			if (c == l) counter++;	
		}
	}
	if (counter == secretWord.size()) return true;
	else return false;
}



string getGuessedWord(string secretWord, char c ,  string temp)
{
	string copy = temp;
	if (is_in_word(secretWord,c))
	{
		for (int i = 0; i < secretWord.size(); i++)
		{
			if (c == secretWord[i])
			{
				if (i == 0)
				{
					copy[i] = c;
				}
				else
				{
					copy[(i*2)] = c;
				}
			}
		}

	}

	
	return copy;
}


string getAvailableLetters(string letterguessed)
{
	static string alpha = "abcdefghijklmnopqrstubwxyz";

	alpha.erase(std::remove(alpha.begin(), alpha.end(), letterguessed[letterguessed.size()-1]), alpha.end());
	
	return alpha;
}


string newstring(string s)
{
	string s2 = "";
	for (int i = 2; i < s.size(); i+=2)
	{
		if (s[i] != '_' )
		{
			s[i - 1] = s[i];
			s[i] = '0';
		}
	}

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != '0')
		{
			s2 += s[i];
		}
	}
	return s2;
}










int main()
{
//Reading words and generates random one

	vector <string> rand_selec = {};  // takes words from txt file and put it in a string vector
	ifstream infile;
	string word;     // random word which computer chooses
	infile.open("D:\\words.txt");

	if (infile.fail())
	{
		cout << "your file didn't open\n";
	}
	else
	{
		string s;
		while (infile >> s)
		{
			rand_selec.push_back(s);
		}
	}
	cout << "The num of words : " << rand_selec.size() << endl;

	srand(time(0));
	word = rand_selec[ rand()% rand_selec.size()];
//	cout <<"the word is: "<< word << endl;          // only can be aproved by the developer
	infile.close();
	infile.clear();
//------- word has been randomly picked--------------------------------------------

	int guess = 8;
	string lettersGuessed = " ";
	string current_word = ""; // current achieve ex : a_ple
	static string temp = "";
	string temp2;
	char c = ' '; // the guess that the gamer every time makes
	cout << "Welcome to the game, Hangman!" << endl;
	cout << "I am thinking of a word that is " << word.size() << " letters long." << endl;
	cout << "---------------------------------------------" << endl;

	for (int i = 0; i < word.size(); i++)
	{
		if (i == word.size() - 1)
		{
			temp += "_";
		}
		else
		{
			temp += "_ ";
		}

	} // end for

	
	
	while (guess)
	{
//		cout << "Temp now equal : " << temp << "\n\n";
		cout << "You have " << guess << " left." << endl;
		cout << "Available Letters: " <<getAvailableLetters(lettersGuessed)<< endl;
		cout << "Please guess a letter : " << endl;
		goto target;  // make sure that the gamer doesn't enter an already guessed letter
	target:
		cin >> c;

		for (char car : lettersGuessed)
		{
			if (c == car)
			{
				cout << "You have already guessed this letter , guess another letter! -_- : ";
				goto target;
			}
		}

		lettersGuessed += c;
//		cout << "now letters guessed are :" << lettersGuessed << endl; //for debugging
		if ( is_in_word (word , c))
		{
			temp2 = getGuessedWord(word, c, temp); // assigns the value of cureent guessed string to a temp string
			cout << "Good guess: " << newstring(temp2) << endl;
			cout << "-----------" << endl;
			temp = getGuessedWord(word, c, temp);

			if (isWordGuessed(word, lettersGuessed))
			{
				cout << "Congratulations, you won!" << endl;
				break;
			}

		}
		else
		{
			guess--;
			temp2 = getGuessedWord(word, c, temp);
			cout << "Oops! That letter is not in my word: " << newstring(temp2) << endl;
			temp = getGuessedWord(word, c, temp);
			cout << "-----------" << endl;

		}
	}

	if (!isWordGuessed(word, lettersGuessed))
	{
		cout << "Sorry, you ran out of guesses. The word was " << word << "." << endl;
	}

	return 0;
}


