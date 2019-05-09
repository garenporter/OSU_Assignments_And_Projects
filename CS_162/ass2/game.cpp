#include "./game.h"
#include "./deck.h"
#include <iostream>

deck d;
/*Function: game
 *   6  * Description: default constructor for game class
 *     7  * Paremeters: none
 *       8  * Post-cond: cards will be a complete deck, player array will be NULL, num players will be 0
 *         9  * Pre-Cond: none
 *          10  */

game::game(){
	cards = d;
	players = NULL;
//	game_dealer = de;
	num_players = 0;
}
/*Function: set_players
 *   6  * Description: creates player array 
 *     7  * Paremeters: int number of players 
 *       8  * Post-cond: players is an empty array
 *         9  * Pre-Cond: none
 *          10  */

void game::set_players(int n){ // takes num_players
	set_num_players(n);
	players = new player[n];
}
/*Function: set_num_players
 *   6  * Description: sets the total number of players 
 *     7  * Paremeters: int number of players
 *       8  * Post-cond: num_players is changed
 *         9  * Pre-Cond:none
 *          10  */

void game::set_num_players(int n){
	num_players = n;
}
/*Function:game
 *   6  * Description: game copy constructor 
 *     7  * Paremeters: const game class object
 *       8  * Post-cond: the game object is coppied
 *         9  * Pre-Cond: players array was created
 *          10  */

game::game(const game &c){
	players = c.players;
	num_players = c.num_players;
	cards = c.cards;
}
/*Function: operator=
 *   6  * Description: operator overload for players array
 *     7  * Paremeters: const game class object
 *       8  * Post-cond: players is deleted and things are coppied
 *         9  * Pre-Cond: players array was created
 *          10  */

void game::operator=(const game &c){
	delete [] players;
	players = c.players;
	num_players = c.num_players;
	cards = c.cards;
}
/*Function: ~game
 *   6  * Description: destructor for game class
 *     7  * Paremeters: none
 *       8  * Post-cond: players array is freed
 *         9  * Pre-Cond: none
 *          10  */

