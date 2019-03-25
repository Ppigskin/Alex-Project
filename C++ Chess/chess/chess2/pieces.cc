#include <iostream>
#include "pieces.h"
#include "grid.h"
using namespace std;
int abs(int n){
  return ((n >= 0) ? n : -n);
}

int King::get_ownership(){
  return ownership;
}

bool King::is_checking(Grid *g, int dx, int dy){
   // Piece * P = g->
    for(int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			     // cout << i << "     " << j << endl;
			Piece * temp = g->get_piece(j, i);
			if (temp != nullptr) {
				if (temp->get_ownership() != ownership) {
					if (temp->getstate() == 'K') {
						if (abs(dx - j) <= 1 && abs(dy - i) <= 1 && (dx != j || dy != i)) {
							return true;
						}
					}
                                          else if (temp->getstate() == 'P'){
                                          int one;
                                          if(ownership == 1) {one = -1;}
                                          else {one = 1;}
                                          if((abs(dx - j) == 1) && (dy == i + one)) {return true;}
                                        }
					else {if (temp->move(g, dx, dy)) {
						return true;}
					}
				}
			}
		}
  }
  return false;
}

bool King::move(Grid *g, int dx, int dy){
  if (dx >= 8 || dy >= 8 || dx < 0 || dy < 0) return false;
 // cout << "king_move" << endl;
  if(dx == x && y == dy) return false;
  if(is_checking(g, dx, dy)) return false;
 // cout << "king_move2" << endl;
  int sx;
  int sy;
  if(ownership == 1){
    sx = 4;
    sy = 0;
  }
  else if(ownership == 2){
    sx = 4;
    sy = 7;
  } 
  if((x != sx) || (y != sy)) has_moved = true;
  if((abs(dx - x) <= 1) && (abs(dy - y) <= 1) && ((dx != x) || (dy != y))){
    if(g->check(dx, dy) != ownership){
      has_moved = true;
   //   cout << "king_move3" << endl;
      return true;
    }
  }
  else if((dy == y) && (dx == 2) && (!has_moved) && (g->getstate(0, dy) == 'R')){
    if(!g->get_piece(0, dy)->get_has_moved() && (!is_checking(g, x, y)) && (!is_checking(g, x - 1, y)) && (!is_checking(g, x - 2, y))){
      if((g->check(1, y) == 0) && (g->check(2, y) == 0) && (g->check(3, y) == 0)){
        g->move(0, y, 3, y);
        has_moved = true;
        return true;
      }
    }
  }
  else if((dy == y) && (dx == 6) && (!has_moved) && (g->getstate(7, dy) == 'R')){
    if(!g->get_piece(7, dy)->get_has_moved() && (!is_checking(g, x, y)) && (!is_checking(g, x + 1, y))){
      if((g->check(5, y) == 0) && (g->check(6, y) == 0)){
        g->move(7, y, 5, y);
        has_moved = true;
        return true;
      }
    }
  }
  return false;
}

char King::getstate() {
  return 'K';
}

int Queen::get_ownership(){
  return ownership;
}


bool Queen::move(Grid *g, int dx, int dy){
	if (dx >= 8 || dy >= 8 || dx < 0 || dy < 0) return false;
 if((dx == x) && (dy == y)) return false;
 else if((dx == x) && (dy > y)){
    for (int i = y + 1; i < dy; ++i){
      if(g->check(x, i) != 0) return false;
    }
  }
 else if ((dx == x) && (dy < y)) {
	 for (int i = y - 1; i > dy; --i) {
		 if (g->check(x, i) != 0) return false;
	 }
 }
 else if((dx > x) && (dy == y)){
    for (int i = x + 1; i < dx; ++i){
      if(g->check(i, y) != 0) return false;
    }
  }
 else if((dx < x) && (dy == y)){
    for (int i = x - 1; i > dx; --i){
      if(g->check(i, y) != 0) return false;
    }
  }
 else if(abs(dx - x) == abs(dy - y)){
    if((dx > x) && (dy > y)){
      for(int i = 1; i < (dx - x); ++i){
        if(g->check(x + i, y + i) != 0) return false;
      }
    }
    else if((dx > x) && (dy < y)){
      for(int i = 1; i < (dx - x); ++i){
        if(g->check(x + i, y - i) != 0) return false;
      }
    }
    else if((dx < x) && (dy < y)){
      for(int i = 1; i < (x - dx); ++i){
        if(g->check(x - i, y - i) != 0) return false;
      }
    }
    else if((dx < x) && (dy > y)){
      for(int i = 1; i < (x - dx); ++i){
        if(g->check(x - i, y + i) != 0) return false;
      }
    }
  }
 else{
    return false;
  }
  
  if (g->check(dx, dy) != ownership){
	  return true;
  }
  else {
	  return false;

  }
}

