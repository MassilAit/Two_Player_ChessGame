#include"Game.h"
#include"Tile.h"
#include<array>
#include<string>

Game::Game() {


	//Creating black pieces at the right position:
	std::vector<std::shared_ptr<Piece>> Blackpieces;
	Blackpieces.push_back(std::make_shared<Rook>(Rook(Position(0, 0), false)));
	Blackpieces.push_back(std::make_shared<Knight>(Knight(Position(0, 1), false)));
	Blackpieces.push_back(std::make_shared<Bishop>(Bishop(Position(0, 2), false)));
	Blackpieces.push_back(std::make_shared<Queen>(Queen(Position(0, 3), false)));
	Blackpieces.push_back(std::make_shared<King>(King(Position(0, 4), false)));
	Blackpieces.push_back(std::make_shared<Bishop>(Bishop(Position(0, 5), false)));
	Blackpieces.push_back(std::make_shared<Knight>(Knight(Position(0, 6), false)));
	Blackpieces.push_back(std::make_shared<Rook>(Rook(Position(0, 7), false)));

	for (int i = 0; i < 8; i++) {
		Blackpieces.push_back(std::make_shared<Pawn>(Pawn(Position(1, i), false)));
	}

	blackPlayer_ = std::make_unique<Player>(Player(Blackpieces));

	//Creating white pieces at the right position:
	std::vector<std::shared_ptr<Piece>> whitePieces;

	for (int i = 0; i < 8; i++) {
		whitePieces.push_back(std::make_shared<Pawn>(Pawn(Position(6, i), true)));
	}

	whitePieces.push_back(std::make_shared<Rook>(Rook(Position(7, 0), true)));
	whitePieces.push_back(std::make_shared<Knight>(Knight(Position(7, 1), true)));
	whitePieces.push_back(std::make_shared<Bishop>(Bishop(Position(7, 2), true)));
	whitePieces.push_back(std::make_shared<Queen>(Queen(Position(7, 3), true)));
	whitePieces.push_back(std::make_shared<King>(King(Position(7, 4), true)));
	whitePieces.push_back(std::make_shared<Bishop>(Bishop(Position(7, 5), true)));
	whitePieces.push_back(std::make_shared<Knight>(Knight(Position(7, 6), true)));
	whitePieces.push_back(std::make_shared<Rook>(Rook(Position(7, 7), true)));


	whitePlayer_ = std::make_unique<Player>(Player(whitePieces));


	//initializing tiles
	std::array<std::array<std::shared_ptr<Tile>, 8>, 8> tiles;

	for (int i = 0; i < 8; i++) {
		tiles[0][i] = std::make_shared<Tile>(Tile(Position(0, i), blackPlayer_->getPieces()[i].get()));
	}
	for (int i = 0; i < 8; i++) {
		tiles[1][i] = std::make_shared<Tile>(Tile(Position(1, i), blackPlayer_->getPieces()[i + 8].get()));
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			tiles[i][j] = std::make_shared<Tile>(Tile(Position(i, j)));
		}
	}

	for (int i = 0; i < 8; i++) {
		tiles[6][i] = std::make_shared<Tile>(Tile(Position(6, i), whitePlayer_->getPieces()[i].get()));
	}
	for (int i = 0; i < 8; i++) {
		tiles[7][i] = std::make_shared<Tile>(Tile(Position(7, i), whitePlayer_->getPieces()[i + 8].get()));
	}


	board_ = std::make_unique<Board>(Board(move(tiles)));
	
}
std::string getPosition(Position position) {
	std::map<int, std::string> map_j = { {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"}, {5, "f"}, {6, "g"}, {7, "h"} };
	std::map<int, std::string> map_i = { {0, "8"}, {1, "7"}, {2, "6"}, {3, "5"}, {4, "4"}, {5, "3"}, {6, "2"}, {7, "1"} };
	return map_j[position.y] + map_i[position.x];
}


void Game::print() {
	std::cout << "\n\t      a b c d e f g h\n\n";
	for (int i = 0; i < 8; i++) {
		std::cout << "\t   "<<8 - i << "  ";
		for (int j = 0; j < 8; j++) {
			board_->getTiles()[i][j]->print();
			std::cout << ' ';
		}
		std::cout << "  " << 8 - i ;
		std::cout << '\n';
	};
	std::cout << "\n \t     a b c d e f g h\n\n";
	
}


void Game::launch() {
	std::cout << "Welcome do this modest chess game, you can enter your next move in the terminal\n";
	while (!isGameFinished_) {
		nextRound();
		isGameFinished_ = isGameFinished();
	}
	std::cout << "CheckMate : Thannk you for playing\n";
}

bool Game::getPositon(int& i, int& j, std::string position) {
	if (map_j.find(position[0]) != map_j.end() and map_i.find(position[1]) != map_i.end()) {
		j = map_j[position[0]];
		i = map_i[position[1]];
		return true;
	}
	
	return false;
}



void Game::nextRound() {

	
	if (isWhiteTurn_) {
		std::cout << "\t----------------------------\n";
		std::cout << "\t| It's WHITE turn to play |\n";
		std::cout << "\t----------------------------\n";
	}
	else  {
		std::cout << "\t----------------------------\n";
		std::cout << "\t| It's BLACK turn to play |\n";
		std::cout << "\t----------------------------\n";
	}

	print();
	
	bool asNotPlayed = true;
	int i, j;
	while (asNotPlayed) {
		bool listening = selectTile(i, j);
		while (listening) {
			listening = selectTile(i, j);
		}
		Tile* tile = board_->getTile(i, j);
		auto possibleMoves=nextMove(tile);
		std::cout << "Your possible moves are : \n";
		for (int i = 0; i < possibleMoves.size(); i++) {
			std::cout << getPosition(possibleMoves[i]) << "\n";
		}
		std::cout << "Please enter the position you want to go to : ";
		std::string nextMove;
		std::cin >> nextMove;
		if (getPositon(i, j, nextMove)) { 
			if (checkIfIn(i, j, possibleMoves)) {
				play(tile, i, j);
					asNotPlayed = false;
					break;
			}

		}
		
		std::cout << "Please select a correct tile\n";

	}

	isWhiteTurn_ = !isWhiteTurn_;
	
}


void Game::play(Tile* tile, int i, int j) {
	auto piece = tile->getPiece();
	piece->move();
	piece->setPosition(Position(i, j));
	tile->removePiece();
	if (piece->getName() == 'K') {
		if (piece->getColor()) {
			whitePlayer_->setKingPosition(Position(i,j));
		}

		else {
			blackPlayer_->setKingPosition(Position(i, j));
		}
	}
	board_->changePiece(Position(i, j), piece);
	if (isWhiteTurn_) {
		blackPlayer_->removePiece(Position(i, j));
	}
	else {
		whitePlayer_->removePiece(Position(i, j));
	} 
 

}

bool Game::selectTile(int& i, int& j) {
	std::string startingPiece;
	std::cout << "Please enter the position of the piece you want to move next : ";
	std::cin >> startingPiece;
	if (getPositon(i, j, startingPiece)) {


		if (board_->getTileColor(i, j) == isWhiteTurn_) {
			return false;
		}

		std::cout << "You have no pieces on that position \n";
		return true;
			
	}
	 std::cout << "Enter a valid position \n";
	 return true;

}





std::vector<Position> Game::nextMove(Tile* tile) {

	std::vector<Position> possibleMoves = tile->getPiece()->nextPossibleMoves(board_.get());
	auto it = possibleMoves.begin();
	while (it != possibleMoves.end())
	{
		if (isPossibleMove(tile,*it))
		{
			it = possibleMoves.erase(it);
		}
		else {
			++it;
		}
	}
	
	return possibleMoves;
	
	

}

bool Game::checkIfIn(int i, int j, std::vector<Position> positions) {
	for (int k = 0; k < positions.size(); k++) {
		if (positions[k].x == i and positions[k].y == j) {
			return true;
		}
	}

	return false;
}

bool Game::checkIfCheck(bool isWhite) {
	std::vector<std::shared_ptr<Piece>> pieces;
	Position kingPos;
	if (isWhite) {
		pieces=blackPlayer_->getPieces();
		kingPos = whitePlayer_->getKingPosition();

	}

	else {
		pieces = whitePlayer_->getPieces();
		kingPos = blackPlayer_->getKingPosition();
	}
	

	for (int i = 0; i < pieces.size(); i++) {
		auto possibleMoves = pieces[i]->nextPossibleMoves(board_.get());
		for (int j = 0; j < possibleMoves.size(); j++) {
			if (possibleMoves[j].x == kingPos.x and possibleMoves[j].y == kingPos.y) {
				return true;
			}
		}
	}

	
	return false;
}

bool Game::isPossibleMove(Tile* tile, Position position) {
	bool isPossibleMove;
	bool isFirstMove = tile->getPiece()->getIsFirstMove();
	Position initialPos = tile->getPiece()->getPosition();
	std::shared_ptr<Piece> finalPiece;
	bool x;
	Position KingPos = blackPlayer_->getKingPosition();
	if (isWhiteTurn_) {
		 KingPos = whitePlayer_->getKingPosition();
	}

	if (x=board_->getTile(position.x, position.y)->isTileOccupied()) {
		if (isWhiteTurn_) {
			finalPiece = blackPlayer_->findPiece(position);
		}
		else {
			finalPiece = whitePlayer_->findPiece(position);
		}
		
	}
	
	play(tile, position.x,position.y);
	isPossibleMove = checkIfCheck(isWhiteTurn_);

	auto piece = board_->getTile(position.x, position.y)->getPiece();
	piece->setPosition(initialPos);
	piece->setisFirstMove(isFirstMove);

	board_->changePiece(initialPos, piece);
	if(x){
		board_->changePiece(position, finalPiece.get());
		if (isWhiteTurn_) {
			blackPlayer_->addPiece(finalPiece);
		}
		else {
			whitePlayer_->addPiece(finalPiece);
		}
	}
	else {
		board_->getTile(position.x, position.y)->removePiece();
	}

	if (isWhiteTurn_) {
		whitePlayer_->setKingPosition(KingPos);
	}

	else {
		blackPlayer_->setKingPosition(KingPos);
	}

	return isPossibleMove;
}

bool Game::isGameFinished(){
	std::vector<std::shared_ptr<Piece>> pieces = blackPlayer_->getPieces();
	if (isWhiteTurn_) {
		pieces = whitePlayer_->getPieces();
	}

	for (int i = 0; i < pieces.size(); i++) {
		if (nextMove(board_->getTile(pieces[i]->getPosition().x, pieces[i]->getPosition().y)).size() > 0) {
			return false;
		}
	}

	return true;
}




