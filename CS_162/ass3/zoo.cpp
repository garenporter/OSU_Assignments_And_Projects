#include "./zoo.h"
/*Function Name: zoo
 * Description: Default constructor for zoo class
 * Parameters: nothing
 * Pre-conditions: zoo is made
 * Post-conditions: zoo members are initialized
 */
zoo::zoo(){
	ta = NULL;
	pa = NULL;
	ba = NULL;
	budget = 50000;
	num_tiger = 0;
	num_bear = 0;
	num_penguin = 0;
}

/*Function Name: get_ta
 * Description: accessor for tiger array
 * Parameters:none
 * Pre-conditions: none
 * Post-conditions:  none
 */
tiger* zoo:: get_ta(){
	return ta;
}

/*Function Name: get_pa
 * Description: accessor for penguin array
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
penguin* zoo::get_pa(){
	return pa;
}

/*Function Name: get_ba
 * Description: accessor for polar bear array
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
bear* zoo::get_ba(){
	return ba;
}

/*Function Name: get_num_tiger
 * Description: returns the number of current tigers
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int zoo::get_num_tiger(){
	return num_tiger;
}

/*Function Name: set_num_bear
 * Description: mutator for number of polar bears
 * Parameters: int number of polar bears
 * Pre-conditions: none
 * Post-conditions: num_bear data member is changed 
 */
void zoo::set_num_bear(int b){
	num_bear = b;
}

/*Function Name: set_num_penguin
 * Description: mutator for number of penguins
 * Parameters: int number of penguins 
 * Pre-conditions: none
 * Post-conditions: num_penguins data member is changed
 */
void zoo::set_num_penguin(int p){
	num_penguin = p;
}

/*Function Name: set_tiger
 * Description: mutator for tiger array, adds a tiger object to the array
 * Parameters: tiger object
 * Pre-conditions: none
 * Post-conditions: tiger array is one size bigger and has a new tiger object in it
 */
void zoo::set_tiger(tiger t){
	tiger *new_data = new tiger[num_tiger+1];
		for (int i = 0; i < num_tiger; i++) {
    			new_data[i] = ta[i];
  		}
  	if (ta != NULL) {
    		delete [] ta;
  	}	
  	new_data[num_tiger] = t;
 	num_tiger++;
  	ta = new_data;
	set_budget(budget - 10000);
}

/*Function Name: set_bear
 * Description: adds a bear object to the tiger array
 * Parameters: bear object
 * Pre-conditions: none
 * Post-conditions: bear array is one size bigger and has a new bear object in it
 */
void zoo::set_bear(bear b){
	bear *new_data = new bear[num_bear+1];
		for (int i = 0; i < num_bear; i++) {
    			new_data[i] = ba[i];
  		}
  	if (ba != NULL) {
    		delete [] ba;
  	}	
  	new_data[num_bear] = b;
 	num_bear++;
  	ba = new_data;
	set_budget(budget-5000);
}

/*Function Name: set_penguin
 * Description: adds a penguin object to the penguin array
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions:  penguin array is one size bigger and has a new penguin object in it.
 */
void zoo::set_penguin(penguin p){
	penguin *new_data = new penguin[num_penguin+1];
		for (int i = 0; i < num_penguin; i++) {
    			new_data[i] = pa[i];
  		}
  	if (pa != NULL) {
    		delete [] pa;
  	}	
  	new_data[num_penguin] = p;
 	num_penguin++;
  	pa = new_data;
	set_budget(budget-1000);
}

/*Function Name: set_budget
 * Description: mutator for budget data member
 * Parameters: int budget
 * Pre-conditions: none
 * Post-conditions: budget data member is changed
 */
void zoo::set_budget(int b){
	budget = b;
}

/*Function Name: get_budget 
 * Description: accessor for budget data member
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
int zoo::get_budget(){
	return budget;
}

/*Function Name: remove_tiger
 * Description: removes a tiger object from the tiger array and resizes the array
 * Parameters: index in tiger array
 * Pre-conditions: none
 * Post-conditions: array is one size less and a member is gone
 */
