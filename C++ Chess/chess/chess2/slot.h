#ifndef _SLOT_H_
#define _SLOT_H_
#include "subject.h"

struct info;
class Piece;
class Grid;

class Slot:public Subject{
  int x;
  int y;
  Piece *piece;
  int under_attack = 0;

  Slot(int x,int y);
  void set(char c,int owner);
  int check() override;
  char getstate() override;
 // void remove();
  Piece *get_piece();
  void put(Piece * newpiece);
  Info getInfo() override;
  void attack(int i);
  friend class Grid;
  //friend class Computer3;
  Piece * temp_get();
  Piece * temp_putback(Piece * newpiece);

public:

~Slot();
};
#endif
