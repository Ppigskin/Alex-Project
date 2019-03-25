#ifndef SUBJECT_H_
#define SUBJECT_H_
#include <vector>
#include"info.h"

class Observer;
class Grid;

class Subject{
protected:
  std::vector<Observer*> observers;
 // int x;
  //int y;
//  bool state = true;
//  Info coordinate;
public:
  //Subject(int x,int y);
  void attach(Observer * o);
  void notifyObservers();
  //void is_alive();
//  virtual bool  move(Grid &g, int x, int y)= 0;
  //void capture(int x,int y);
  virtual int check() = 0 ;
  virtual char getstate() = 0;
  virtual Info getInfo()= 0;
};

#endif
