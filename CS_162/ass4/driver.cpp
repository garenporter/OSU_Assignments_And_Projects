#include "./room.h"
#include "./wumpus.h"
#include "./pit.h"
#include "./gold.h"
#include "./bats.h"
#include "./map.h"
#include <cstdlib>
#include <ctime>
int main(int argc, char *argv[]){
	int av = NULL;
	if(argv[1] == NULL){
		av = 0;
	}
	else{
		av = atoi(argv[1]);
	}
	while(av<=4){
		cout << "Enter a number greater than 4: ";
		int t;
		cin >> t;
		av = t;
	}
	cout << endl;
	cout <<"Welcome to Hunt the Wumpus! You are the adventurer Jeremy Cole. You've heard rumors of a stash of gold buried deep in a cave and want to see if these rumors are true. You are in the cave, but there are many hazards to watch out for..." << endl;
	cout << "1. Bottomless pits: You will feel a breeze when you are next to a bottomless pit" << endl;
	cout << "2. Super Bats: You will hear wings flapping when you are next to super bats. " << endl;
	cout << "3. Wumpus: You will smell a terrible stench when the wumpus is near by.  You must shoot the wumpus to complete your quest." << endl;
	cout <<"4. Gold: You will see a glimmer when you are next to the gold. You must acquire the gold to complete your quest." << endl;
	cout << "To win you must kill the wumpus, find the gold, and make it back to the room you started in. Good luck! " << endl;
	cout << endl;
//	m.set_size(5);

//	m.set_cave(m.get_size());
	int g = 0;
	while(g==0){
		map m, m2;
		m.set_size(av);
		m.set_cave(m.get_size());
		m2 = m;
		m.play_game();		
		cout << "Would you like to play again? (Press 1 for yes, 0 for no) ";
		int d;
		cin >> d;
		if(d==1){
			int h = 0;
			while(h==0){
				cout << "Would you like to play the same map(press 1) or a different map (press 2)? " << endl;
				int d2;
				cin >> d2;
				if(d2 == 1){
					
					m2.play_game();
				}
				if(d2 == 2){
					map m3;
					cout << "What size of cave would you like? ";
					int s;
					cin >> s;
					m3.set_size(s);
					m3.set_cave(m3.get_size());
					m3.play_game();
				}
				cout << "Would you like to play again? (Press 1 for yes, 0 for no) ";
				int d3;
				cin >> d3;
				if(d3 == 1)
					h = 0;
				else 
					break;
			}
		}
		break;
	}
	/*for(int i = 0; i < m.get_size(); i++){
		for(int j = 0; j < m.get_size(); j++){
			cout << m.get_cave()[i][j].get_event().get_id() << " ";
		}
		cout << endl;
	}*/
	
	return 0;
}
