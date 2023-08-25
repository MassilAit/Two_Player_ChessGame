#include"Tile.h"
#include <cstddef>


Tile::Tile(Position tileCoordinates, Piece* piece) {
	tileCoordinates_ = Position(tileCoordinates.x,tileCoordinates.y);
	piece_ = piece;
	if (piece != nullptr) {
		isTileOccupied_ = true;
	}
	
}

bool Tile::isTileOccupied() {
	return isTileOccupied_;
}
Piece* Tile::getPiece() {
	return piece_;
}

void Tile::setPiece(Piece* piece) {
	removePiece();
	piece_ = piece;
	isTileOccupied_ = true;
}

void Tile::removePiece() {
	
	if (isTileOccupied_) {
		isTileOccupied_ = false;
		piece_ = nullptr;
		
	}
}

Position Tile::getPosition() {
	return tileCoordinates_;
}