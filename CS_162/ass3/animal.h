#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#pragma once

using namespace std;

class animal{
	protected:
		//int *exhibit;
		int age;
		int cost;
		int num_animal;
		int food_cost;
		int payoff;
	public:
		animal();
		int* get_exhibit();
		int get_cost();
		int get_num_animal();
		int get_food_cost();
		int get_payoff();
		int get_age();	

		void set_age(int);
		void set_exhibit(int);
		void set_cost(int);
		void set_num_animal(int);
		void set_food_cost(int);
		void set_payoff(int);
/*
		~animal();
		animal(const animal &);
		void operator =(const animal &);
*/
};
