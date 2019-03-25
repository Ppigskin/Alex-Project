#include"subject.h"
#include<vector>
#include"computer2.h"
#include <stdlib.h>
#include <algorithm>
#include<cstdlib>
#include"grid.h"
using namespace std;
#include "info.h"


Computer2::Computer2(int i, Grid *game):ownership { i }, g{game} {}

void Computer2::move() {
srand((unsigned)time(NULL));
Info EnemyKing;
//vector<Info>temp;
vector<Info>mypiece;
vector<Info>otherpiece;
vector<Info>emptyslot;
int otherownership;
if (ownership == 1) otherownership = 2;
else otherownership = 1;

/*for (int i = 0; i < gridsize; ++i) {
for (int j = 0; j < gridsize; ++j) {
	temp.emplace_back(Info(j,i));
}
}*/

for (int i = 0; i < gridsize; ++i) {
for (int j = 0; j < gridsize; ++j) {
	if (g->check(j,i) == ownership) {
		mypiece.emplace_back(Info{ j,i });
	}
	else if (g->check(j, i) == otherownership) {
		otherpiece.emplace_back(Info{ j, i });
		if (g->getstate(j, i) == 'K') {
			EnemyKing = Info{ j, i };
		}
	}
	else {
		emptyslot.emplace_back(Info{ j, i });
	}
}
}

int kx = EnemyKing.col;
int ky = EnemyKing.row;

vector<Info>pcheck;
vector<Info>rcheck;
vector<Info>ncheck;
vector<Info>bcheck;
vector<Info>qcheck;

for (int i = kx + 1; i < gridsize; i++) {
	if (g->check(i, ky) == otherownership) {
		break;
		rcheck.emplace_back(Info{ i, ky });
		qcheck.emplace_back(Info{ i, ky });
	}
	else if (g->check(i, ky) ==  0) {
		rcheck.emplace_back(Info{ i, ky });
		qcheck.emplace_back(Info{ i, ky });
	}
}
for (int i = kx - 1; i > 0; i--) {
	if (g->check(i, ky) == otherownership) {
		break;
		rcheck.emplace_back(Info{ i, ky });
		qcheck.emplace_back(Info{ i, ky });
	}
	else if (g->check(i, ky) ==  0) {
		rcheck.emplace_back(Info{ i, ky });
		qcheck.emplace_back(Info{ i, ky });
	}

}
for (int i = ky + 1; i < gridsize; i--) {
	if (g->check(kx, i) == otherownership) {
		rcheck.emplace_back(Info{ kx,i });
		qcheck.emplace_back(Info{ kx, i });
		break;
	}
	else if (g->check(kx, i) ==  0) {
		rcheck.emplace_back(Info{ kx, i });
		qcheck.emplace_back(Info{ kx, i });
	}
}
for (int i = ky - 1; i > 0; i--) {
	if (g->check(kx, i) == otherownership) {		
		rcheck.emplace_back(Info{ kx, i });
		qcheck.emplace_back(Info{ kx, i });
		break;
	}
	else if (g->check(kx, i) ==  0) {
		rcheck.emplace_back(Info{ kx, i });
		qcheck.emplace_back(Info{ kx, i });
	}
}
for (int i = 1; i < gridsize; i++) {
	int px = kx + i;
	int py = ky + i;
	if (px >= gridsize || py >= gridsize) break;
	else if (g->check(px, py) == otherownership) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px, py });
		break;
	}
	else if (g->check(px, py) == 0) {
		bcheck.emplace_back(Info{ px,py });
		qcheck.emplace_back(Info{ px,py });
	}
}
for (int i = 1; i < gridsize; i++) {
	int px = kx - i;
	int py = ky - i;
	if (px < 0 || py < 0) break;
	else if (g->check(px, py) == otherownership) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px, py });
		break;
	}
	else if (g->check(px, py) == 0) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px, py });
	}
}
for (int i = 1; i < gridsize; i++) {
	int px = kx + i;
	int py = ky - i;
	if (px >= gridsize || py < 0) break;
	else if (g->check(px, py) == otherownership) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px,py });
		break;
	}
	else if (g->check(px, py) == 0) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px,py });
	}
}
for (int i = 1; i < gridsize; i++) {
	int px = kx - i;
	int py = ky + i;
	if (px < 0|| py >= gridsize) break;
	else if (g->check(px, py) == otherownership) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px,py });
		break;
	}
	else if (g->check(px, py) == 0) {
		bcheck.emplace_back(Info{ px, py });
		qcheck.emplace_back(Info{ px,py });
	}
}
int pc = 0;

//pcheck
if (otherownership == 1) {
	pc = 1;
}
else {
	pc = -1;
}
if (g->check(kx + 1, ky + pc) != ownership) {
	pcheck.emplace_back(Info{ kx + 1, ky + pc });
}
if (g->check(kx - 1, ky + pc) != ownership) {
	pcheck.emplace_back(Info{ kx - 1, ky + pc });
}

random_shuffle(mypiece.begin(), mypiece.end());
vector <Info>possibleattack;

for (size_t i = 0; i < mypiece.size(); i++){
	int x = mypiece.at(i).col;
	int y = mypiece.at(i).row;
	possibleattack.clear();
	possibleattack.insert(possibleattack.end(), otherpiece.begin(), otherpiece.end());

	if (g->getstate(x, y) == 'P') {
		possibleattack.insert(possibleattack.end(), pcheck.begin(), pcheck.end());
	}
	else if (g->getstate(x, y) == 'R') {
		possibleattack.insert(possibleattack.end(), rcheck.begin(), rcheck.end());
	}
	else if (g->getstate(x, y) == 'N') {
		possibleattack.insert(possibleattack.end(), ncheck.begin(), ncheck.end());
	}
	else if (g->getstate(x, y) == 'B') {
		possibleattack.insert(possibleattack.end(), bcheck.begin(), bcheck.end());
	}
	else if (g->getstate(x, y) == 'Q') {
		possibleattack.insert(possibleattack.end(), qcheck.begin(), qcheck.end());
	}
	else if (g->getstate(x, y) == 'K') {
		break; 
		//possibleattack.insert(possibleattack.end(), kcheck.begin(), kcheck.end());
	}
	random_shuffle(possibleattack.begin(), possibleattack.end());


for (size_t j = 0; j < possibleattack.size(); j++){
	int dx = possibleattack.at(j).col;
	int dy = possibleattack.at(j).row;
	bool ismove = false;
	try
	{
		ismove = g->move(x, y, dx, dy);
	}
	catch (int prox) {
		if (prox == 10) {
			ismove = true;
			g->promote('Q', dx, dy, ownership);
		}
	}

	if (ismove) {
		possibleattack.clear();
		mypiece.clear();
		return;
	}
}
}

//cant capture and check
random_shuffle(mypiece.begin(), mypiece.end());
random_shuffle(emptyslot.begin(), emptyslot.end());
for (size_t p = 0; p < mypiece.size(); p++) {
for (size_t i = 0; i < emptyslot.size(); i++) {
	int x = mypiece.at(p).col;
	int y = mypiece.at(p).row;
	int dx = emptyslot.at(i).col;
	int dy = emptyslot.at(i).row;
	bool ismove = false;
	try
	{
		ismove = g->move(x, y, dx, dy);
	}
	catch (int x) {
		if (x == 10) {
			ismove = true;
			g->promote('Q', dx, dy, ownership);
		}
	}

	if (ismove) {
		emptyslot.clear();
		mypiece.clear();
		return;
	}
}
}
// reshu
}
