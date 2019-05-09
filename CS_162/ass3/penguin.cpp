#include "./penguin.h"

/*Function Name: penguin
 * Description: defualy constructor for penguin class
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: penguin members are initialized
 */
penguin::penguin() :animal() {
	cost = 1000;
	num_animal = 0;
	food_cost = 200;
	payoff = 50;
	age = 0;
}
