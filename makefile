all: test

test: main.o GridMap.o Cell.o Solver.o MapGenerator.o Interface.o Game.o
	g++ -lncurses  main.o GridMap.o Cell.o Solver.o MapGenerator.o Interface.o Game.o -o test

main.o: main.cpp
	g++ -c main.cpp -o main.o

GridMap.o: GridMap.cpp
	g++ -c GridMap.cpp -o GridMap.o

Cell.o: Cell.cpp
	g++ -c Cell.cpp -o Cell.o

Solver.o: Solver.cpp
	g++ -c Solver.cpp -o Solver.o

MapGenerator.o: MapGenerator.cpp
	g++ -c MapGenerator.cpp -o MapGenerator.o

Interface.o: Interface.cpp
	g++ -c Interface.cpp -o Interface.o

Game.o: Game.cpp
	g++ -c Game.cpp -o Game.o
