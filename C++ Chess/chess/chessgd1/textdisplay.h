#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
//#include "state.h"
#include "info.h"

class Cell;

class TextDisplay: public Observer{
  std::vector<std::vector<char>> theDisplay;
  const int gridSize;
 public:
  ~TextDisplay() = default;
  TextDisplay(int n);

  void notify(Subject &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif

