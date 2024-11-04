#pragma once
#include <iostream>
#include <string>
using namespace std;
class Word
{
private:
	string text;
	string displayText;
public:
	Word();
	Word(string text);
	~Word();

	string getText();

	string getDisplayText();
	bool setDisplayText(char hint);

	bool checkGuess(char n);
	void displayWord();

	void resetDisplayText();
};

