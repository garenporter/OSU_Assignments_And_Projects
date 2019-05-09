#include "./wumpus.h"
/*Function Name: wumpus
 *  16  * Description: default constructor for wumpus class
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */



wumpus::wumpus() :event(){
	this -> event_message = "You've awoken the wumpus and immediantly find yourself being eaten! You lose and did not complete your quest!";

	this -> adj_message = "You smell a terrible stench";

	id = 'w';
}
/*Function Name: get_event_message
 *  16  * Description: accessor for get_event_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string wumpus::get_event_message(){
	return this -> event_message;
}
/*Function Name: get_event_message
 *  16  * Description: accessor for get_event_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string wumpus::get_adj_message(){
	return this -> adj_message;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

char wumpus::get_id(){
	return id;
}
