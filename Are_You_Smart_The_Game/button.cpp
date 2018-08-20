#include "button.h"

void Button::setParameters() {
	font.loadFromFile("arial.ttf");
	this->text.setFont(font);
	this->text.setCharacterSize(30);
	this->text.setColor(sf::Color::White);
}


sf::Text Button::getText()
{
	return this->text;
}

Button::Button(std::string text, int x, int y) {
	setParameters();
	this->text.setString(text);
	this->text.setPosition(sf::Vector2f(x, y));
}

Button::Button(std::string text) {
	setParameters();
	this->text.setString(text);
}

bool Button::intersectsWithMouse(sf::RenderWindow& window)
{
	int x = sf::Mouse::getPosition(window).x,
		y = sf::Mouse::getPosition(window).y;
	if (x > text.getPosition().x && x < text.getPosition().x + text.getLocalBounds().width &&
		y > text.getPosition().y && y < text.getPosition().y + text.getLocalBounds().height) {
		return true;
	}
	return false;
}

bool Button::isClicked(sf::RenderWindow& window)
{
	if (intersectsWithMouse(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void Button::setColor(sf::Color color)
{
	this->text.setColor(color);
}

void Button::setPosition(int x, int y)
{
	text.setPosition(sf::Vector2f(x, y));
}

sf::FloatRect Button::getLocalBounds()
{
	return text.getLocalBounds();
}
