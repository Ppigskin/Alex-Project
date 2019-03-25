#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player{
public:
	virtual bool move(int x, int y, int dx, int dy) { return false; }
	virtual void move() { return; }


};
#endif
