game: game.o creature.o player.o screens.o
	g++ game.o creature.o player.o screens.o -o game -lncursesw
	
game.o: game.cpp
	g++ -c game.cpp

creature.o: creature.cpp creature.hpp
	g++ -c creature.cpp
	
player.o: player.cpp player.hpp
	g++ -c player.cpp
	
screens.o: screens.cpp screens.hpp
	g++ -c screens.cpp
	
clean:
	rm *.o game
