#pragma once
#include<array>
#include"Position.h"
#include<memory>

class Tile;
class Piece;

class Board {

public:
	Board(std::array<std::array<std::shared_ptr<Tile>, 8>, 8>&& tiles);
	std::array<std::array<std::shared_ptr<Tile>, 8>, 8>& getTiles();
	void print();
	int getTileColor(int i, int j);
	Tile* getTile(int i, int j);
	void changePiece(Position position, Piece* piece);
private:
	std::array<std::array<std::shared_ptr<Tile>, 8>, 8> tiles_;
};