chess:main.o grid.o textdisplay.o pieces.o graphicsdisplay.o slot.o subject.o computer2.o computer1.o human.o computer3.o
	g++ -std=c++14 *.o window.cc -o chess -lX11

main.o: main.cc grid.h slot.h subject.h info.h player.h computer1.h computer2.h computer3.h human.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c main.cc

grid.o: grid.cc slot.h subject.h info.h grid.h player.h pieces.h textdisplay.h observer.h reverse_move.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c grid.cc

textdisplay.o: textdisplay.cc textdisplay.h observer.h info.h subject.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c textdisplay.cc

pieces.o: pieces.cc pieces.h grid.h slot.h subject.h info.h player.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c pieces.cc

graphicsdisplay.o:graphicsdisplay.cc graphicsdisplay.h window.h subject.h observer.h info.h 
	g++ -std=c++14 -Wall -MMD -Werror=vla -c graphicsdisplay.cc	

slot.o: slot.cc slot.h subject.h info.h pieces.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c slot.cc

subject.o:subject.cc subject.h info.h observer.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c subject.cc

computer3.o:computer3.cc info.h computer3.h player.h grid.h slot.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c computer3.cc

computer2.o:computer2.cc info.h computer2.h player.h grid.h slot.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c computer2.cc

computer1.o: computer1.cc subject.h info.h computer1.h player.h grid.h slot.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c computer1.cc

human.o: human.cc subject.h info.h human.h player.h grid.h slot.h
	g++ -std=c++14 -Wall -MMD -Werror=vla -c human.cc



.PHONY:clean
clean:
	rm *.o a.out


