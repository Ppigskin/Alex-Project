#include "slot.h"
#include"info.h"
#include"pieces.h"
//dtor

Slot::Slot(int x, int y) :x{ x }, y{ y }, piece{ nullptr }, under_attack{0} {}

Info Slot::getInfo(){
  Info cor = Info {x,y};

  return cor;
}
void Slot::set(char c,int owner){
  Piece * newpiece;
  if (c == 'K') newpiece = new King(owner, x, y);
  else if (c == 'Q') newpiece = new Queen(owner, x, y);
  else if (c == 'B') newpiece = new Bishop(owner, x, y);
  else if (c == 'R') newpiece = new Rook(owner, x, y);
  else if (c == 'N') newpiece = new Knight(owner, x, y);
  else if (c == 'P') newpiece = new Pawn(owner, x, y);
  else {
	  newpiece = piece;
	  piece = nullptr;
  }
  delete piece;
  piece = newpiece;
  notifyObservers();
}

char Slot::getstate() {
	if (piece == nullptr)
	{
		return '?';
	}
	return piece->getstate();
}

int Slot::check() {
	if (piece == nullptr) {return 0;}
	else {   
		return piece->get_ownership();
	}
}

Slot::~Slot(){
  delete piece;
}

/*void Slot::remove() {
	delete piece;
	piece = nullptr;
	notifyObservers();
}*/

Piece * Slot::get_piece() {
	Piece * thispiece = piece;
	piece = nullptr;
	notifyObservers();
	return thispiece;
}

void Slot::put(Piece *newpiece){
	if (this -> piece == nullptr) {
		this -> piece = newpiece;
		notifyObservers();
	}
	else {
		delete piece;
		this->piece = newpiece;
		notifyObservers();
	}
}

void Slot::attack(int i) {
	if (under_attack != i) under_attack = 3;
	else if (under_attack == 0) under_attack = i;
}

Piece * Slot::temp_get() {
	Piece * thispiece = piece;
	piece = nullptr;
	return thispiece;
}

Piece * Slot::temp_putback(Piece *newpiece) {
	if (this->piece == nullptr) {
		this->piece = newpiece;
		return nullptr;
	}
	else {
		Piece * p = piece;
		this->piece = newpiece;
		return p;
	}
}

