#pragma once
#include<vector>
#include<iostream>
#include"Position.h"
#include"Board.h"
#include <windows.h>  



class Piece {
protected:
	char typeName_ = NULL;
	bool isWhite_;
	Position position_;
	bool isFirstMove_;
	bool addMove(std::vector<Position>& possibleMoves,Position position, Board* board);
public:
	Piece(Position position, bool isWhite);
	char getName();
	int getColor();
	void setPosition(Position position);
	void move() {
		isFirstMove_ = false;
	}
	bool getIsFirstMove() {
		return isFirstMove_;
	}

	void setisFirstMove(bool isFirstMove) {
		isFirstMove_ = isFirstMove;
	}
	Position getPosition();
	void print();
	virtual std::vector<Position> nextPossibleMoves(Board* board )=0;
};

class Pawn : public Piece {
public:
	Pawn(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
	void diagonal(int i, int j, std::vector<Position>& possibleMoves, Board* board, bool isWhite);
};

class Rook : public Piece {
public:
	Rook(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
};

class Bishop :public Piece {
public:
	Bishop(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
};

class Knight :public Piece {
public:
	Knight(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
};

class Queen :public Piece {
public:
	Queen(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
};

class King :public Piece {
public:
	King(Position position, bool isWhite);
	std::vector<Position> nextPossibleMoves(Board* board) override;
};