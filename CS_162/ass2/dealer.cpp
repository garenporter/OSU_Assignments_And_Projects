#include "./dealer.h"

hand h1;

/*Function: dealer
 * Description: Constructor for dealer class
 * Paremeters:none
 * Post-cond:d_hand is given empty hand and card_total is set to 0
 * Pre-Cond:None
 */

dealer::dealer(){
	d_hand = h1;
	card_total = 0;
}

/*Function: get_d_hand
 *   6  * Description: accessor for d_hand
 *     7  * Paremeters: none
 *       8  * Post-cond: none
 *         9  * Pre-Cond: none
 *          10  */


hand& dealer::get_d_hand(){
	return d_hand;
} 
/*Function:get_Card_total
 *   6  * Description:accessor for card_total
 *     7  * Paremeters:none
 *       8  * Post-cond:none
 *         9  * Pre-Cond:none
 *          10  */

int dealer::get_card_total(){
	return card_total;
}
/*Function:set_card_total
 *   6  * Description:mutator for card_total
 *     7  * Paremeters:int card total
 *       8  * Post-cond:card_total is changed
 *         9  * Pre-Cond:none
 *          10  */

void dealer::set_card_total(int ct){
	card_total = ct;
}


