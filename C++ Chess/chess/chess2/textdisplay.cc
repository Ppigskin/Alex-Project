#include "textdisplay.h"
#include "subject.h"
using namespace std;

TextDisplay::TextDisplay(int n):theDisplay{},gridSize{n}{
  for(int i = 0; i < gridSize; i++){
    vector<char> newline;
    theDisplay.push_back(newline);
    char n = '8' - i;
    theDisplay.at(i).push_back(n);
    theDisplay.at(i).push_back(' ');
  for(int j = 0; j < gridSize; j++){
    if((i+j)%2 != 0)theDisplay.at(i).push_back('_');
	else theDisplay.at(i).push_back(' ');
  }
    theDisplay.at(i).push_back('\n'); 
  }
 vector<char> newline;
 theDisplay.push_back(newline);
 theDisplay.at(8).push_back('\n');
 theDisplay.at(8).push_back(' ');
 theDisplay.at(8).push_back(' ');
 theDisplay.at(8).push_back('a');
 theDisplay.at(8).push_back('b');
 theDisplay.at(8).push_back('c');
 theDisplay.at(8).push_back('d');
 theDisplay.at(8).push_back('e');
 theDisplay.at(8).push_back('f');
 theDisplay.at(8).push_back('g');
 theDisplay.at(8).push_back('h');
 theDisplay.at(8).push_back('\n');
}

void TextDisplay::notify(Subject &whoNotified){
  int x = whoNotified.getInfo().col + 2;
  int y = whoNotified.getInfo().row;
  if (whoNotified.check() == 2) {// daxie
	  char c = whoNotified.getstate();
	  theDisplay.at(y).at(x) = c;
  }
  else if (whoNotified.check() == 1) { //daxie biancheng xiaoxie
	  char c = whoNotified.getstate();
	  c = c - 'A' + 'a';
	  theDisplay.at(y).at(x) = c;
  }
  else if (whoNotified.check() == 0) {
   if((x + y )% 2 != 0) theDisplay.at(y).at(x) = '_';
   else theDisplay.at(y).at(x) = ' ';

  }
  
}

ostream &operator<<(ostream &out, const TextDisplay &td){
  for(int i = 0; i < td.gridSize ; i++){
  for(int j = 0; j <=td.gridSize + 2; j++){
    out<<td.theDisplay.at(i).at(j);
    
  }
  }
  for(int i = 0; i<td.gridSize + 4; i++){
    out<<td.theDisplay.at(8).at(i);

  }
  return out;
} 
