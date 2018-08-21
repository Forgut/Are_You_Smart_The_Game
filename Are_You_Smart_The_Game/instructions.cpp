#include "instructions.h"
#include <time.h>

Instructions::Instructions()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Instruction", sf::Style::Default);
	sf::Font font;
	font.loadFromFile("Arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setPosition(sf::Vector2f(10, 10));
	text.setString("Use your left mouse button to choose\na pawn.\n\nThen chose the place you want your pawn\nto land.\n\nPawn can only jump over another pawn\nin straight line on empty slot\n\nIf you missclick use right mouse button\nto unchoose pawn");

	sf::CircleShape pawn(20);
	pawn.setOutlineThickness(3);

	sf::Event event;

	bool changeAnimationState = false;

	time_t now = time(NULL);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);

		window.draw(text);
		if (!changeAnimationState) {
			for (int i = 0; i < 3; i++) {
				if (i < 2) {
					pawn.setFillColor(sf::Color(100, 0, 0, 255));
					pawn.setOutlineColor(sf::Color(60, 0, 0, 255));
					if (i == 0) {
						pawn.setFillColor(sf::Color(200, 0, 0, 255));
					}
				}
				else {
					pawn.setFillColor(sf::Color(20, 0, 0, 255));
					pawn.setOutlineColor(sf::Color(50, 50, 50, 255));
				}
				pawn.setPosition(sf::Vector2f(60 * i + 123, 300));
				window.draw(pawn);
			}
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (i < 2) {
					pawn.setFillColor(sf::Color(20, 0, 0, 255));
					pawn.setOutlineColor(sf::Color(50, 50, 50, 255));
					}
				else {
					pawn.setFillColor(sf::Color(100, 0, 0, 255));
					pawn.setOutlineColor(sf::Color(60, 0, 0, 255));
				}
				pawn.setPosition(sf::Vector2f(60 * i + 123, 300));
				window.draw(pawn);
			}
		}
		if (time(0) - now > 1) {
			changeAnimationState = !changeAnimationState;
			now = time(0);
		}

		window.display();

	}
}
