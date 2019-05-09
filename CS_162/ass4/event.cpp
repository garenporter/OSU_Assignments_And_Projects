#include "./event.h"

/*Function Name: event
 *  16  * Description: default constructor for event class
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */

event::event(){
	this -> event_message = "";
	this -> adj_message = "";
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

string event::get_event_message() {
	return event_message;
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

string event::get_adj_message() {
	return adj_message;
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

char event::get_id(){
	return id;
}
