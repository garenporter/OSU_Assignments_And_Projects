#include "./gold.h"
/*Function Name: gold
 *  16  * Description: default constructor for gold class
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */


gold::gold() :event() {
	this -> event_message = "You picked up the gold!";
	this -> adj_message = "You see a glimmer nearby...";
	id = 'g';
}
/*Function Name: get_event_message
 *  16  * Description: accessor for get_event_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string gold::get_event_message(){
	return this -> event_message;
}
/*Function Name: get_adj_message
 *  16  * Description: accessor for get_adj_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string gold::get_adj_message(){
	return adj_message;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


char gold::get_id(){
	return id;
}