game::~game(){
	delete [] players;
}
/*Function:get_players
 *   6  * Description: accessor for player array
 *     7  * Paremeters: none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

player* game::get_players(){
	return players;
}
/*Function: play_game
 *   6  * Description: plays the game itself. that master function
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

void game::play_game(){
	d.shuffle(d.get_cards());	
 	cout<<"How much money is each player starting with? ";
	int pt;
	cin>>pt;
	for(int i = 0; i < num_players; i++){ // set playing total
		players[i].set_playing_total(pt);
	}
	int h = 1;
	while(h == 1){
	for(int i = 0; i<num_players; i++){ // deal cards
		players[i].get_p_hand().set_card(0, d.remove_top_card());
		players[i].get_p_hand().set_card(1, d.remove_top_card());
		}
	
	for(int i = 0; i < num_players; i++){ // set bets
		int g = 1;
		while(g == 1){
			cout<<"player "<< i+1 <<", how much would you like to bet? ";
			int b;
			cin>>b;
			if(b > players[i].get_playing_total())
				g = 1;
			else
				g = 0;
				players[i].set_bet(b);
		}
	}
	cout<<endl;
	// cout << "before2 " << players[1].get_p_hand().get_cards()[2].value << " " << players[1].get_p_hand().get_cards()[1].value << endl;
	cout<<"The deck has been shuffled and the game is ready to be played, player one will play first."<<endl;
	for(int j = 0; j<num_players; j++){ // display hands
		cout<<"Player "<<j+1<<" is holding: ";
		cout<<players[j].get_p_hand().get_cards()[0].value<< " of "<< players[j].get_p_hand().get_cards()[0].suit<<" and a ";
		cout<<players[j].get_p_hand().get_cards()[1].value<< " of "<< players    [j].get_p_hand().get_cards()[1].suit<<endl;
	}
	cout << endl;
//cout << "before " << players[1].get_p_hand().get_cards()[0].value << " " << players[1].get_p_hand().get_cards()[1].value << endl;	
// check for 11-13	
	for(int i = 0; i < num_players; i++){
		
		if(players[i].get_p_hand().get_cards()[0].value >=10 and players[i].get_p_hand().get_cards()[0].value <= 13){
                          players[i].get_p_hand().get_cards()[0].value = 10;
                }
 
                if(players[i].get_p_hand().get_cards()[1].value >=10 and players[i].get_p_hand().get_cards()[1].value <= 13){
                          players[i].get_p_hand().get_cards()[1].value = 10;
                }
	//	cout << players[1].get_p_hand().get_cards()[0].value << " " << players[1].get_p_hand().get_cards()[1].value << endl;
                players[i].set_card_total(players[i].get_p_hand().get_cards()[0].value +  players[i].get_p_hand().get_cards()[1].value);
	}
//	cout << players[1].get_card_total() << endl;
	for(int i = 0; i < num_players; i++){ // play each turn
		cout << endl;
		cout<<"Player " <<  i+1 << "'s turn..."<<endl;
		cout << endl;
	//	cout << "card total " << players[i].get_card_total() << endl;

		if((players[i].get_p_hand().get_cards()[0].value == 1 or players[i].get_p_hand().get_cards()[1].value == 1) and ((players[i].get_p_hand().get_cards()[0].value >=10 and players[i].get_p_hand().get_cards()[0].value <= 13) or (players[i].get_p_hand().get_cards()[1].value >= 10 and players[i].get_p_hand().get_cards()[1].value <= 13))){
			cout<<"Blackjack!!! You win your bet!"<<endl;
			players[i].set_card_total(21);
		//	players[i].set_playing_total(players[i].get_playing_total() + players[i].get_bet());
		}
		else{
			int t = 1;
			while(t == 1){
				cout << "card total " << players[i].get_card_total() << endl;
				if(players[i].get_card_total() > 21){
					cout << "You bust! You lose your bet!" << endl;
					break;
				}
				cout<<"Would you like to hit(1) or stay(2)? ";
				int dec;
				cin>> dec;
				if(dec == 2){
					break;
				}
				if(dec==1){
					players[i].get_p_hand().set_card(i+2, d.remove_top_card());
					cout << "You recieved a " << players[i].get_p_hand().get_cards()[i+2].value <<" of " << players[i].get_p_hand().get_cards()[i+2].suit << endl;
					 if(players[i].get_p_hand().get_cards()[i+2].value >=10 and players[i].get_p_hand().get_cards()[i+2].value <= 13){
 			                         players[i].get_p_hand().get_cards()[i+2].value = 10;
					}
					 players[i].set_card_total(players[i].get_card_total() + players[i].get_p_hand().get_cards()[i+2].value);
					// cout << players[i].get_card_total() << endl;
					
				}
			}
		}
	}
//below is dealer ai

	game_dealer.get_d_hand().set_card(0, d.remove_top_card());  
        game_dealer.get_d_hand().set_card(1, d.remove_top_card());
	
	cout << "The dealer was dealt a ";

	cout<<game_dealer.get_d_hand().get_cards()[0].value<< " of "<< game_dealer.get_d_hand().get_cards()[0].suit<<" and a ";
        cout<<game_dealer.get_d_hand().get_cards()[1].value<< " of "<< game_dealer.get_d_hand().get_cards()[1].suit<<endl;
	cout << endl;
	 if((game_dealer.get_d_hand().get_cards()[0].value == 1 or game_dealer.get_d_hand().get_cards()[1].value == 1) and ((game_dealer.get_d_hand().get_cards()[0].value >=10 and game_dealer.get_d_hand().get_cards()[0].value <= 13) or (game_dealer.get_d_hand().get_cards()[1].value >= 10 and game_dealer.get_d_hand().get_cards()[1].value <= 13))){
		cout << "The dealer was dealt a blackjack" << endl;
		game_dealer.get_d_hand().get_cards()[0].value = 20;
		game_dealer.get_d_hand().get_cards()[1].value = 1;
		
		
	}
	else if(game_dealer.get_d_hand().get_cards()[0].value >=10 and game_dealer.get_d_hand().get_cards()[0].value <= 13){
                          game_dealer.get_d_hand().get_cards()[0].value = 10;
        }
        if(game_dealer.get_d_hand().get_cards()[1].value >=10 and game_dealer.get_d_hand().get_cards()[1].value <= 13){
                          game_dealer.get_d_hand().get_cards()[1].value = 10;
        }

        game_dealer.set_card_total(game_dealer.get_d_hand().get_cards()[0].value +  game_dealer.get_d_hand().get_cards()[1].value);
	
	int i = 0;
	while(game_dealer.get_card_total() < 17){
		game_dealer.get_d_hand().set_card(i+2, d.remove_top_card());
                cout << "The dealer recieved a " << game_dealer.get_d_hand().get_cards()[i+2].value <<" of " << game_dealer.get_d_hand().get_cards()[i+2].suit << endl;
               
		 if(game_dealer.get_d_hand().get_cards()[i+2].value >=10 and game_dealer.get_d_hand().get_cards()[i+2].value <= 13){
                	game_dealer.get_d_hand().get_cards()[i+2].value = 10;
                }
                game_dealer.set_card_total(game_dealer.get_card_total() + game_dealer.get_d_hand().get_cards()[i+2].value);
		if(game_dealer.get_card_total() > 21){
                        cout << "The dealer busted!" << endl;
			game_dealer.set_card_total(0);
                        break;
		}
		i++;
	}
	cout << endl;
//	cout << players[0].get_card_total()<<endl;
//	cout << players[1].get_card_total() << endl;
//	cout << game_dealer.get_card_total() << endl;
	for(int j = 0; j < num_players; j++){
		if(players[j].get_card_total() < game_dealer.get_card_total() or players[j].get_card_total() > 21){
			cout <<"Player " << j+1 <<" lost to the dealer. They lose there bet" << endl;
			players[j].set_playing_total(players[j].get_playing_total()- players[j].get_bet());
		}
		else if(players[j].get_card_total() == game_dealer.get_card_total()){
			cout << "Player " << j+1 << " tied with the dealer. The bet is kept" << endl;
		}
		else if(players[j].get_card_total() > game_dealer.get_card_total()){
			cout <<"Player " << j+1 <<" beat the dealer. The player wins their bet"<<endl;
			players[j].set_playing_total(players[j].get_playing_total() + players[j].get_bet());
		}
	}
	cout << endl;
	for(int j = 0; j < num_players; j++){
		cout << "Here are the current playing totals for the players:"<<endl;
		cout << "Player " << j+1 << " has " << players[j].get_playing_total() << " dollars" << endl;
	}
	cout << "Play another round? ";
	string a;
	cin >> a;
	if(a == "yes"){
		h = 1;
	}
	else{
		h = 0;
	}
	}
}












