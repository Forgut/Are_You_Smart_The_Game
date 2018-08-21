#include "menu.h"
#include "button.h"
#include "scores.h"
#include "instructions.h"
#include <SFML\Graphics.hpp>	

int Menu::checkButtonActivations(Button &button,sf::RenderWindow& window)
{
	if (button.isClicked(window)) {
		window.close();
		return 2;
	}
	if (button.intersectsWithMouse(window)) {
		button.setColor(sf::Color::Red);
		return 1;
	}
	else {
		button.setColor(sf::Color::White);
	}
	return 0;
}

void Menu::playTheGame()
{
	Board board;
	board.runTheGame();
	Menu menu;
}

void Menu::showScores() {
	Scores scores;
	scores.printScores();
	Menu menu;
}

void Menu::showTutorial() {
	Instructions instructions;
	Menu menu;
}



Menu::Menu()
{
	const int winWidth = 400, winHight = 400;
	sf::RenderWindow window(sf::VideoMode(winWidth, winHight), "Are you smart?", sf::Style::Default);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		printf("error while uploading font, check your files");
	}
	sf::Text Menu;
	Menu.setFont(font);
	Menu.setCharacterSize(40);
	Menu.setColor(sf::Color::White);
	sf::Event event;
	Button play("Play");
	play.setPosition(winWidth / 2 - play.getLocalBounds().width / 2,winHight*3/10);
	Button scores("Scores");
	scores.setPosition(winWidth / 2 - scores.getLocalBounds().width / 2, winHight * 4 / 10);
	Button quit("Quit");
	quit.setPosition(winWidth / 2 - quit.getLocalBounds().width / 2, winHight * 6 / 10);
	Button tutorial("Tutorial");
	tutorial.setPosition(winWidth / 2 - tutorial.getLocalBounds().width / 2, winHight * 5 / 10);

	while (window.isOpen()) {
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		Menu.setPosition(sf::Vector2f(winWidth/2- Menu.getLocalBounds().width/2 ,winHight/20));
		Menu.setString("Main menu");
		if (checkButtonActivations(play, window) == 2)
			playTheGame();
		if (checkButtonActivations(scores, window) == 2)
			showScores();
		if (checkButtonActivations(tutorial, window) == 2)
			showTutorial();
		if (checkButtonActivations(quit, window) == 2)
			break; //quit the game

		window.draw(Menu);
		window.draw(play.getText());
		window.draw(scores.getText());
		window.draw(quit.getText());
		window.draw(tutorial.getText());
		window.display();
	}
}
