#include "Game.h"
#include <ctime>
Game::Game()
{
	wordCount = hintCount = 0;
	failCount = 0;
	wordLimit = hintLimit = failLimit = 0;
	wordBank.clear();
	playingWord = Word();
	finish = true;
}

Game::~Game()
{
}

int Game::getFailLimit()
{
	return failLimit;
}

void Game::setFailLimit()
{
	string userInput;
	bool flag;
	do {
		flag = false;
		cout << "Input the limit for failure: ";
		getline(cin, userInput);
		if (userInput == "") { flag = true; }
		else {
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] < 48 || userInput[i] > 57) { flag = true; break; }
			}
		}
	} while (flag);
	failLimit = stoi(userInput);
	cout << "Successfully setting Failure Limit!" << endl;
}

int Game::getHintLimit()
{
	return hintLimit;
}

void Game::setHintLimit()
{
	string userInput;
	bool flag;
	do {
		flag = false;
		cout << "Input the limit for hint: ";
		getline(cin, userInput);
		if (userInput == "") { flag = true; }
		else {
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] < 48 || userInput[i] > 57) { flag = true; break; }
			}
		}
		if (!flag) if (stoi(userInput) < 0) { flag = true; }
	} while (flag);
	hintLimit = stoi(userInput);
	cout << "Successfully setting Hint Limit!" << endl;
}

int Game::getWordLimit()
{
	return wordLimit;
}

void Game::setWordLimit()
{
	string userInput;
	bool flag;
	do {
		flag = false;
		cout << "Input the limit for word: ";
		getline(cin, userInput);
		if (userInput == "") { flag = true; }
		else {
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] < 48 || userInput[i] > 57) { flag = true; break; }
			}
		}
		if (!flag) if (stoi(userInput) < 0 || stoi(userInput) >= wordBank.size()) { flag = true; }
	} while (flag);
	wordLimit = stoi(userInput);
	cout << "Successfully setting Word Limit!" << endl;
}

void Game::addWord()
{
	cout << "Enter word: ";
	string newWord;
	getline(cin, newWord);
	Word word = Word(newWord);
	wordBank.push_back(word);
	cout << "Successfully adding Word!" << endl;
}

void Game::resetWordBank()
{
	wordBank.clear();
	cout << "Successfully resetting Wordbank!" << endl;
}

void Game::shufferWordBank()
{
	srand((unsigned int)(time(NULL)));
	int count = 0;
	while (true) {
		int idx1 = rand() % wordBank.size();
		int idx2 = rand() % wordBank.size();
		if (idx1 == idx2)
			continue;
		Word tmp = wordBank[idx1];
		wordBank[idx1] = wordBank[idx2];
		wordBank[idx2] = tmp;
		count++;
		if (count > 10) break;
	}
}

Word Game::getOneWord(int index)
{
	return wordBank[index];
}

int Game::preGame()
{
	if (wordCount == wordLimit && finish == true) {
		cout << "No more words to play." << endl;
		wordCount = 0;
		return -2;
	}
	if (finish) {
		if(wordCount == 0) this->shufferWordBank();
		playingWord = this->getOneWord(wordCount);
		playingWord.displayWord();
		wordCount++;
		finish = false;
		failCount = 0;
		hintCount = 0;
	}
	return -1;
}

void Game::guessingWord()
{
	bool guess = true;
	cout << "Enter a character: ";
	char chr;
	cin >> chr;
	cin.ignore(INT_MAX, '\n');
	guess = playingWord.checkGuess(chr);
	if (guess == false) failCount++;
	if (failCount == failLimit) {
		cout << "Game Over" << endl;
		cout << "---Next Word---" << endl;
		finish = true;
	}
	string displayText = playingWord.getDisplayText();
	string text = playingWord.getText();
	if (text == displayText) finish = true;
}

void Game::showHint()
{
	if (hintCount == hintLimit) {
		cout << "You have no more hints!" << endl;
		string displayText = playingWord.getDisplayText();
		for (int i = 0; i < displayText.length(); i++) {
			cout << displayText[i] << " ";
		}
		cout << endl;
		return;
	}
	string displayText = playingWord.getDisplayText();
	int count = 0;
	vector<int> unknowChrPos;
	for (int i = 0; i < displayText.length(); i++) {
		if (displayText[i] == '_') {
			unknowChrPos.push_back(i);
			count++;
		}
	}
	string text = playingWord.getText();
	srand((unsigned int)(time(NULL)));
	char hint = text[unknowChrPos[rand() % count]];
	finish = playingWord.setDisplayText(hint);
	hintCount++;
	displayText = playingWord.getDisplayText();
	for (int i = 0; i < displayText.length(); i++) {
		cout << displayText[i] << " ";
	}
	cout << endl;
	if (displayText == text) {
		cout << "---Congratulations---" << endl;
		finish = true;
	}
	else finish = false;
}


void Game::resetGame()
{
	for (int i = 0; i < wordBank.size(); i++) {
		wordBank[i].resetDisplayText();
	}
	this->shufferWordBank();
	finish = true;
	failCount = 0;
	hintCount = 0;
	wordCount = 0;
}
