#include "./player.h"
#include "./hand.h"

hand h;
/*Function: player
 *   6  * Description: default constructor for player class
 *     7  * Paremeters: none
 *       8  * Post-cond: p_hand gets an empty hand, playing total = 0, card_total = 0, bet = 0
 *         9  * Pre-Cond: none
 *          10  */

player::player(){
	p_hand = h;
	playing_total = 0;
	card_total = 0;
	bet = 0;
}
/*Function:get_p_hand
 *   6  * Description: accessor for get_p_hand
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

hand& player::get_p_hand(){
	return p_hand;
}
/*Function:set_card_total
 *   6  * Description:mutator for total hand value
 *     7  * Paremeters: new card total
 *       8  * Post-cond: card total is changed
 *         9  * Pre-Cond: none
 *          10  */

void player::set_card_total(int ct){
	card_total = ct;
}
/*Function:get_playing_total
 *   6  * Description:accessor for playing_total
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

int player::get_playing_total(){
	return playing_total;
}
/*Function:get_card_total
 *   6  * Description:accessor for card_total
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

int player::get_card_total(){
	return card_total;
}
/*Function:get_bet
 *   6  * Description: accessor for bet
 *     7  * Paremeters: none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

int player::get_bet(){
	return bet;
}
/*Function:set_playing_total
 *   6  * Description:mutator for playing_total
 *     7  * Paremeters:int new playing total
 *       8  * Post-cond:playing total is changed
 *         9  * Pre-Cond:none
 *          10  */

void player::set_playing_total(int p){
	playing_total = p;
}
/*Function:set_bet
 *   6  * Description:mutator for bet
 *     7  * Paremeters:new bet
 *       8  * Post-cond: bet is changed
 *         9  * Pre-Cond: none
 *          10  */

void player::set_bet(int b){
	bet = b;
}
