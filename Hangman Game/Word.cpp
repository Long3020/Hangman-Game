#include "Word.h"
#include <ctime>

Word::Word()
{
	text = "";
	displayText = "";
}

Word::Word(string text)
{
	this->text = text;
	displayText = text;
	for (int i = 0; i < text.length(); i++) {
		displayText[i] = '_';
	}
}

Word::~Word(){}

string Word::getText()
{
	return text;
}

string Word::getDisplayText()
{
	return displayText;
}

bool Word::setDisplayText(char hint)
{
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == hint) displayText[i] = hint;
	}
	int finish = 0;
	for (int i = 0; i < displayText.length(); i++) {
		if (displayText[i] == '_') finish++;
	}
	if (finish == 0) {
		cout << "---Next Word---" << endl;
		return true;
	}
	else return false;
}

bool Word::checkGuess(char n)
{
	int occurence = 0;
	for (int i = 0; i < text.length(); i++) {
		if (text[i] == n) {
			occurence++;
			displayText[i] = n;
		}
	}
	if (occurence == 1) cout << "There is " << occurence << " " << n << " in this word." << endl;
	else cout << "There are " << occurence << " " << n << " in this word." << endl;
	for (int i = 0; i < displayText.length(); i++) {
		cout << displayText[i] << " ";
	}
	cout << endl;
	if (displayText == text) {
		cout << "---Congratulations---" << endl;
		cout << "---Next Word---" << endl;
	}
	if (occurence == 0) return false;
	else return true;
}

void Word::displayWord()
{
	cout << "The word has total " << text.length() << " characters!" << endl;
	for (int i = 0; i < displayText.length(); i++) {
		cout << displayText[i] << " ";
	}
	cout << endl;
}

void Word::resetDisplayText()
{
	for (int i = 0; i < displayText.length(); i++) {
		displayText[i] = '_';
	}
}
