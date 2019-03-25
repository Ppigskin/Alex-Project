#ifndef GRAPHICSDISPLAY_H_
#define GRAPHICSDISPLAY_H_
#include "info.h"
#include <vector>
#include "observer.h"
#include "window.h"
#include "subject.h"

class GraphicsDisplay: public Observer{
  Xwindow w;
  int gridSize;
  //Observer<Info, State> *ob = nullptr;
public:
  GraphicsDisplay(int n);
  
  void notify(Subject &getchange)override;
};

#endif


