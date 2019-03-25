#include"subject.h"
#include<vector>
#include"computer1.h"
#include"grid.h"
#include <stdlib.h>
#include <algorithm>
#include<cstdlib>
using namespace std;
#include "info.h"

Computer1::Computer1(int i, Grid * game):ownership{ i }, g {game}{}

void Computer1::move() {
srand((unsigned)time(NULL));

vector<Info> temp;
vector<Info> mypiece;

/*for (int i = 0; i < gridsize; ++i) {
for (int j = 0; j < gridsize; ++j) {
	temp.emplace_back(Info{ j,i });
}
}*/

for (int i = 0; i < gridsize; ++i) {
for (int j = 0; j < gridsize; ++j) {
	if (g->check(j, i) == ownership) {
		mypiece.emplace_back(Info{ j, i });
	}
	else {
		temp.emplace_back(Info{ j,i });
	}
}
}

random_shuffle(temp.begin(), temp.end());
random_shuffle(mypiece.begin(), mypiece.end());

for (size_t p = 0; p < mypiece.size(); p++) {
for (size_t i = 0; i < temp.size(); i++) {
	int x = mypiece.at(p).col;
	int y = mypiece.at(p).row;
	int dx = temp.at(i).col;
	int dy = temp.at(i).row;
	bool ismove = false;
	try
	{
		ismove = g->move(x, y, dx, dy);
	}
	catch (int x){
		if (x == 10) {
			ismove = true;
			g->promote('Q', dx, dy, ownership);
		}
	}
	
	if (ismove) {
		temp.clear();
		mypiece.clear();
		return;
	}
}
}
throw "novalidmove";
}


