#include "./room.h"
/*Function Name: room
 *  16  * Description: default constructor for room
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: members are initialized
 *      20  */

event room::get_event(){
	return e;
}

/*Function Name: get_id
 *  16  * Description: accessor for get_id
 *   17  * Paremters: None
 *    18  * Pre-conditions: None
 *     19  * Post-conditions: none
 *      20  */

void room::set_event(event e1) {
	e = e1;
}
