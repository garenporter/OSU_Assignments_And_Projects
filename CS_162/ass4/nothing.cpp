#include "./nothing.h"

/*Function Name: nothing
 * Description: Default constructor for nothing class
 * Paremters: None
 * Pre-conditions: None
 * Post-conditions: members are initialized
 */
nothing::nothing() :event() {
	event_message = "There is nothing significant in this room";
	adj_message = "";
	id = 'n';
}

/*Function Name: get_id
 * Description: accessor for get_id
 * Paremters: None
 * Pre-conditions: None
 * Post-conditions: none
 */
char nothing::get_id(){
	return id;
}
