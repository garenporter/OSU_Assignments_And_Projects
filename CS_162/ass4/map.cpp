#include "./map.h"
#include <ctime>
#include<cstdlib>
#include "./player.h"

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

map::map(){
	w_x = 0;
	w_y = 0;
	size = 0;
	cave = NULL;
	w_dead = false;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::set_size(int s){
	size = s;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

bool map::get_w_dead(){
	return w_dead;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::set_w_dead(bool w){
	w_dead = w;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

int map::get_size(){
	return size;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

room**& map::get_cave(){
	return cave;
}
/*Function Name: set_cave
 *  16  * Description: creates cave
 *   17  * Paremters: size of cave
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: cave is made
 *      20  */

void map::set_cave(int s){
	cave = new room*[s];
	srand(time(NULL));

	for(int i =0; i < s; i++){
		cave[i] = new room[s];
		for(int j = 0; j<s; j++){
			nothing n;
			cave[i][j].set_event(n);
		}
	}
	for(int j = 0; j < 2; j++){
		int x = 1;
		while(x == 1){
			int temp1 = rand()%(s);
			int temp2 = rand()%(s);
			if(cave[temp1][temp2].get_event().get_id() != 'n'){
				x = 1;
			}
			else{
				pit p;
				cave[temp1][temp2].set_event(p);
				x = 0;
			}
		}
	}	

	for(int j = 0; j < 2; j++){
		int x = 1;
		while(x == 1){
			int temp1 = rand()%(s);
			int temp2 = rand()%(s);
			if(cave[temp1][temp2].get_event().get_id() != 'n'){
				x = 1;
			}
			else{
				bats p;
				cave[temp1][temp2].set_event(p);
				x = 0;
			}
		}
	}
	
	for(int j = 0; j < 1; j++){
		int x = 1;
		while(x == 1){
			int temp1 = rand()%(s);
			int temp2 = rand()%(s);
			if(cave[temp1][temp2].get_event().get_id() != 'n'){
				x = 1;
			}
			else{
				wumpus p;
				cave[temp1][temp2].set_event(p);
				set_w_y(temp2);
				set_w_x(temp1);
				x = 0;
			}
		}
	}

	for(int j = 0; j < 1; j++){
		int x = 1;
		while(x == 1){
			int temp1 = rand()%(s);
			int temp2 = rand()%(s);
			if(cave[temp1][temp2].get_event().get_id() != 'n'){
				x = 1;
			}
			else{
				gold p;
				cave[temp1][temp2].set_event(p);
				x = 0;
			}
		}
	}	






	
}
/*Function Name: ~map
 *  16  * Description: deconstructor
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: cave is deleted
 *      20  */

map::~map(){
	for(int i=0; i<size; i++){
		delete []cave[i];
	}
	delete []cave;
}
/*Function map
 *  16  * Description: copy constructor 
 *   17  * Paremters: map object
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

map::map(map& other){
	size = other.get_size();
	cave = new room*[other.get_size()];
	for(int i = 0; i < other.get_size(); i++){
		cave[i] = new room[other.get_size()];
		for(int j = 0; j < other.get_size(); j++){
			cave[i][j] = other.get_cave()[i][j];
		}
	}
	w_x = other.w_x;
	w_y = other.w_x;
	w_dead = other.w_dead;
}
/*Function Name: operator=
 *  16  * Description: operator overload
 *   17  * Paremters: map object
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

map& map::operator=(map& other){
	size = other.get_size();
	cave = new room*[other.get_size()];
	for(int i = 0; i < other.get_size(); i++){
		cave[i] = new room[other.get_size()];
		for(int j = 0; j < other.get_size(); j++){
			cave[i][j] = other.get_cave()[i][j];
		}
	}
	w_dead = other.w_dead;
	w_x = other.w_x;
	w_y = other.w_y;
	return *this;
}
/*Function Name: check_adj_event
 *  16  * Description: checkes event of room and prints appropriate message
 *   17  * Paremters: player position
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::check_adj_event(int x, int y){
	if(room_event_id(x, y) == 'p')
		cout << cave[x][y].get_event().get_adj_message()<<endl;
	if(room_event_id(x,y) == 'g')
		cout << cave[x][y].get_event().get_adj_message()<<endl;
	if(room_event_id(x,y) == 'w')
		cout <<cave[x][y].get_event().get_adj_message()<<endl;
	if(room_event_id(x,y) == 'b')
		cout << cave[x][y].get_event().get_adj_message()<<endl;
}
player p;
/*Function Name: check_adj
 *  16  * Description: checks adjecent rooms to player
 *   17  * Paremters: player position
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::check_adj(int x, int y){
	if(x==0 and y == 0){
		check_adj_event(x+1,y);
		check_adj_event(x,y+1);
		cout << "You can move South(press 3), or East(press 2), or shoot(press 5)"<<endl;	
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==3 or d==2 or d == 5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
		
	}
	if(x==0 and (y!=0 and y != size-1)){
		check_adj_event(x+1,y);
		check_adj_event(x,y+1);
		check_adj_event(x,y-1);
		cout << "You can move East(press 2), or South(press 3), or West(press 4), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==3 or d==2 or d==4 or d == 5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d==4){
			p.set_y_pos(p.get_y_pos()-1);
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
	}
	if(x==0 and y == size-1){
		check_adj_event(x,y-1);
		check_adj_event(x+1,y);
		cout << "You can move South(press 3), or West(press 4), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==3 or d==4 or d == 5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
		if(d == 4){
			p.set_y_pos(p.get_y_pos()-1);
		}
	}
	if(y == size-1 and (x != 0 and x != size-1)){
		check_adj_event(x,y-1);
		check_adj_event(x-1,y);
		check_adj_event(x+1,y);
		cout << "You can move North(press 1), or South(press 3), or West(press 4) or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==1 or d==3 or d==4 or d ==5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d==4){
			p.set_y_pos(p.get_y_pos()-1);
		}
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
	}
	if(x == size-1 and y == size-1){
		check_adj_event(x-1,y);
		check_adj_event(x,y-1);
		cout << "You can move North(press 1), or West(press 4), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==1 or d==4 or d==5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 4){
			p.set_y_pos(p.get_y_pos()-1);
		}
	}
	if(x == size-1 and (y != 0 and y != size -1)){
		check_adj_event(x,y+1);
		check_adj_event(x,y-1);
		check_adj_event(x-1,y);
		cout << "You can move North(press 1), or East(press 2), or West(press 4), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==1 or d==2 or d==4 or d == 5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d==4){
			p.set_y_pos(p.get_y_pos()-1);
		}
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
	}
	if(x == size-1 and y == 0){
		check_adj_event(x-1,y);
		check_adj_event(x,y+1);
		cout << "You can move North(press 1), or East(press 2), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==1 or d==2 or 5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
	}
	if(y == 0 and (x != 0 and x != size-1)){
		check_adj_event(x+1,y);
		check_adj_event(x-1,y);
		check_adj_event(x,y+1);
		cout << "You can move North(press 1), or East(press 2), or South(press 3), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==3 or d==2 or d==1 or d==5)
				break;
			else
				d=0;
		}
		
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
	}
	if(x != 0 and x != size-1 and y != 0 and y != size-1){
		check_adj_event(x+1,y);
		check_adj_event(x-1,y);
		check_adj_event(x,y+1);
		check_adj_event(x,y-1);
		cout << "You can move North(press 1), or East(press 2), or South(press 3), or West(press 4), or shoot(press 5)" << endl;
		int d = 0;
		while(d == 0){
			cin >> d;
			if(d==3 or d==2 or d == 1 or d == 4 or d==5)
				break;
			else
				d=0;
		}
		if(d==5){
			char s;
			cout << "What direction do you want to shoot in?(North, n)(East, e)(South, s)(West, w)  ";
			cin >> s;
			if(s == 'n')
				shoot(p.get_x_pos(), p.get_y_pos(), 'n');
			if(s == 'e')
				shoot(p.get_x_pos(), p.get_y_pos(), 'e');
			if(s == 's')
				shoot(p.get_x_pos(), p.get_y_pos(), 's');
			if(s == 'w')
				shoot(p.get_x_pos(), p.get_y_pos(), 'w');
		}
			
		if(d == 1){
			p.set_x_pos(p.get_x_pos()-1);
		}
		if(d == 4){
			p.set_y_pos(p.get_y_pos()-1);
		}
		if(d == 3){
			p.set_x_pos(p.get_x_pos()+1);
		}
		if(d == 2){
			p.set_y_pos(p.get_y_pos()+1);
		}
	}
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

char map::room_event_id(int x, int y){
	return cave[x][y].get_event().get_id();
}
/*Function Name: shoot
 *  16  * Description: shoots an arrow three rooms over
 *   17  * Paremters: position of player and direction
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: arrows decremented and wumpus may be killed or moved
 *      20  */

void map::shoot(int x, int y, char d){
	if(d=='n'){
		for(int i = 0; i < 3; i++){
			if(x-i-1 > 0){
				if(room_event_id(x-i-1,y) == 'w'){
					cout << "You killed the wumpus!" << endl;
					w_dead = true;
					nothing n;
					cave[x-i-1][y].set_event(n);
					p.set_num_arrows(p.get_num_arrows()-1);
					cout << "You only have "<<p.get_num_arrows()<<" arows left..."<<endl;
				}
			}
		/*	else{
			 	p.set_num_arrows(p.get_num_arrows()-1);
				cout << "You only have "<<p.get_num_arrows()<<" left..."<<endl;
			}*/
		}
	}
		
	if(d=='e'){
		for(int i = 0; i < 3; i++){
			if(y+i+1 < size){
				if(room_event_id(x,y+i+1) == 'w'){
					cout << "You killed the wumpus!" << endl;
					w_dead = true;
					nothing n;
					cave[x][y+i+1].set_event(n);
					p.set_num_arrows(p.get_num_arrows()-1);
					cout << "You only have "<<p.get_num_arrows()<<" arrows left..."<<endl;
				}
			}
	/*	else{
			 p.set_num_arrows(p.get_num_arrows()-1);
			cout << "You only have "<<p.get_num_arrows()<<" l    eft..."<<endl;
		}*/
	}
	}
	
	if(d=='s'){
		for(int i = 0; i < 3; i++){
			if(x+i+1 < size){
				if(room_event_id(x+i+1,y) == 'w'){
					cout << "You killed the wumpus!" << endl;
					w_dead = true;		
					nothing n;
					cave[x+i+1][y].set_event(n);
					p.set_num_arrows(p.get_num_arrows()-1);
					cout << "You only have "<<p.get_num_arrows()<<" arrows left..."<<endl;
				}
			}
	/*	else{
		 	p.set_num_arrows(p.get_num_arrows()-1);
			cout << "You only have "<<p.get_num_arrows()<<" l    eft..."<<endl;
		}*/
		}
	}
	
	if(d=='w'){
		for(int i = 0; i < 3; i++){
			if(y-i-1 > 0){
				if(room_event_id(x,y-i-1) == 'w'){
					cout << "You killed the wumpus!" << endl;
					w_dead = true;
					nothing n;
					cave[x][y-i-1].set_event(n);
					p.set_num_arrows(p.get_num_arrows()-1);
					cout << "You only have "<<p.get_num_arrows()<<" arrows left..."<<endl;
				}
			}
		
		//	else{
		//		 p.set_num_arrows(p.get_num_arrows()-1);
		//		cout << "You only have "<<p.get_num_arrows()<<" l    eft..."<<endl;
		//	}
		}
	}
	if(w_dead != true){
		int r = rand()%3;
		if(r==0 or r==1 or r==2){
			nothing n;
			cave[get_w_x()][get_w_y()].set_event(n);
			int l = 0;
			while(l==0){
				int x = rand()%size;
				int y = rand()%size;
				if(room_event_id(x,y) == 'n'){
					wumpus w;
					cave[x][y].set_event(w);
					cout << "You missed and awoke the wumpus and it has moved to a different room!" << endl;
					break;
				}
			}
		}
		p.set_num_arrows(p.get_num_arrows()-1);
		cout << "You only have " << p.get_num_arrows() << " arrows left..." << endl;
	}
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::set_w_x(int x){
	w_x = x;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void map::set_w_y(int y){
	w_y = y;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

int map::get_w_x(){
	return w_x;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

int map::get_w_y(){
	return w_y;
}
/*Function Name: play_game
 *  16  * Description: plays the game
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


void map::play_game(){
	int f = 0;
	while(f==0){
		int x = rand()%size;
		int y = rand()%size;
		if(room_event_id(x ,y) == 'n'){
			p.set_start_x(x);
			p.set_start_y(y);
			p.set_x_pos(x);
			p.set_y_pos(y);
			break;
		}
	}
	int g = 0;
	while(g==0){
	//	cout << p.get_x_pos() << " " << p.get_y_pos() << endl;
		
		if(room_event_id(p.get_x_pos(), p.get_y_pos()) == 'w'){
			cout << cave[p.get_x_pos()][p.get_y_pos()].get_event().get_event_message() << endl;
			break;
		}
		if(room_event_id(p.get_x_pos(), p.get_y_pos()) == 'p'){
			cout << cave[p.get_x_pos()][p.get_y_pos()].get_event().get_event_message() << endl;
		break;
		}
		if(room_event_id(p.get_x_pos(), p.get_y_pos()) == 'g'){
			cout << cave[p.get_x_pos()][p.get_y_pos()].get_event().get_event_message() << endl;
		p.set_have_gold(true);
		nothing n;
		cave[p.get_x_pos()][p.get_y_pos()].set_event(n);
		}
		if(room_event_id(p.get_x_pos(), p.get_y_pos()) == 'b'){
			cout << cave[p.get_x_pos()][p.get_y_pos()].get_event().get_event_message() << endl;
			int x = rand()%size;
			int y = rand()%size;
			p.set_x_pos(x);
			p.set_y_pos(y);
		}
		check_adj(p.get_x_pos(), p.get_y_pos());
		if(get_w_dead()==true and p.get_have_gold()==true and p.get_x_pos()==p.get_start_x() and p.get_y_pos()==p.get_start_y()){
			cout << "You win and your quest is complete! Congratulations!" << endl;
			break;
		}
		if(p.get_num_arrows() == 0 and w_dead != true){
			cout << "You ran out of arrows and now stand no chance against the wumpus! You lose!" << endl;
			break;
		}	
	}
	p.set_num_arrows(3);
}

















