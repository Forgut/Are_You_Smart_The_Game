#include "scores.h"
#include <windows.h>

Scores::Scores()
{
	std::ifstream file;
	file.open("scores.txt");
	std::string first;
	int second;
	while (file >> first >> second) {
		score.push_back(std::pair<std::string, int>(first, second));
	}
	file.close();
}

void Scores::saveScores()
{
	std::ofstream file("scores.txt");
	for (auto pair : score) {
		file << pair.first;
		file << " ";
		file << pair.second;
		file << std::endl;
	}
	file.close();
}

void Scores::printScores() {
	sf::RenderWindow window(sf::VideoMode(400, 400), "Scores", sf::Style::Default);
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::White);
	text.setCharacterSize(30);



	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		text.setString("Score Table");
		text.setPosition(sf::Vector2f(200 - text.getLocalBounds().width / 2,0));
		int height = text.getLocalBounds().height+10;
		window.draw(text);
		for (auto pair : score) {
			text.setString(pair.first + "    " + std::to_string(pair.second));
			text.setPosition(sf::Vector2f(0, height));
			window.draw(text);
			height += text.getLocalBounds().height + 10;
		}
		window.display();
	}
}

bool wayToSort(std::pair<std::string, int> a, std::pair<std::string, int> b) {
	return a.second < b.second;
}

void Scores::addNewScore(int letfPawns)
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	std::string date;
	date = std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + "-" + std::to_string(st.wDay) + "/" + std::to_string(st.wMonth) + "/" + std::to_string(st.wYear);
	score.push_back(std::pair<std::string, int>(date, letfPawns));
	std::sort(score.begin(), score.end(),wayToSort);
	if (score.size() > 10)
		score.resize(10);
	saveScores();
}
