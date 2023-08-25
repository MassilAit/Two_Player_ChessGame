#pragma once
#include<vector>
#include<memory>
#include"Piece.h"
class Player {
public:
	Player(std::vector<std::shared_ptr<Piece>> pieces);
	std::vector<std::shared_ptr<Piece>> getPieces();
	void removePiece(Position position);
	void setKingPosition(Position position);
	Position getKingPosition();
	std::shared_ptr<Piece> findPiece(Position position);
	void addPiece(std::shared_ptr<Piece> piece) {
		pieces_.push_back(piece);
	}
	void print() {
		std::cout << "Print player pieces : \n";
		for (int i = 0; i < pieces_.size(); i++) {
			std::cout << "Name : " << pieces_[i]->getName() << "  Position : (" << pieces_[i]->getPosition().x << "," << pieces_[i]->getPosition().y << ")\n";
		}
	}

private:
	std::vector<std::shared_ptr<Piece>> pieces_;
	Position kingPosition_;
};