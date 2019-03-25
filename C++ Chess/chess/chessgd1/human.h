#ifndef _HUMAN_H_
#define _HUMAN_H_
#include"player.h"

class Human:public Player{
	int  ownership;
	Grid *g;
public:
	Human(int i, Grid *g);
	bool move(int x,int y,int dx,int dy)override;

};
#endif


