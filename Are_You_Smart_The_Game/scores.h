#ifndef _Scores
#define _Scores

#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include "SFML\Graphics.hpp"

class Scores {
	std::vector<std::pair<std::string, int>> score;
public:
	Scores();
	void saveScores();
	void printScores();
	void addNewScore(int letfPawns);
};


#endif // !_Scores
