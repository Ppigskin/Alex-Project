#include"subject.h"
#include<vector>
#include"human.h"
#include"grid.h"

Human::Human(int i,Grid *game):ownership{ i },g {game} {}

bool Human::move(int x, int y, int dx, int dy) {
	if (x >= 8 || y >= 8 || x < 0 || y < 0) {
		return false;
	}
	else if (g->check(x,y) == ownership) {
		return g->move(x, y, dx, dy);
	}
	return false;
}


