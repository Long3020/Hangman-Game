#pragma once
#include <iostream>
#include<vector>
#include "Word.h"
using namespace std;

class Game
{
private:
	int failCount, hintCount, wordCount;
	int failLimit, hintLimit, wordLimit;
	vector<Word> wordBank;
	Word playingWord;
	bool finish;
public:
	Game();
	~Game();
	int getFailLimit();
	void setFailLimit();

	int getHintLimit();
	void setHintLimit();

	int getWordLimit();
	void setWordLimit();

	void addWord();
	void resetWordBank();
	void shufferWordBank();
	Word getOneWord(int index);

	int preGame();
	void guessingWord();
	void showHint();

	void resetGame();
};

