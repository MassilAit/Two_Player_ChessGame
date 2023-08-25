#include"Board.h"
#include"Piece.h"
#include"Tile.h"



Board::Board(std::array<std::array<std::shared_ptr<Tile>, 8>, 8>&& tiles) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tiles_[i][j] = std::move(tiles[i][j]);
		}
	}
}



std::array<std::array<std::shared_ptr<Tile>, 8>, 8>& Board::getTiles() {
	return tiles_;
};

void Board::print() {
	for (int i = 0; i < 8; i++) {
		
		for (int j = 0; j < 8; j++) {
			tiles_[i][j]->print();
			std::cout << ',';
		}
		std::cout << '\n';
	}
}

int Board::getTileColor(int i, int j) {
	if (tiles_[i][j]->isTileOccupied()) {
		return tiles_[i][j]->getPiece()->getColor();
	}
	return -1;
}

Tile* Board::getTile(int i, int j) {
	return tiles_[i][j].get();
}

void Board::changePiece(Position position, Piece* piece) {
	tiles_[position.x][position.y]->setPiece(piece);
}