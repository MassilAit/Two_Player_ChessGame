#pragma once
#include<memory>
#include"Board.h"
#include"Player.h"
#include<map>
#include<vector>


class Game {
public:
	Game();
	void launch();
	void print();
	void nextRound();
	void play(Tile* tile, int i, int j);
	std::vector<Position> nextMove(Tile* tile);
	bool selectTile(int& i, int& j);
	bool getPositon(int& i, int& j, std::string position);
	bool checkIfIn(int i, int j, std::vector<Position> positions);
	bool checkIfCheck(bool isWhite);
	bool isPossibleMove(Tile* tile, Position position);
	bool isGameFinished();
private:
	std::unique_ptr<Board> board_;
	std::unique_ptr<Player> whitePlayer_;
	std::unique_ptr<Player> blackPlayer_;
	bool isWhiteTurn_ = true;
	bool isGameFinished_=false;
	std::map<char, int> map_j={{'a',0},{'b',1},{'c',2}, {'d',3},{'e',4},{'f',5},{'g',6},{'h',7}};
	std::map<char, int> map_i = { {'8',0},{'7',1},{'6',2}, {'5',3},{'4',4},{'3',5},{'2',6},{'1',7} };


};