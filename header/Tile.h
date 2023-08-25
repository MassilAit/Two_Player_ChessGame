#pragma once
#include<iostream>
#include"Piece.h"
#include"Position.h"



class Tile {
public:
	Tile(Position tileCoordinates, Piece* piece_ = nullptr);
	void print() {
		if (isTileOccupied_) {
			piece_->print();
			return;
		}

		std::cout << '0';
	}
	void setPiece(Piece* piece);
	bool isTileOccupied();
	void removePiece();
	Piece* getPiece();
	Position getPosition();


	

private:
	Position tileCoordinates_;
	bool isTileOccupied_=false;
	Piece* piece_=nullptr;

};
