#include "./hand.h"
#include "./card.h"
/*Function: hand
 *   6  * Description: hand delfault constructor
 *     7  * Paremeters: sets num_cards to 0
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

hand::hand(){
	//cards = ;
	num_cards = 0;
}
/*Function: set_Card
 *   6  * Description: puts a card in hand
 *     7  * Paremeters: hand position and card
 *       8  * Post-cond: hand is populated
 *         9  * Pre-Cond: none
 *          10  */

void hand::set_card(const int nc, const card c){
	cards[nc] = c;
	
}
/*Function:get_Cards
 *   6  * Description: accessor for cards in hand
 *     7  * Paremeters: none
 *       8  * Post-cond: none
 *         9  * Pre-Cond: none
 *          10  */

card * hand::get_cards() {
	return cards;
}

/*void hand::create_cards(const int nc){
	cards = new card[nc];
	
}*/
/*Function: get_num_cards
 *   6  * Description: accessor for num cards
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

int hand::get_num_cards() const{
	return num_cards;
}
/*
hand::hand(const hand &c){
	//cards = new card[c.num_cards];
	cards = c.cards;
	num_cards = c.num_cards;
}

hand::~hand(){
	delete [] cards;
}

void hand::operator=(const hand &c){
	delete [] cards;
	cards = c.cards;
	num_cards = c.num_cards;
}
*/

	
