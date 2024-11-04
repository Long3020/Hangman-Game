#include <iostream>
#include "Menu.h"
#include "Game.h"
using namespace std;

enum ACTIONTYPE {
	PLAY_GAME,
	EXIT_GAME,
	HINT_SETTING,
	FAIL_SETTING,
	WORD_SETTING,
	ADD_WORD,
	RESET_WORD,
	GUESS_WORD,
	SHOW_HINT
};


int main() {
	Menu* mainMenu = new Menu("Main Menu");
	Menu* settingMenu = new Menu("Game Settings Menu");
	Menu* wordBankMenu = new Menu("Word Bank Menu");
	Menu* playMenu = new Menu("Play Game", PLAY_GAME);
	Menu* exitMenu = new Menu("Exit Game", EXIT_GAME);
	mainMenu->addSubMenu(settingMenu);
	mainMenu->addSubMenu(wordBankMenu);
	mainMenu->addSubMenu(playMenu);
	mainMenu->addSubMenu(exitMenu);

	Menu* setHint = new Menu("Hint Settings", HINT_SETTING);
	Menu* setFail = new Menu("Fail Settings", FAIL_SETTING);
	Menu* setWord = new Menu("Word Settings", WORD_SETTING);
	settingMenu->addSubMenu(setHint);
	settingMenu->addSubMenu(setFail);
	settingMenu->addSubMenu(setWord);
	settingMenu->addSubMenu(mainMenu);

	Menu* addWord = new Menu("Add Word", ADD_WORD);
	Menu* resetWord = new Menu("Reset Word", RESET_WORD);
	wordBankMenu->addSubMenu(addWord);
	wordBankMenu->addSubMenu(resetWord);
	wordBankMenu->addSubMenu(mainMenu);

	Menu* guessWord = new Menu("Guess Word", GUESS_WORD);
	Menu* showHint = new Menu("Show Hint", SHOW_HINT);
	playMenu->addSubMenu(guessWord);
	playMenu->addSubMenu(showHint);
	playMenu->addSubMenu(mainMenu);

	Menu* currentMenu = mainMenu;
	Game* currentGame = new Game();

	currentMenu->displayMenu();
	int opt = currentMenu->promptOption();
	currentMenu = currentMenu->getSubMenu(opt);

	int finish = 0;

	while (true) {
		switch (currentMenu->getAction()) {
		case -1:
			if (finish == -1) currentGame->resetGame();
			currentMenu->displayMenu();
			opt = currentMenu->promptOption();
			currentMenu = currentMenu->getSubMenu(opt);
			break;
		case FAIL_SETTING:
			currentGame->setFailLimit();
			currentMenu = settingMenu;
			break;
		case HINT_SETTING:
			currentGame->setHintLimit();
			currentMenu = settingMenu;
			break;
		case WORD_SETTING:
			currentGame->setWordLimit();
			currentMenu = settingMenu;
			break;
		case ADD_WORD:
			currentGame->addWord();
			currentMenu = wordBankMenu;
			break;
		case RESET_WORD:
			currentGame->resetWordBank();
			currentMenu = wordBankMenu;
			break;
		case PLAY_GAME:
			finish = currentGame->preGame();
			if (finish == -2) {
				currentMenu = mainMenu;
				currentGame->resetGame();
			}
			else {
				currentMenu->displayMenu();
				opt = currentMenu->promptOption();
				currentMenu = currentMenu->getSubMenu(opt);
			}
			break;
		case GUESS_WORD:
			currentGame->guessingWord();
			currentMenu = playMenu;
			break;
		case SHOW_HINT:
			currentGame->showHint();
			currentMenu = playMenu;
			break;
		case EXIT_GAME:
			delete mainMenu;
			delete currentGame;
			exit(0);
		}
	}
	return 0;
}