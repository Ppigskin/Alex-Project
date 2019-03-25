#ifndef _COMPUTER1_H_
#define _COMPUTER1_H_
#include"player.h"

class Grid;

class Computer1:public Player{
	int ownership;
	Grid * g;
	const int gridsize = 8;
public:
	Computer1(int i,Grid *game);
	void move()override;
};
#endif
