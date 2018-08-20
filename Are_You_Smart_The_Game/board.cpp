#include "board.h"
#include "scores.h"
#include "menu.h"
#include "SFML\Graphics.hpp"

#include <stdio.h>
#include <windows.h>


/*
this is how it looks like
		O O O
		O O O
	O O O O O O O
	O O O   O O O
	O O O O O O O
		O O O
		O O O
*/

Board::Board() {
	chosingWhereToJump = false;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = false;
	for (int i = 0; i < size; i++) {
		for (int j = 2; j < size-2; j++) {
			board[i][j] = board[j][i] = true;
		}
	}
	board[size / 2][size / 2] = false;
}

void Board::printConsole() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j]) printf("O "); else printf("  ");
		}
		printf("\n");
	}
}

bool xOR(bool a, bool b) {
	if (a == b) return false; else return true;
}

bool Board::noMorePossibleMoves() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if ((i > 1 && i < size - 2) || (j > 1 && j < size - 2)) {
				if (board[i][j]) {
					if (i > 0 && i < size - 1)
						if (xOR(board[i - 1][j], board[i + 1][j]))
							return false;
					if (j > 0 && j < size - 1)
						if (xOR(board[i][j - 1], board[i][j + 1])) 
							return false;
				}
			}
		}
	}
	return true;
}

int Board::countPawns() {
	int pawnsLeft = 0;
	for (int i=0;i<size;i++) 
		for (int j = 0; j < size; j++) {
			if (board[i][j])
				pawnsLeft++;
		}
	return pawnsLeft;
}

void Board::endingMessage()
{
	MessageBox(NULL, std::string("no more moves").c_str(), std::string("end").c_str(), MB_OK);
}

void Board::runTheGame() {
	sf::RenderWindow window(sf::VideoMode(560, 560), "Are you smart?", sf::Style::Default);
	sf::CircleShape pawn(20);
	pawn.setOutlineThickness(3);
	sf::Vector2i chosenPawnCoordinates;
	while (window.isOpen()) {
		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		} 
		if (chosingWhereToJump) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2i coordinates;
				coordinates.x = (mousePos.x - 20) / 80;
				coordinates.y = (mousePos.y - 20) / 80;
				bool xOutOfRange = false, yOutOfRange = false;
				if (coordinates.x < 2 || coordinates.x > size - 3) xOutOfRange = true;
				if (coordinates.y < 2 || coordinates.y > size - 3) yOutOfRange = true;
				if (!(xOutOfRange && yOutOfRange)) {
					if (chosenPawnCoordinates.x - coordinates.x == 2 && chosenPawnCoordinates.y - coordinates.y == 0 && board[chosenPawnCoordinates.x - 1][chosenPawnCoordinates.y] && !board[chosenPawnCoordinates.x - 2][chosenPawnCoordinates.y]) { //jumping left
						board[chosenPawnCoordinates.x][chosenPawnCoordinates.y] = false;
						board[coordinates.x][coordinates.y] = true;
						board[coordinates.x + 1][coordinates.y] = false;
						chosingWhereToJump = false;
					}
					if (chosenPawnCoordinates.x - coordinates.x == -2 && chosenPawnCoordinates.y - coordinates.y == 0 && board[chosenPawnCoordinates.x + 1][chosenPawnCoordinates.y] && !board[chosenPawnCoordinates.x + 2][chosenPawnCoordinates.y]) { //jumping right
						board[chosenPawnCoordinates.x][chosenPawnCoordinates.y] = false;
						board[coordinates.x][coordinates.y] = true;
						board[coordinates.x - 1][coordinates.y] = false;
						chosingWhereToJump = false;
					}
					if (chosenPawnCoordinates.x - coordinates.x == 0 && chosenPawnCoordinates.y - coordinates.y == 2 && board[chosenPawnCoordinates.x][chosenPawnCoordinates.y - 1] && !board[chosenPawnCoordinates.x][chosenPawnCoordinates.y - 2]) { //jumping up
						board[chosenPawnCoordinates.x][chosenPawnCoordinates.y] = false;
						board[coordinates.x][coordinates.y] = true;
						board[coordinates.x][coordinates.y + 1] = false;
						chosingWhereToJump = false;
					}
					if (chosenPawnCoordinates.x - coordinates.x == 0 && chosenPawnCoordinates.y - coordinates.y == -2 && board[chosenPawnCoordinates.x][chosenPawnCoordinates.y + 1] && !board[chosenPawnCoordinates.x][chosenPawnCoordinates.y + 2]) { //jumping down
						board[chosenPawnCoordinates.x][chosenPawnCoordinates.y] = false;
						board[coordinates.x][coordinates.y] = true;
						board[coordinates.x][coordinates.y - 1] = false;
						chosingWhereToJump = false;
					}
				}
				Sleep(100);
			
			}
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2i coordinates;
				coordinates.x = (mousePos.x - 20) / 80;
				coordinates.y = (mousePos.y - 20) / 80;
				bool xOutOfRange = false, yOutOfRange = false;
				if (coordinates.x < 2 || coordinates.x > size - 3) xOutOfRange = true;
				if (coordinates.y < 2 || coordinates.y > size - 3) yOutOfRange = true;
				if (!(xOutOfRange && yOutOfRange)) {
					if (board[coordinates.x][coordinates.y]) {
						chosingWhereToJump = true;
						chosenPawnCoordinates = coordinates;
					}
				}
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			chosingWhereToJump = false;
			chosenPawnCoordinates = sf::Vector2i();
			Sleep(100);
		}
		window.clear();
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((i > 1 && i < size - 2) || (j > 1 && j < size - 2)) {
					if (board[i][j]) {
						pawn.setFillColor(sf::Color(100,0,0,255));
						pawn.setOutlineColor(sf::Color(60, 0, 0, 255));
						if (i == chosenPawnCoordinates.x && j == chosenPawnCoordinates.y)
							pawn.setFillColor(sf::Color(200, 0, 0, 255));
					}
					else {
						pawn.setFillColor(sf::Color(20, 0, 0, 255));
						pawn.setOutlineColor(sf::Color(50,50,50,255));
					}
					pawn.setPosition(sf::Vector2f(20 + i * 80, 20 + j * 80));
					window.draw(pawn);
				}
			}
		}
		window.display();
		if (noMorePossibleMoves()) {
			endingMessage();
			Scores score;
			score.addNewScore(countPawns());
			while (true) {
				if (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}
			}
		}
	}
}

