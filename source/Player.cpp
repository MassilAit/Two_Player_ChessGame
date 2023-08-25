#include"Player.h"


Player::Player(std::vector<std::shared_ptr<Piece>> pieces) {
	for (int i = 0; i < size(pieces); i++) {
		if (pieces[i]->getName() == 'K') {
			kingPosition_ = pieces[i]->getPosition();
		}
		pieces_.push_back(std::move(pieces[i]));
	}
}

void Player::setKingPosition(Position position) {
	kingPosition_ = position;
}

Position Player::getKingPosition() {
	return kingPosition_;
}

std::vector<std::shared_ptr<Piece>> Player::getPieces() {
	return pieces_;
}

void Player::removePiece(Position position) {
	for (int i = 0; i < pieces_.size(); i++) {
		if (pieces_[i]->getPosition().x == position.x and pieces_[i]->getPosition().y == position.y) {
			pieces_.erase(pieces_.begin() + i);
		}
	}
}
std::shared_ptr<Piece> Player::findPiece(Position position) {
	for (int i = 0; i < pieces_.size(); i++) {
		if (pieces_[i]->getPosition().x == position.x and pieces_[i]->getPosition().y == position.y) {
			return pieces_[i];
		}
	}

	return nullptr;
}
