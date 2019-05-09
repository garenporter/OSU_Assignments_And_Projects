#include "./pit.h"

/*Function Name: pit
 *  16  * Description: default constructor for pit class
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */

pit::pit() :event(){
	this -> event_message = "You fell in a bottomless pit! You died and were unable to complete your quest!";

	this -> adj_message = "You feel a breeze...";

	id = 'p';
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

string pit::get_event_message(){
	return this -> event_message;
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

string pit::get_adj_message(){
	return this -> adj_message;
}	

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

char pit::get_id(){
	return id;
}
