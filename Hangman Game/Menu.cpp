#include "Menu.h"
#include <string>
using namespace std;

Menu::Menu()
{
	name = "Default Menu";
	action = -1;
	subMenu.clear();
}

Menu::Menu(string name, int action)
{
	this->name = name;
	this->action = action;
	this->subMenu.clear();
}

Menu::~Menu()
{
	if (!subMenu.empty()) {
		for (int i = 0; i < subMenu.size() - 1; i++) {
			if (subMenu[i])
				delete subMenu[i];
		}
		subMenu.clear();
	}
}

string Menu::getName()
{
	return this->name;
}

void Menu::setName(string n)
{
	this->name = n;
}

int Menu::getAction()
{
	return action;
}

void Menu::setAction(int a)
{
	this->action = a;
}

void Menu::addSubMenu(Menu* m)
{
	this->subMenu.push_back(m);
}

Menu* Menu::getSubMenu(int index)
{
	if (index > 0 && index <= subMenu.size()) {
		index--;
		return subMenu[index];
	}
	else
		return nullptr;
}

void Menu::displayMenu()
{
	cout << "=====" << this->name << "=====" << endl;
	for (int i = 0; i < subMenu.size(); i++) {
		cout << i + 1 << "." << subMenu[i]->getName() << endl;
	}
}

int Menu::promptOption()
{
	string userInput;
	bool flag;
	do {
		flag = false;
		cout << "Your option: ";
		getline(cin, userInput);
		if (userInput[0] == 48 || userInput == "") { flag = true; }
		else {
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] < 48 || userInput[i] > 57) { flag = true; break; }
			}
		}
	} while (flag || stoi(userInput) > subMenu.size());
	return stoi(userInput);
}
