CC=g++

blackjack: driver.o deck.o  hand.o player.o dealer.o game.o
	g++ driver.o deck.o hand.o player.o dealer.o game.o -o blackjack
driver.o: driver.cpp
	g++ driver.cpp -c
deck.o: deck.cpp
	g++ deck.cpp -c 
hand.o: hand.cpp
	g++ hand.cpp -c
player.o: player.cpp
	g++ player.cpp -c
dealer.o: dealer.cpp
	g++ dealer.cpp -c
game.o: game.cpp
	g++ game.cpp -c
clean:
	rm -f a.out blackjack *.o
