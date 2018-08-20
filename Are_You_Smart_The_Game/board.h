#ifndef _board
#define _board 

class Board {
	static const int size = 7;
	bool board[size][size];
	bool chosingWhereToJump;
	bool noMorePossibleMoves();
	int countPawns();
	void endingMessage();
public:
	Board();
	void printConsole();
	void runTheGame();
};

#endif // !_board

