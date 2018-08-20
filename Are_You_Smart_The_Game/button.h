#ifndef _Button
#define _Button

#include "SFML\Graphics.hpp"
#include <string>

class Button {
	void setParameters();
	sf::Text text;
	sf::Font font;
	void * function;
public:
	sf::Text getText();
	Button(std::string,int,int);
	Button(std::string);
	bool intersectsWithMouse(sf::RenderWindow&);
	bool isClicked(sf::RenderWindow&);
	void setColor(sf::Color);
	void setPosition(int,int);
	sf::FloatRect getLocalBounds();
};

#endif // !_Button
