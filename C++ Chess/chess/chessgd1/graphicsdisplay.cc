#include "graphicsdisplay.h"
#include "window.h"
using namespace std;
#include<string>
GraphicsDisplay::GraphicsDisplay(int n) :w{}, gridSize{ n } {
	int size = 500 / (gridSize + 1);
	for (int i = 1; i < gridSize + 1; i++) {
		for (int j = 0; j < gridSize; j++) {
			if ((i + j) % 2 == 0) {
				w.fillRectangle(i*size, j * size, size, size, Xwindow::Black);
			}
			else {
				w.fillRectangle(i*size, j * size, size, size, Xwindow::White);
			}
		}
	}
	int half_s = size / 2;
	w.drawString(half_s, 0 * size + half_s, "8");
	w.drawString(half_s, 1 * size + half_s, "7");
	w.drawString(half_s, 2 * size + half_s, "6");
	w.drawString(half_s, 3 * size + half_s, "5");
	w.drawString(half_s, 4 * size + half_s, "4");
	w.drawString(half_s, 5 * size + half_s, "3");
	w.drawString(half_s, 6 * size + half_s, "2");
	w.drawString(half_s, 7 * size + half_s, "1");

	w.drawString(1 * size + half_s, 8 * size + half_s, "a");
	w.drawString(2 * size + half_s, 8 * size + half_s, "b");
	w.drawString(3 * size + half_s, 8 * size + half_s, "c");
	w.drawString(4 * size + half_s, 8 * size + half_s, "d");
	w.drawString(5 * size + half_s, 8 * size + half_s, "e");
	w.drawString(6 * size + half_s, 8 * size + half_s, "f");
	w.drawString(7 * size + half_s, 8 * size + half_s, "g");
	w.drawString(8 * size + half_s, 8 * size + half_s, "h");
}
  


void GraphicsDisplay::notify(Subject &getchange){
  int size = 500 / (gridSize + 1);
  int half_s = size / 2;
  int quar_s = size / 4;
  int x = getchange.getInfo().col + 1;
  int y = getchange.getInfo().row;
  char c = getchange.getstate();
  int owner = getchange.check();
   if((x+y) % 2 == 0){ 
     w.fillRectangle(x * size, y * size, size , size , Xwindow::Black);
    }
   else{
     w.fillRectangle(x * size, y * size, size , size , Xwindow::White);
   }

   if (owner == 2) {
	   string s = "";
	   s = s + c;
	   w.fillRectangle(x * size + quar_s, y * size + quar_s, half_s, half_s, Xwindow::Green);
	   w.drawString(x * size + half_s, y * size + half_s, s);
   }
   else if (owner == 1) {
	   c = c - 'A' + 'a';
	   string s = ""; 
	   s = s + c;
	   w.fillRectangle(x * size + quar_s, y * size + quar_s, half_s, half_s, Xwindow::Blue);
	   w.drawString(x * size + half_s, y * size + half_s, s);
   }
   else {
   }
}


