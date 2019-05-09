#include "./bear.h"

/*Function Name: bear
 * Description: default constructor for bear class
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: bear data members are initialized 
 */
bear::bear() :animal(){
	cost = 5000;
	num_animal = 0;
	food_cost = 600;
	payoff = 250;
	age = 0;
}
