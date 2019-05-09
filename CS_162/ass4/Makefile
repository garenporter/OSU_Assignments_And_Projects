CC=g++

hunt_the_wumpus: driver.o map.o player.o gold.o wumpus.o pit.o bats.o nothing.o event.o room.o
	g++ driver.o map.o player.o gold.o wumpus.o pit.o bats.o nothing.o event.o room.o
driver.o: driver.cpp
	g++ driver.cpp -c
map.o: map.cpp
	g++ map.cpp -c
player.o: player.cpp
	g++ player.cpp -c
gold.o: gold.cpp
	g++ gold.cpp -c
wumpus.o: wumpus.cpp
	g++ wumpus.cpp -c
pit.o: pit.cpp
	g++ pit.cpp -c
bats.o: bats.cpp
	g++ bats.cpp -c
nothing.o: nothing.cpp
	g++ nothing.cpp -c
room.o: room.cpp
	g++ room.cpp -c
event.o: event.cpp
	g++ event.cpp -c
clean:
	rm -f a.out hunt_the_wumpus *.o
