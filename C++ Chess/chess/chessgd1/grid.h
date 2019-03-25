#ifndef GRID_H
#define GRID_H

#include<iostream>
#include<vector>
#include"slot.h"
#include"player.h"


class Reverse_move;
class Player;
class Subject;
class TextDisplay;
class Piece;


class Grid{
  std::vector<std::vector<Slot>> theGrid;
  std::vector<Player *> Players;
  std::vector<Reverse_move> step;
  TextDisplay *td = nullptr;
  Observer * ob = nullptr;

  const int size = 8;
  //Reverse_move * rmp = nullptr;
  Info find_king(int o);
  bool move_king(int o);
  bool move2(int x,int y,int dx,int dy);
public: 
	
	Grid();
	~Grid();
	void undo();
	void setpiece(char c, int x, int y,int ownership);
	void init(Player * p1,Player * p2);
	bool is_valid();
	int check (int x, int y);
	void remove(int x,int y);
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
    Piece * get_piece(int x, int y);// ?? meiyong
	void put_piece(int x, int y,Piece * piece);// ???meiyong
    char getstate(int x,int y);
	bool is_king_check (int ownership);
	bool move(int x, int y, int dx, int dy);
	void result(int ownership);
	bool passant(int a, int b);
	void promote(char c,int x,int y,int ownership);
};

#endif


