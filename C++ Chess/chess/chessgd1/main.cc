#include <iostream>
#include <string>
#include<sstream>
#include "grid.h"
#include "info.h"
#include "player.h"
#include"computer1.h"
#include"computer2.h"
#include"computer3.h"
#include "human.h"

using namespace std;

int main(int argc, char *argv[]) {
	cin.exceptions(ios::eofbit | ios::failbit);
	string cmd;
	
	// int colour = 0;
	int hand = 2;
	bool p1isc = false;
	bool p2isc = false;
	bool isset = false;
	double wwin = 0;
	double bwin = 0;

	try {
		while (true) {
			if (cin.eof()) {
				break;
			}
			else {
				Grid g;
				Player * p1;
				Player * p2;
				while (cin >> cmd) {
					if (cmd == "setup") {
						isset = true;
						string set_cmd;
						cout << g;
						int ownership = 2;

						while (true) {
							cin >> set_cmd;
							if (set_cmd == "done") {
								if (g.is_valid()) {
									break;
								}
							}
							else if (set_cmd == "+") {
								char c;
								cin >> c;
								string s;
								cin >> s;
								istringstream ss(s);
								char x;
								char y;
								if (ss.get(x) && ss.get(y)) {
									int dx = x - 'a';
									int dy = 8 - y + '0';
									// cout << dx << " " << dy << endl;
									if (dx < 8 && dx >= 0 && dy < 8 && dy >= 0) {
										g.setpiece(c, dx, dy, ownership);
										cout << g;
									}
								}
							}
							else if (set_cmd == "-") {
								string s;
								cin >> s;
								istringstream ss(s);
								char x;
								char y;
								if (ss.get(x) && ss.get(y)) {
									int dx = x - 'a';
									int dy = 8 - y + '0';
									// cout << dx <<" " << dy << endl;
									if (dx < 8 && dx >= 0 && dy < 8 && dy >= 0) {
										g.remove(dx, dy);
										cout << g;
									}
								}
							}
							else if (set_cmd == "=") {
								string ss;
								cin >> ss;
								if (ss == "colour") {
									if (ownership == 2) {
										ownership = 1;
										// cout << ownership;
									}
									else if (ownership == 1) {
										ownership = 2;
										// cout << ownership;
									}
								}
							}
						}
					}
					else if (cmd == "game") {
						string player1;
						string player2;
						cin >> player1;
						cin >> player2;
						if ((player1 == "human" || player1 == "computer1" || player1 == "computer2" || player1 == "computer3" || player1 == "computer4") &&
							(player2 == "human" || player2 == "computer1" || player2 == "computer2" || player2 == "computer3" || player2 == "computer4")) {
							if (player1 == "human") {
								p2 = new Human(2, &g);
							}
							else if (player1 == "computer1") {
								p2 = new Computer1(2, &g);
								p2isc = true;
							}
							else if (player1 == "computer2") {
								p2 = new Computer2(2, &g);
								p2isc = true;
							}
							else if (player1 == "computer3") {
								p2isc = true;
								p2 = new Computer3(2, &g);
							}
							/*
							else if(player1 == "computer4"){
							p2isc = true;
							p2 = new Computer4(2, &g);
							}*/
							else {}
							if (player2 == "human") {
								p1 = new Human(1, &g);
							}
							else if (player2 == "computer1") {
								p1isc = true;
								p1 = new Computer1(1, &g);
							}
							else if (player2 == "computer2") {
								p1isc = true;
								p1 = new Computer2(1, &g);
							}
							else if (player2 == "computer3") {
								p1isc = true;
								p1 = new Computer3(1, &g);
							}
							/*
							else if(player2 == "computer4"){
							p1isc = true;
							p1 = new Computer4(1, &g);
							}*/
							else {}
							if (!isset) {
								g.init(p2, p1);
							}
							cout << g;
							try
								{
									g.result(hand);
								}
							catch (int result) {
									if (result == 1) {
										wwin++;
										cout << "White wins!" << endl;
										break;
									}
									else if (result == 0) {
										bwin = bwin + 0.5;
										wwin = wwin + 0.5;
										cout << "Stalemate!" << endl;
										break;
									}
									else {}
								}							
							break;
						}
						else {}
					}
				}
				while (cin >> cmd) {
					if (cmd == "move") {
						if (hand == 2) {
							bool ismove = false;
							if (p2isc) {
								p2->move();
								ismove = true;
							}
							else {
								ismove = false;
								string s;
								cin >> s;
								istringstream ss(s);
								cin >> s;
								istringstream ss2(s);
								char cx, cy, cdx, cdy;
								if (ss.get(cx) && ss.get(cy) && ss2.get(cdx) && ss2.get(cdy)) {
									int x = cx - 'a';
									int y = 8 - cy + '0';
									int dx = cdx - 'a';
									int dy = 8 - cdy + '0';
									if (dx < 8 && dx >= 0 && dy < 8 && dy >= 0
										&& x < 8 && x >= 0 && y < 8 && y >= 0) {
										try
										{
											ismove = p2->move(x, y, dx, dy);
										}
										catch (int pr) {
											if (pr == 10) {
												ismove = true;
												char c;
												while (cin >> c)
												{
													if (c == 'R' || c == 'N' || c == 'B' || c == 'Q') {
														g.promote(c, dx, dy, hand);
														break;
													}
													else {
														cin.clear();
													}
												}
											}
										}
									}
								}
							}
							if (ismove == true) {
								hand = 1;
								cout << g;
								if (g.is_king_check(hand)) {
									cout << "Black is in check." << endl;
								}
								try
								{
									g.result(hand);
								}
								catch (int result) {
									if (result == 1) {
										wwin++;
										cout << "White wins!" << endl;
										break;
									}
									else if (result == 0) {
										bwin = bwin + 0.5;
										wwin = wwin + 0.5;
										cout << "Stalemate!" << endl;
										break;
									}
									else {}
								}
							}
						
						}
						else if (hand == 1) {
							bool ismove = false;
							if (p1isc) {
								p1->move();
								ismove = true;
							}
							else {
								ismove = false;
								string s;
								cin >> s;
								istringstream ss(s);
								cin >> s;
								istringstream ss2(s);
								char cx, cy, cdx, cdy;
								if (ss.get(cx) && ss.get(cy) && ss2.get(cdx) && ss2.get(cdy)) {
									int x = cx - 'a';
									int y = 8 - cy + '0';
									int dx = cdx - 'a';
									int dy = 8 - cdy + '0';
									if (dx < 8 && dx >= 0 && dy < 8 && dy >= 0
										&& x < 8 && x >= 0 && y < 8 && y >= 0) {
										try
										{
											ismove = p1->move(x, y, dx, dy);
										}
										catch (int pr) {
											if (pr == 10) {
												ismove = true;
												char c;
												while (cin >> c)
												{
													if (c == 'R' || c == 'N' || c == 'B' || c == 'Q') {
														g.promote(c, dx, dy, hand);
														break;
													}
													else {
														cin.clear();
													}
												}

											}
										}
									}
								}
							}
							if (ismove) {
								hand = 2;
								cout << g;
								if (g.is_king_check(hand)) {
									cout << "White is in check." << endl;
								}
								try
								{
									g.result(hand);
								}
								catch (int result) {
									if (result == 1) {
										bwin++;
										cout << "Black wins!" << endl;
										break;
									}
									else if (result == 0) {
										bwin = bwin + 0.5;
										wwin = wwin + 0.5;
										cout << "Stalemate!" << endl;
										break;
									}
									else {}
								}
							}
						}
					}
					else if (cmd == "resign") {
						if (hand == 1) {
							wwin++;
							cout << "White wins!" << endl;
						}
						else {
							bwin++;
							cout << "Black wins!" << endl;
						}
						break;
					}
					else if (cmd == "undo") {
						g.undo();
					}
				}
				delete p1;
				delete p2;
			}
		}
		
	}
	catch (ios::failure &) {}  // Any I/O failure quits
	cout << "Final Score:" << endl << "White: " << wwin << endl << "Black: " << bwin << endl;
}



