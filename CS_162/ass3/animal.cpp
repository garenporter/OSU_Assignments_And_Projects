#include "./animal.h"

/*Function Name: animal
 * Description: default constructor for animal class
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: data members are initialized 
 */
animal::animal(){
//	exhibit = NULL;
	cost = 0;
	num_animal = 0;
	food_cost = 0;
	payoff = 0;
}
/*
int* animal::get_exhibit(){
	return exhibit;
}
*/

/*Function Name: get_age
 * Description: accessor for animal ages
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int animal::get_age(){
	return age;
}

/*Function Name: get_cost
 * Description: accessor for animal cost
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int animal::get_cost(){
	return cost;
}

/*Function Name: get_num_animal
 * Description: accessor for number of animals
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int animal::get_num_animal(){
	return num_animal;
}

/*Function Name: get_food_cost
 * Description: accessor for animal food cost
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */

int animal::get_food_cost(){
	return food_cost;
}

/*Function Name: get_payoff
 * Description: accessor for animal payoff
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int animal::get_payoff(){
	return payoff;
}
/*
void animal::set_exhibit(int a){
	int* b = new int[a];
	exhibit = b;
}
*/

/*Function Name: set_age
 * Description: mutator for age data member
 * Parameters: age of animal
 * Pre-conditions: none
 * Post-conditions: age member is changed
 */
void animal::set_age(int a){
	age = a;
}

/*Function Name: set_cost
 * Description: mutator for animal cost
 * Parameters: cost of animal
 * Pre-conditions: none
 * Post-conditions: cost member is changed
 */
void animal::set_cost(int c){
	cost = c;
}

/*Function Name: set_num_animal
 * Description: mutator for number of animals
 * Parameters: number of animals
 * Pre-conditions: none
 * Post-conditions: num_animal member changed
 */
void animal::set_num_animal(int n){
	num_animal = n;
}

/*Function Name: set_food_cost
 * Description: mutator for food cost member
 * Parameters: food cost for animal
 * Pre-conditions: none
 * Post-conditions: food_cost data member changed
 */
void animal::set_food_cost(int f){
	food_cost = f;
}

/*Function Name:set_payoff
 * Description: mutator for payoff member
 * Parameters: animal payoff
 * Pre-conditions: none
 * Post-conditions: payoff member is changed
 */
void animal::set_payoff(int p){
	payoff = p;
}
/*
animal::~animal(){
	delete [] exhibit;
}

animal::animal(const animal &obj){
	cost = obj.cost;
	num_animal = obj.num_animal;
	food_cost = obj.food_cost;
	payoff = obj.payoff;
	exhibit = obj.exhibit;
}

void animal::operator =(const animal &obj){
	 cost = obj.cost;
         num_animal = obj.num_animal;
         food_cost = obj.food_cost;
         payoff = obj.payoff;
         exhibit = obj.exhibit;
	 delete [] exhibit;
}
*/

