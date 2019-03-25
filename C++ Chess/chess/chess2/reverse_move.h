#ifndef REVERSE_MOVE_H
#define REVERSE_MOVE_H
#include "pieces.h"
class Reverse_move{
public: 
  int x;
  int y;
  int dx;
  int dy;
  Piece *captured;

  ~Reverse_move(){delete captured;};
};

#endif