char Queen::getstate() {
  return 'Q';
}


int Bishop::get_ownership(){
  return ownership;
}

bool Bishop::move(Grid *g, int dx, int dy) {
	if (dx >= 8 || dy >= 8 || dx < 0 || dy < 0) return false;
	if ((dx == x) && (dy == y)) return false;
	else if (abs(dx - x) == abs(dy - y)) {
		if ((dx > x) && (dy > y)) {
			for (int i = 1; i < (dx - x); ++i) {
				if (g->check(x + i, y + i) != 0) return false;
			}
		}
		else if ((dx > x) && (dy < y)) {
			for (int i = 1; i < (dx - x); ++i) {
				if (g->check(x + i, y - i) != 0) return false;
			}
		}
		else if ((dx < x) && (dy < y)) {
			for (int i = 1; i < (x - dx); ++i) {
				if (g->check(x - i, y - i) != 0) return false;
			}
		}
		else if ((dx < x) && (dy > y)) {
			for (int i = 1; i < (x - dx); ++i) {
				if (g->check(x - i, y + i) != 0) return false;
			}
		}
		else {
			return false;
		}
	}
        else {
          return false;
        } 
	if (g->check(dx, dy) != ownership) {
		return true;
	}
	else {
		return false;
	}
	
}

char Bishop::getstate() {
	return 'B';
}

int Rook::get_ownership(){
  return ownership;
}

bool Rook::move(Grid *g, int dx, int dy){
	if (dx >= 8 || dy >= 8 || dx < 0 || dy < 0) return false;
  if((dx == x) && (dy == y)) return false;
  else if((dx == x) && (dy > y)){
    for (int i = y + 1; i < dy; ++i){
      if(g->check(x, i) != 0) return false;
    }
  }
  else if((dx == x) && (dy < y)){
    for (int i = y - 1; i > dy; --i){
      if(g->check(x, i) != 0) return false;
    }
  }
  else if((dx > x) && (dy == y)){
    for (int i = x + 1; i < dx; ++i){
      if(g->check(i, y) != 0) return false;
    }
  }
  else if((dx < x) && (dy == y)){
    for (int i = x - 1; i > dx; --i){
      if(g->check(i, y) != 0) return false;
    }
  }
  else{
    return false;
  }
  if (g->check(dx, dy) != ownership) {
	  return true;
  }
  else {
	  return false;
  }
}

char Rook::getstate() {
  return 'R';
}

/*bool Rook::get_has_moved(){
  return has_moved;
}*/

int Knight::get_ownership(){
  return ownership;
}

bool Knight::move(Grid *g, int dx, int dy){
  if(((abs(dx - x) == 2) && (abs(dy - y) == 1)) || ((abs(dx - x) == 1) && (abs(dy - y) == 2))){
    if(g->check(dx, dy) != ownership) {
      return true;
    }
  }
  return false;
}

char Knight::getstate() {
  return 'N';
}

int Pawn::get_ownership(){
  return ownership;
}

bool Pawn::move(Grid *g, int dx, int dy){
	if (dx >= 8 || dy >= 8 || dx < 0 || dy < 0) return false;
  int move_one;
  int move_two;
  int start_line;
  int pass_line;
  if(ownership == 1){
    move_one = 1;
    move_two = 2;
    start_line = 1;
    pass_line = 4;
  }
  else if(ownership == 2){
    move_one = -1;
    move_two = -2;
    start_line = 6;
    pass_line = 3;
  }
  if(y == start_line) has_moved = false;
  else has_moved = true;
  if((abs(dx - x) == 1) && (dy == (y + move_one))){
    if((g->check(dx, dy) != ownership) && (g->check(dx, dy) != 0)){
      return true;
    }
    else if(g->passant(x, y) && (y == pass_line)){
      return true;
    }
  }
  else if((dy == (y + move_two)) && (dx == x) && (!has_moved)){
    if((g->check(dx, y + move_one) == 0) && (g->check(dx, y + move_two) == 0)){
      return true;
    }
  }
  else if((dy == (y + move_one)) && (dx == x)){
    if(g->check(dx, dy) == 0){
      return true;
    }
  }
 return false;
}
  
char Pawn::getstate() {
  return 'P';
}
