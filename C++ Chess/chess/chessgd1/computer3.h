#ifndef _COMPUTER3_H_
#define _COMPUTER3_H_
#include"player.h"

class Grid;


class Computer3:public Player{
	int ownership;
	Grid *g;
	const int gridsize = 8;
public:
	Computer3(int i,Grid *game);
	void move()override;


};
#endif