void zoo::remove_tiger(int idx) {
	tiger *new_data = new tiger[num_tiger-1];
	int insert_idx = 0;
  	for (int i = 0; i < num_tiger; i++) {
    		if (i != idx) {
      		new_data[insert_idx] = ta[i];
      		insert_idx++;
    		}
  	}	
	num_tiger--;
	delete [] ta; 
	ta = new_data;
}

/*Function Name: remove_bear
 * Description: removes a bear object from the bear array and resizes the array
 * Parameters: index in bear array
 * Pre-conditions: none
 * Post-conditions: array is one size smaller and a member is gone
 */
void zoo::remove_bear(int idx) {
	bear *new_data = new bear[num_bear-1];
	int insert_idx = 0;
  	for (int i = 0; i < num_bear; i++) {
    		if (i != idx) {
      		new_data[insert_idx] = ba[i];
      		insert_idx++;
    		}
  	}	
	num_bear--;
	delete [] ba; 
	ba = new_data;
}

/*Function Name: remove_penguin
 * Description: removes a penguin object from the penguin array and resizes the array
 * Parameters: index in penguin array
 * Pre-conditions: none
 * Post-conditions: penguin array is one size smaller and a member is gone
 */
void zoo::remove_penguin(int idx) {
	penguin *new_data = new penguin[num_penguin-1];
	int insert_idx = 0;
  	for (int i = 0; i < num_penguin; i++) {
    		if (i != idx) {
      		new_data[insert_idx] = pa[i];
      		insert_idx++;
    		}
  	}	
	num_penguin--;
	delete [] pa; 
	pa = new_data;
}

/*Function Name: t_at
 * Description: gets the tiger object at a specific place in the tiger array
 * Parameters: index in tiger array
 * Pre-conditions: none
 * Post-conditions: none
 */
tiger zoo::t_at(int i) const{
	return ta[i];
}

/*Function Name: b_at
 * Description: gets the bear object at a specific place in the bear array
 * Parameters: index in bear array
 * Pre-conditions: none
 * Post-conditions: none
 */
bear zoo::b_at(int i) const{
	return ba[i];
}

/*Function Name: p_at
 * Description: gets the penguin at a specific spot in the penguin array
 * Parameters: index in penguin array
 * Pre-conditions: none none
 * Post-conditions: 
 */
penguin zoo::p_at(int i) const{
	return pa[i];
}

/*Function Name: ~zoo
 * Description: destructor for animal arrays
 * Parameters: none
 * Pre-conditions: memory is dynamically allocated 
 * Post-conditions:  memory is freed
 */
zoo::~zoo(){
	delete [] ta;
	delete [] ba;
	delete [] pa;
}

/*Function Name: zoo
 * Description: copy constructor for zoo class
 * Parameters: address of zoo object
 * Pre-conditions: none
 * Post-conditions: new zoo object is initialized
 */
zoo::zoo(const zoo& other) {
	budget = other.budget;
	ta = new tiger[other.num_tiger];
	for(int i = 0; i < other.num_tiger; i++){
		ta[i] = other.t_at(i);
	}
	num_tiger = other.num_tiger;
	num_bear = other.num_bear;
	num_penguin = other.num_penguin;

		
	ba = new bear[other.num_bear];
	for(int i = 0; i < other.num_bear; i++){
		ba[i] = other.b_at(i);
	}

	pa = new penguin[other.num_penguin];
	for(int i = 0; i < other.num_penguin; i++){
		pa[i] = other.p_at(i);
	}
}

/*Function Name: operator=
 * Description: operator overload for zoo big three
 * Parameters: address of zoo object
 * Pre-conditions: none
 * Post-conditions: members of one zoo object is copied into another
 */
zoo& zoo::operator=(const zoo& other){
	delete [] ta;
	delete [] ba;
	delete [] pa;
	
	budget = other.budget;
	ta = new tiger[other.num_tiger];
	for(int i = 0; i < other.num_tiger; i++){
		ta[i] = other.t_at(i);
	}
	num_tiger = other.num_tiger;
	num_bear = other.num_bear;
	num_penguin = other.num_penguin;

		
	ba = new bear[other.num_bear];
	for(int i = 0; i < other.num_bear; i++){
		ba[i] = other.b_at(i);
	}

	pa = new penguin[other.num_penguin];
	for(int i = 0; i < other.num_penguin; i++){
		pa[i] = other.p_at(i);
	}
	return *this;
}

