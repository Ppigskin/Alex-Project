#include "slot.h"
#include "grid.h"
#include "subject.h"
#include "pieces.h"
#include "textdisplay.h"
#include "info.h"
#include "reverse_move.h"
#include "graphicsdisplay.h"


using namespace std;
struct Info;

Grid::~Grid(){
  delete td;
  delete ob;
}
Grid::Grid() { 
  td = new TextDisplay(size);
  ob = new GraphicsDisplay(size);
	//theGrid.clear();
  for (int i = 0; i < size; i++) {
	  vector<Slot>newline;
	  theGrid.emplace_back(newline);
	  for (int j = 0; j < size; j++) {
        theGrid[i].emplace_back(Slot(j,i));
		theGrid[i][j].attach(td);
		theGrid[i][j].attach(ob);
	  }
  }
}

int Grid::check(int x, int y) {
	if (x >= 0 && y >= 0 && x < 8 && y < 8) {
		return theGrid[y][x].check();
	}
	else return 10;
}

void Grid::init(Player * p1, Player * p2) {
	Players.emplace_back(p1);
	Players.emplace_back(p2);
	theGrid[0][0].set('R',1);
	theGrid[0][1].set('N',1);
	theGrid[0][2].set('B',1);
	theGrid[0][3].set('Q',1);
	theGrid[0][4].set('K',1);
	theGrid[0][5].set('B',1);
	theGrid[0][6].set('N',1);
	theGrid[0][7].set('R',1);

	theGrid[7][0].set('R',2);
	theGrid[7][1].set('N',2);
	theGrid[7][2].set('B',2);
	theGrid[7][3].set('Q',2);
	theGrid[7][4].set('K',2);
	theGrid[7][5].set('B',2);
	theGrid[7][6].set('N',2);
	theGrid[7][7].set('R',2);

	for (int i = 0; i < size; i++) {
		theGrid[1][i].set('P', 1);
		theGrid[6][i].set('P', 2);
	}    
}
 
bool Grid::is_valid() {
	int BK = 0;
	int WK = 0;
	for (int i = 0; i < size; i++) {
	for (int j = 0; j < size; j++) {
		if (theGrid[i][j].getstate() == 'K') {
		if (theGrid[i][j].check() == 1) {
			WK++;
                if(theGrid[i][j].piece ->is_checking(this,j,i)){
                   return false;
		}
                }
		else {
                if(theGrid[i][j].piece->is_checking(this,j,i)){
                   return false;
                }
			BK++;
		}
		}
		else if (theGrid[i][j].getstate() == 'P') {
		if (i == 7 || i == 0) {
		    return false;
		}
		}
			
	}
	}
	if (BK == 1 && WK == 1)return true;
	else return false;
}

void Grid::remove(int x,int y) {
	if (x >= 0 && y >= 0 && x < size && y < size) {
		delete theGrid[y][x].piece;
		theGrid[y][x].piece = nullptr;
		theGrid[y][x].notifyObservers();
	}
}

void Grid::setpiece(char c,int x,int y,int ownership) {
	if (x >= 0 && y >= 0 && x < size && y < size) {
		theGrid[y][x].set(c, ownership);
	}
}

char Grid::getstate(int x, int y) {
	if (x >= 0 && y >= 0 && x < size && y < size) {
		return theGrid[y][x].getstate();
	}
	else return '?';
}

ostream &operator<<(ostream &out, const Grid &g) {
	out << * g.td;
	return out;
}

Piece * Grid:: get_piece(int x, int y){ // meiyong
	if (x >= 0 && y >= 0 && x < size && y < size) {
		return theGrid[y][x].piece;
	}
	else return nullptr;
}

void Grid::put_piece(int x, int y, Piece * piece) {// ???? meiyong
	if (x >= 0 && y >= 0 && x < size && y < size) {
		theGrid[y][x].put(piece);
	}
}

