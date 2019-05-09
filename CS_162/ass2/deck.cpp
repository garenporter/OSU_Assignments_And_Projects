#include "./deck.h"
#include <iostream>

/*Function: deck
 *   6  * Description: default constructor for deck class
 *     7  * Paremeters: none
 *       8  * Post-cond: deck_pos is 0 and num_cards is 52
 *         9  * Pre-Cond: none
 *          10  */


deck::deck(){ // default constructor
	deck_pos = 0;	
	num_cards = 52;;
	
	int j = 1;
	int k = 0;
	for(int i = 0; i<13; i++){
		
		cards[k].value = j;
		cards[k].suit = "clubs";
		
		cards[k+1].value = j;
		
		cards[k+1].suit = "hearts";
		cards[k+2].value = j;
		cards[k+2].suit = "spades";
		
		cards[k+3].value = j;
		cards[k+3].suit = "diamonds";
	
		k+=4;
		j++;
  	}	
}
/*Function: get_cards
 *   6  * Description: accessor for card array
 *     7  * Paremeters: none
 *       8  * Post-cond: none
 *         9  * Pre-Cond: none
 *          10  */

card * deck::get_cards(){ // card array accessor
	return cards;

}
/*Function: set_deck_pos
 *   6  * Description: changed position is the deck
 *     7  * Paremeters: current deck position
 *       8  * Post-cond: deck position is changed
 *         9  * Pre-Cond: none
 *          10  */

void deck::set_deck_pos(int dp){
	deck_pos = dp;
}
/*Function: shuffle
 *   6  * Description: shuffles the deck
 *     7  * Paremeters: card array
 *       8  * Post-cond: deck is shuffled
 *         9  * Pre-Cond: none
 *          10  */

void deck::shuffle(card * c){
	srand(time(NULL));

	for(int i = 0; i<1000; i++){
		int r = rand() % 52;
		int q = rand() % 52;
		card temp = c[q];
		card temp2 = c[r];
		c[r] = temp;
		c[q] = temp2;
	}
	/*for(int i = 0; i<51 ; i++){
			int x = rand()%1000+1;
			cout<<x<<endl;
		for(int j = 0; j<x; j++){
			card temp = c[i];
			c[i] = c[i+1];
			c[i+1] = temp;
		}
	}*/

}
/*Function: remove_top_card
 *   6  * Description: removes top card of deck and reshuffles if need be
 *     7  * Paremeters: none
 *       8  * Post-cond: deck pos is changed
 *         9  * Pre-Cond: none
 *          10  */

card deck::remove_top_card(){
	if(deck_pos == 52){
		cout << "reshuffling deck..."<<endl;
		shuffle(cards);
		deck_pos = 0;
}
	
	set_deck_pos(deck_pos+1);
	return cards[deck_pos-1];
	
}			

	