/*Function Name: get_starting_animals
 * Description: gets the initial animals the zoo keeper starts with
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions:  animals arrays are created and their members set
 */
void zoo::get_starting_animals(){
	cout << "You start with a budget of $50000. You must get your zoo off the ground, so you will choose one or two of each of the following animals: Tigers, Polar Bears, and Penguins" << endl;
	cout << endl;

	int t, b, p;

	cout << "How many tigers do you want to start with? They cost $10,000 ";
	cin >> t;
	
	cout << "How many polar bears do you want to start with? They cost $5,000. ";
	cin >> b;

	cout << "How many penguins do you want to start with? They cost $1,000. ";
	cin >> p;

	if(t==1){
		tiger t;
		set_tiger(t);
		get_ta()[0].set_age(3);
	}
	if(t==2){	
		tiger t, t2;
		set_tiger(t);
		set_tiger(t2);
		get_ta()[0].set_age(3);
		get_ta()[1].set_age(3);
	}

	if(b==1){
		bear b;
		set_bear(b);
		get_ba()[0].set_age(3);
	}
	if(b==2){	
		bear b, b2;
		set_bear(b);
		set_bear(b2);
		get_ba()[0].set_age(3);
		get_ba()[1].set_age(3);
	}

	if(p==1){
		penguin p;
		set_penguin(p);
		get_pa()[0].set_age(3);
	}
	if(p==2){	
		penguin p, p2;
		set_penguin(p);
		set_penguin(p2);
		get_pa()[0].set_age(3);
		get_pa()[1].set_age(3);
	}

}

