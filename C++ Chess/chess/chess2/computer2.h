#ifndef _COMPUTER2_H_
#define _COMPUTER2_H_
#include"player.h"

class Grid;


class Computer2:public Player{
	int ownership;
	Grid *g;
	const int gridsize = 8;
public:
	Computer2(int i,Grid *game);
	void move()override;


};
#endif
