#include"Piece.h"
#include"Tile.h";
#include <cctype>;

Piece::Piece(Position position, bool isWhite) {
	position_ = position;
	isWhite_ = isWhite;
	isFirstMove_ = true;

}

bool Piece::addMove(std::vector<Position>& possibleMoves, Position position, Board* board) {
	
	
	if (position.x < 0 or position.x>7 or position.y < 0 or position.y>7) {
		
		return false;
	}


	Tile* tile = board->getTile(position.x, position.y);
	if (tile->isTileOccupied()) {
		if (tile->getPiece()->getColor() == isWhite_) {
			
			return false;
		}
		possibleMoves.push_back(position);
		
		return false;

	}
	
	possibleMoves.push_back(position);
	return true;


}

char Piece::getName() {
	return typeName_;
}

int Piece::getColor() {
	return int(isWhite_);
}
void Piece::setPosition(Position position) {
	position_ = position;
}

Position Piece::getPosition() {
	return position_;
}

void Piece::print() {

	if (isWhite_) {
		std::cout << char(tolower(typeName_));
	}
	else {
		std::cout << typeName_;
	}
	
}

Pawn::Pawn(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'P';
}

void Pawn::diagonal(int i, int j, std::vector<Position>& possibleMoves, Board* board, bool isWhite) {
	if (i < 0 or i>7 or j < 0 or j>7) {
		return;
	}
	
	if (!(board->getTile(i, j)->isTileOccupied())) {
		return;
	}
	isWhite = !isWhite;

	if (board->getTile(i, j)->getPiece()->getColor() == int(isWhite)) {
		possibleMoves.push_back(Position(i,j));
	}

}

std::vector<Position> Pawn::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	if (isWhite_) {
		if (isFirstMove_) {
			Position position(i - 2, j);
			if (!(board->getTile(position.x, position.y)->isTileOccupied()) and !(board->getTile(position.x+1, position.y)->isTileOccupied())) {
				possibleMoves.push_back(position);
			}	
		}
		Position position(i - 1, j);
		if (!(board->getTile(position.x, position.y)->isTileOccupied())) {
			possibleMoves.push_back(position);
		}

		diagonal(i - 1, j + 1, possibleMoves, board, isWhite_);
		diagonal(i - 1, j - 1, possibleMoves, board, isWhite_);

	}

	else {
		if (isFirstMove_) {
			Position position(i + 2, j);
			if (!(board->getTile(position.x, position.y)->isTileOccupied()) and !(board->getTile(position.x - 1, position.y)->isTileOccupied())) {
				possibleMoves.push_back(position);
			}
		}
		Position position(i + 1, j);
		if (!(board->getTile(position.x, position.y)->isTileOccupied())) {
			possibleMoves.push_back(position);
		}

		diagonal(i + 1, j + 1, possibleMoves, board, isWhite_);
		diagonal(i + 1, j - 1, possibleMoves, board, isWhite_);

	}
	return possibleMoves;
}

Queen::Queen(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'Q';
}
std::vector<Position> Queen::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	int tmp = i + 1;
	while (addMove(possibleMoves, Position(tmp, j), board)) {
		tmp += 1;
	}
	tmp = i - 1;
	while (addMove(possibleMoves, Position(tmp, j), board)) {
		tmp -= 1;
	}

	tmp = j + 1;
	while (addMove(possibleMoves, Position(i, tmp), board)) {
		tmp += 1;
	}

	tmp = j - 1;
	while (addMove(possibleMoves, Position(i, tmp), board)) {
		tmp -= 1;
	}

	int tmpi = i + 1;
	int tmpj = j + 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi++;
		tmpj++;
	}

	tmpi = i - 1;
	tmpj = j + 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi--;
		tmpj++;
	}

	tmpi = i + 1;
	tmpj = j - 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi++;
		tmpj--;
	}

	tmpi = i - 1;
	tmpj = j - 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi--;
		tmpj--;
	}
	return possibleMoves;
}

King::King(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'K';
}

std::vector<Position> King::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	addMove(possibleMoves, Position(i + 1, j), board);
	addMove(possibleMoves, Position(i - 1, j), board);
	addMove(possibleMoves, Position(i, j + 1), board);
	addMove(possibleMoves, Position(i , j - 1), board);
	addMove(possibleMoves, Position(i + 1, j + 1), board);
	addMove(possibleMoves, Position(i - 1, j + 1), board);
	addMove(possibleMoves, Position(i + 1, j - 1), board);
	addMove(possibleMoves, Position(i - 1, j - 1), board);

	return possibleMoves;
}

Rook::Rook(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'R';
}

std::vector<Position> Rook::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	int tmp = i+1;
	while (addMove(possibleMoves, Position(tmp, j), board)) {
		tmp += 1;
	}
	tmp = i-1;
	while (addMove(possibleMoves, Position(tmp, j), board)) {
		tmp -= 1;
	}

	tmp = j+1;
	while (addMove(possibleMoves, Position(i, tmp), board)) {
		tmp += 1;
	}

	tmp = j-1;
	while (addMove(possibleMoves, Position(i, tmp), board)) {
		tmp -= 1;
	}
	return possibleMoves;
}

Bishop::Bishop(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'B';
}

std::vector<Position> Bishop::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	int tmpi = i+1;
	int tmpj = j+1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi++;
		tmpj++;
	}

	tmpi = i - 1;
	tmpj = j + 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi--;
		tmpj++;
	}

	tmpi = i + 1;
	tmpj = j - 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi++;
		tmpj--;
	}

	tmpi = i - 1;
	tmpj = j - 1;
	while (addMove(possibleMoves, Position(tmpi, tmpj), board)) {
		tmpi--;
		tmpj--;
	}
	return possibleMoves;
}


Knight::Knight(Position position, bool isWhite) :
	Piece(position, isWhite) {
	typeName_ = 'N';
}

std::vector<Position> Knight::nextPossibleMoves(Board* board) {
	std::vector<Position> possibleMoves;
	int i = position_.x;
	int j = position_.y;
	addMove(possibleMoves, Position(i + 2, j+1), board);
	addMove(possibleMoves, Position(i + 2, j - 1), board);
	addMove(possibleMoves, Position(i - 2, j + 1), board);
	addMove(possibleMoves, Position(i - 2, j - 1), board);
	addMove(possibleMoves, Position(i + 1, j + 2), board);
	addMove(possibleMoves, Position(i - 1, j + 2), board);
	addMove(possibleMoves, Position(i + 1, j - 2), board);
	addMove(possibleMoves, Position(i - 1, j - 2), board);

	return possibleMoves;
}