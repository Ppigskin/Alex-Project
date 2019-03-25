#ifndef _COMPUTER_H_
#define _COMPUTER_H_
#include"player.h"

class Computer:public Player{
	bool ischeck;
	bool isloss;
public:
	void move();


};
#endif
