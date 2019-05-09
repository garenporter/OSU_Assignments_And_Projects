#include "./bats.h"
/*Function Name: bats
 *  16  * Description: default constructor for bats class
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */


bats::bats() :event() {
	this -> event_message = "The super bats suround you and pick you up! You are flown to a new room!";
	this -> adj_message = "You hear wings flapping...";
	id = 'b';
}
/*Function Name: get_event_message
 *  16  * Description: accessor for get_event_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string bats::get_event_message(){
	return this -> event_message;
}
/*Function Name: getadj_message
 *  16  * Description: accessor for get_adj_message
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


string bats::get_adj_message(){
	return this -> adj_message;
}
/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */


char bats::get_id(){
	return this -> id;
}
