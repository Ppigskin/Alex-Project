#include"subject.h"
#include<vector>
#include"observer.h"
void Subject::notifyObservers(){
  for(auto &ob: observers) ob->notify(*this);
}

void Subject::attach(Observer *o){
  observers.emplace_back(o);
}


//Subject::Subject(int x,int y):observer{},x{x},y{y}{}


/*bool Subject::is_alive(){
  return state;
}

void Subject::capture(){
  state = false;
}*/

/*Info getinfo(){
	Info coordinate = Info{x ,y};
    return coordinate;
}*/