/*Function Name: play_game
 * Description: plays the game
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 */
void zoo::play_game(){
	srand(time(NULL));
	int z = 1;
	while(z==1){
	cout << endl;
	cout << "It's a new day! First things first, the animals must be fed. You current budget before feeding the animals is " << budget << " and your new budget is ";
	cout << endl;
	int a = get_ta()[0].get_food_cost()*num_tiger;
	int b = get_ba()[0].get_food_cost()*num_bear;
	int c = get_pa()[0].get_food_cost()*num_penguin;
	set_budget(budget-(a+b+c));
	cout << budget <<endl;

	int r = rand()%4+1;
	
	if(r==1){
		int x = 1;
		while(x==1){
		cout << "An animal has gotten sick! Which species of animal will die (1 for tiger, 2 for polar bear, 3 for penguin)? ";
		int d;
		cin >> d;
		if(d == 1){
			if(num_tiger == 0){
				cout << "You have no tigers!" << endl;
				break;
			}
			int k = rand()%num_tiger;
			if(t_at(k).get_age() < 3){
				cout << "A baby tiger died." << endl;
				set_budget(budget - get_ta()[0].get_cost()*2);
				cout << "Your new budget is " << get_budget() << endl;
				num_tiger--;
			}
			else{
				cout <<"An adult tiger dies" << endl;
				set_budget(budget-get_ta()[0].get_cost());
				remove_tiger(k);
				cout << "Your new budget is " << get_budget() << endl;
				num_tiger--;
				x = 0;
			}
		}
			
		if(d == 2){
			if(num_bear == 0){
				cout << "You have no polar bears!" << endl;
				break;
			}
			int k = rand()%num_bear;
			if(b_at(k).get_age() < 3){
				cout << "A baby polar bear died." << endl;
				set_budget(budget - get_ba()[0].get_cost()*2);
				cout << "Your new budget is " << get_budget() << endl;
				num_bear--;
			}
			else{
				cout <<"An adult polar bear died" << endl;
				set_budget(budget-get_ba()[0].get_cost());
				remove_bear(k);
				cout << "Your new budget is " << get_budget() << endl;
				num_bear--;
				x = 0;
			}
		}
			
		if(d == 3){
			if(num_penguin == 0){
				cout << "You have no penguins!" << endl;
				break;
			}
			int k = rand()%num_penguin;
			if(p_at(k).get_age() < 3){
				cout << "A baby penguin died." << endl;
				set_budget(budget - get_pa()[0].get_cost()*2);
				num_penguin--;
				cout << "Your new budget is " << get_budget() << endl;
			}
			else{
				cout <<"An adult penguin dies" << endl;
				set_budget(budget-get_pa()[0].get_cost());
				remove_penguin(k);
				cout << "Your new budget is " << get_budget() << endl;
				x = 0;
				num_penguin--;
			}
		}	
		}
		
			
	}
	
	if(r==2){
		cout << "There is a tiger boom! Each tiger recieves a bonus payoff of ";
		int h = rand()%250+251;	
		cout << h << endl;
		for(int i = 0; i<num_tiger; i++){
			get_ta()[i].set_payoff(get_ta()[i].get_payoff()+h);
		}
		cout << endl;
	}
	if(r==3){
		int y = 1;
		while(y==1){
		cout << "An animal is gon have a baby! Which animal would you like to have a baby? Tigers(press 1) have 1 baby. Polar bears (press 2) have 2 babies. Penguins (press 3) have three babies. ";
		int t;
		cin >> t;
		if(t==1){
			for(int i = 0; i < num_tiger; i++){
				if(get_ta()[i].get_age() >= 3){
					tiger t;
					set_tiger(t);
					cout << "A baby tiger was born!" << endl;
					set_budget(budget+10000);
					num_tiger++;
					y = 0;
					break;
				}
			cout << "There is not a tiger old enough to have a baby." << endl;
			}
		}

		if(t==2){
			for(int i = 0; i < num_bear; i++){
				if(get_ba()[i].get_age() >= 3){
					bear t, t2;
					set_bear(t);
					set_bear(t2);
					cout << "Two baby polar bears were born!" << endl;
					set_budget(budget+10000);
					set_num_bear(num_bear+2);
					y = 0;
					break;
				}
			cout << "There is not a polar bear old enough to have a baby." << endl;
			}
		}

		if(t==3){
			for(int i = 0; i < num_penguin; i++){
				if(get_pa()[i].get_age() >= 3){
					penguin t, t2, t3;
					set_penguin(t);
					set_penguin(t2);
					set_penguin(t3);
					cout << "Three baby penguins were born!" << endl;
					set_budget(budget+3000);
					set_num_penguin(num_penguin + 3);
					y = 0;
					break;
				}
			cout << "There is not a penguin old enough to have a baby." << endl;
			}
		}

		}
	}
	if(r==4){
		cout << "Nothing out of the ordinary happened today."<<endl;
	}
	for(int i = 0; i < num_tiger; i++){	
		if(get_ta()[i].get_age() < 3)
			set_budget(budget+2000);
		if(get_ta()[i].get_age() >=3)
			set_budget(budget+1000);
			
	}
	for(int i =0; i < num_bear; i++){
		if(get_ba()[i].get_age() < 3)
			set_budget(budget + 500);
		if(get_ba()[i].get_age() >= 3)
			set_budget(budget + 250);
	}
	for(int i = 0; i < num_penguin; i++){
		if(get_pa()[i].get_age() < 3)
			set_budget(budget+100);
		if(get_pa()[i].get_age() >=3)
			set_budget(budget+50);
	}
	cout << "After the payoff your budget is " << budget << endl;
	if(budget < 0){
		cout << "You are bankrupt and your zoo has run aground! You lose!" << endl;
		break;
	}
	cout << "Would you like to quit the game? (1 for yes, 0 for no) ";
	int e;
	cin >> e;
	if(e==1)
		break;
	cout << "Would you like to buy an adult tiger(1), adult polar bear(2), or adult penguin(3), or nothing(4)? ";
	int f;
	cin >> f;
	if(f==1){
		tiger t;
		t.set_age(3);
		set_tiger(t);
	}
	if(f==2){
		bear b;
		b.set_age(3);
		set_bear(b);
	}
	if(f==3){
		penguin p;
		p.set_age(3);
		set_penguin(p);
	}
	cout << "It's time to move on to the next turn..."<<endl;
	cout << endl;
	for(int i = 0; i<num_tiger; i++){
		get_ta()[i].set_age(get_ta()[i].get_age()+1);
	}
	
	for(int i = 0; i<num_bear; i++){
		get_ba()[i].set_age(get_ba()[i].get_age()+1);
	}
	for(int i = 0; i<num_penguin; i++){
		get_pa()[i].set_age(get_pa()[i].get_age()+1);
	}
	

}
}
	































