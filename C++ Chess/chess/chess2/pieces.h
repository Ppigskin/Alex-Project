#ifndef PIECES_H
#define PIECES_H
#include <iostream>
//#include "subject.h"
class Grid;
class Piece {
public:
/*	int x;
	int y;
	int ownership;*/
//	Piece(int ownership, int x,int y)
//		:x{ x }, y{ y }, ownership{ ownership } {};
	virtual char getstate() = 0;
	virtual int get_ownership() = 0;
	virtual bool move(Grid *g, int dx, int dy) = 0;
    virtual bool get_has_moved(){return true;};
    virtual void set(int dx, int dy) = 0;
    virtual bool is_checking(Grid * g, int dx,int dy){return false;}
    virtual ~Piece() = default;
    const int weight = 0;
};

class King :public Piece{
  int x;
  int y;
  int ownership;
  bool has_moved = false;
public:
  const int weight = 100;
  King(int ownership, int x, int y)
	:x {x}, y{ y }, ownership{ ownership } {};
  bool is_checking(Grid *g, int dx, int dy)override;
  bool move(Grid *g, int dx, int dy) override;
  char getstate()override;
  bool get_has_moved()override{return has_moved;}
  int get_ownership();
  void set(int dx, int dy)override{x = dx; y = dy;}
};

class Queen :public Piece {
  int x;
  int y;
  int ownership;
public:
  const int weight = 9;
  Queen(int ownership, int x, int y)
	: x{ x }, y{ y }, ownership{ ownership } {};
  bool move(Grid * g, int dx, int dy) override;
  char getstate()override;
  int get_ownership() override;
  void set(int dx, int dy)override{x = dx; y = dy;}
};

class Bishop :public Piece {
  int x;
  int y;
  int ownership;
public:
  const int weight = 3;
  Bishop(int ownership, int x, int y)
	: x{ x }, y{ y }, ownership{ ownership } {};
  bool move(Grid *g, int dx, int dy) override;
  char getstate()override;
  int get_ownership() override;
  void set(int dx, int dy)override{x = dx; y = dy;}
};

class Rook :public Piece {
   int x;
   int y;
   int ownership;
  bool has_moved = false;
public:
  const int weight = 5;
  Rook(int ownership, int x, int y)
	 :x{ x }, y{ y }, ownership{ ownership } {};
  bool move(Grid *g, int dx, int dy) override;
  char getstate()override;
  int get_ownership() override;
  bool get_has_moved()override{return has_moved;}
  void set(int dx, int dy)override{x = dx; y = dy;}
};

class Knight :public Piece {
	int x;
	int y;
	int ownership;// int ownership;
public:
  const int weight = 3;
  Knight(int ownership, int x, int y)
	: x{ x }, y{ y }, ownership{ ownership } {};
  bool move(Grid *g, int dx, int dy) override;
  char getstate()override;
  int get_ownership() override;
  void set(int dx, int dy)override{x = dx; y = dy;}
};

class Pawn :public Piece {
	int x;
	int y;
	int ownership;//int ownership;
    bool has_moved = false;
public:
  const int weight = 1;
  Pawn(int ownership, int x, int y)
	:x{ x }, y{ y }, ownership{ ownership } {};
  bool move(Grid *g, int x, int y) override;
  char getstate()override;
  int get_ownership() override;
  void set(int dx, int dy)override{x = dx; y = dy;}
};

#endif
