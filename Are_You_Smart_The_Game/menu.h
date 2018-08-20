#ifndef _menu
#define _menu

#include "board.h"
#include "button.h"

class Menu {
	int checkButtonActivations(Button &button,sf::RenderWindow& window);
public:
	Menu();
	void playTheGame();
	void showScores();
};


#endif // !_menu

