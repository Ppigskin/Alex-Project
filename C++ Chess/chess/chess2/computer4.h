#ifndef _COMPUTER4_H_
#define _COMPUTER4_H_
#include"player.h"
#include"info.h"

class Grid;


class Computer4:public Player{
	int ownership;
	Grid *g;
	const int gridsize = 8;
public:
	Computer4(int i,Grid *game);
	void move()override;
        bool compare(Info a, Info b);

};
#endif