Info Grid::find_king(int o) {
//	cout << "finedK" << endl;
	Info in;
	for (int i = 0; i < size; ++i) {
	for (int j = 0; j < size; ++j) {
		Piece *temp = get_piece(j, i);
		//cout << j << i << endl;
		if (temp != nullptr) {
		if ((temp->get_ownership() == o) && (temp->getstate() == 'K')) {
			in = Info{ j, i };
			break;
				}
		}
		}
	}
//	cout << "endfindk" << endl;
	return in;
	
}

bool Grid::passant(int a, int b){
  if(step.empty()) return false;
  int x = step.back().x;
  int y = step.back().y;
  int dx = step.back().dx;
  int dy = step.back().dy;
  int start_line, end_line, owner;
  owner = check(dx , dy);
  if(owner == 1) {
    start_line = 1;
    end_line = 3;
  }
  else {
    start_line = 6;
    end_line = 4;
  }
  if((getstate(dx, dy) == 'P') && (y == start_line) && (dy == end_line) && (b == dy) && ((dx == a + 1) || (dx == a - 1))){ 
    return true;
  }
  return false;
}

bool Grid::move(int x, int y, int dx, int dy) {
	if (x >= 0 && y >= 0 && x < size && y < size && dx >= 0 && dy >= 0 && dx < size && dy < size && theGrid[y][x].piece != nullptr) {
		if (theGrid[y][x].piece->move(this, dx, dy) && (getstate(dx, dy) != 'K')) {
			int ownership = check(x, y);
			Piece *temp1 = theGrid[y][x].temp_get();
			Piece *temp2 = theGrid[dy][dx].temp_putback(temp1);
			Info position_king = find_king(ownership);
			int king_x = position_king.col;
			int king_y = position_king.row;
			if (theGrid[king_y][king_x].piece->is_checking(this, king_x, king_y)) {		
					temp1 = theGrid[dy][dx].temp_putback(temp2);
					temp2 = theGrid[y][x].temp_putback(temp1);
					return false;
				}
			else {
				temp1 = theGrid[dy][dx].temp_putback(temp2);
				temp2 = theGrid[y][x].temp_putback(temp1);
				
			}
		
                        if(passant(x, y) && (getstate(x, y) == 'P') && (check(dx, y) != 0) && (dx == step.back().dx)){
                                if(getstate(dx, y) == 'P'){
                               
                                Piece *t = theGrid[y][dx].get_piece();
                                delete t;
                                }
                        }
			get_piece(x, y)->set(dx, dy);
			Piece * piece = theGrid[y][x].get_piece();			
			Piece * last = theGrid[dy][dx].piece;
			theGrid[dy][dx].piece = nullptr;
			theGrid[dy][dx].put(piece);			
			step.clear();
			step.emplace_back(Reverse_move{ x, y, dx, dy, nullptr });
			step.back().captured = last;
			if ((getstate(dx, dy) == 'P') && ((dy == 0) || (dy == 7))) {
				throw 10;
			}
//			Reverse_move *r = new Reverse_move{ x, y, dx, dy, last };
//			delete rmp;
//			rmp = r;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}


bool Grid::move2(int x, int y, int dx, int dy) {
	if (x >= 0 && y >= 0 && x < size && y < size && dx >= 0 && dy >= 0 && dx < size && dy < size && theGrid[y][x].piece != nullptr) {
		if (theGrid[y][x].piece->move(this, dx, dy) && (getstate(dx, dy) != 'K')) {
			int ownership = check(x, y);
			Piece *temp1 = theGrid[y][x].temp_get();
			Piece *temp2 = theGrid[dy][dx].temp_putback(temp1);
			Info position_king = find_king(ownership);
			int king_x = position_king.col;
			int king_y = position_king.row;
			if (theGrid[king_y][king_x].piece->is_checking(this, king_x, king_y)) {
				temp1 = theGrid[dy][dx].temp_putback(temp2);
				temp2 = theGrid[y][x].temp_putback(temp1);
				return false;
			}
			else {
				temp1 = theGrid[dy][dx].temp_putback(temp2);
				temp2 = theGrid[y][x].temp_putback(temp1);
			}
			return true;
		}
	}
	return false;
}

bool Grid::move_king(int ownership) {
	Info position_king = find_king(ownership);
	int x = position_king.col;
	int y = position_king.row;
	if (move2(x,y,x + 1,y)) {
		return true;
	}
	if (move2(x, y, x + 1, y + 1)) {
		return true;
	}
	if (move2(x, y, x + 1, y - 1)) {
		return true;
		
	}
	if (move2(x, y, x - 1, y + 1)) {
		return true; 
	}
	if (move2(x, y, x - 1, y - 1)) {
		return true; 
	}
	if (move2(x, y, x - 1, y)) {
		return true; 
	}
	if (move2(x, y, x , y + 1)) {
		return true; 
	}
	if (move2(x, y, x, y - 1)) {
		return true;
	}
	
	return false;
}

void Grid::result(int ownership){
 Info position_king = find_king(ownership);
  int king_x = position_king.col;
  int king_y = position_king.row;
  vector<Info>mypieces;
  vector<Info>moveslot;
  for (int i = 0; i < size; i++) {
	  for (int j = 0; j < size; j++) {
		  if(theGrid[j][i].getstate() == 'K' && theGrid[j][i].check() == ownership){}
		  else  if (theGrid[j][i].check() == ownership) {
			  mypieces.emplace_back(Info{ i, j });
		  }
		  else {
			  moveslot.emplace_back(Info{ i,j });
		  }
	  }
  }

  if (theGrid[king_y][king_x].piece->is_checking(this, king_x, king_y)) {
	  for (size_t start = 0; start < mypieces.size(); start++) {
		  for (size_t end = 0; end < moveslot.size(); end++) {
			  int x = mypieces.at(start).col;
			  int y = mypieces.at(start).row;
			  int dx = moveslot.at(end).col;
			  int dy = moveslot.at(end).row;
			  if (move2(x,y,dx,dy)) {
				  return;
			  }
		  }
	  }
	  if (move_king(ownership)) { 
		  return;
	  }
	  throw 1;
  }
  else {//"stalemate"

	  for (size_t start = 0; start < mypieces.size(); start ++){
		  for (size_t end = 0; end < moveslot.size();end++){
			  int x = mypieces.at(start).col;
			  int y = mypieces.at(start).row;
			  int dx = moveslot.at(end).col;
			  int dy = moveslot.at(end).row;
			  //cout << x << " " << y << " " << dx << " " << dy << endl;
			  if (move2(x,y,dx,dy)){
				  mypieces.clear();
				  moveslot.clear();
				  return;
			  }
		  }
	  }

	  if (move_king(ownership)) { return; }
	  throw 0;
  }
  return;
}

bool Grid::is_king_check(int ownership) {
	Info position_king = find_king(ownership);
	int king_x = position_king.col;
	int king_y = position_king.row;
	return theGrid[king_y][king_x].piece->is_checking(this, king_x, king_y);
}

void Grid::undo() {
	if (step.size() == 0) {
		return;
	}
	else {
		int x = step.back().x;
		int y = step.back().y;
		int dx = step.back().dx;
		int dy = step.back().dy;
		Piece * capture = step.back().captured;
		Piece * piece = theGrid[dy][dx].get_piece();
		theGrid[y][x].put(piece);
		theGrid[dy][dx].piece = capture;
		theGrid[dy][dx].notifyObservers();
		theGrid[y][x].piece->set(x, y);
		step.back().captured = nullptr;
		step.pop_back();
	}
}

void Grid::promote(char c,int x,int y,int ownership) {
	remove(x, y);
	setpiece(c, x, y, ownership);
}



