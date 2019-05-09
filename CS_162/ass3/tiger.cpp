#include "./tiger.h"

/*Function Name: tiger
 * Description: default constructor for tiger class
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: tiger members are initialized
 */
tiger::tiger() :animal(){
	bonus = 0;
	cost = 10000;
	food_cost = 1000;
	num_animal = 0;
	payoff = 1000;
	age = 0;
}

/*Function Name: get_bonus
 * Description: accessor for tiger bonus
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions:  none
 */
int tiger::get_bonus(){
	return bonus;
}

/*Function Name: set_bonus
 * Description: mutator for bonus member
 * Parameters: new tiger bonus
 * Pre-conditions: none
 * Post-conditions: bonus data member is changed
 */
void tiger::set_bonus(int b){
	bonus = b;
}

