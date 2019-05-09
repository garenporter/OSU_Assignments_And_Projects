CC=g++

zoo_tycoon: driver.o zoo.o animal.o tiger.o bear.o penguin.o
	g++ driver.o zoo.o animal.o tiger.o bear.o penguin.o -o zoo_tycoon
driver.o: driver.cpp
	g++ driver.cpp -c
zoo.o: zoo.cpp
	g++ zoo.cpp -c
animal.o: animal.cpp
	g++ animal.cpp -c
tiger.o: tiger.cpp
	g++ tiger.cpp -c
bear.o: bear.cpp
	g++ bear.cpp -c
penguin.o: penguin.cpp
	g++ penguin.cpp -c
clean:
	rm -f a.out zoo_tycoon *.o
