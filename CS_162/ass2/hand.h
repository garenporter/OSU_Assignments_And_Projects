#include <cstdlib>
#include "./card.h"
#pragma once

class hand{
	private:
		card cards[9];
		int num_cards;
	public:
		hand(); // default constructor
		void set_card(const int, const card); // mutator
		card * get_cards() ; // accessor for cards
		void create_cards(const int); // creates card array
		int get_num_cards()const; // accessor for num_cards
	//	hand(const hand &); // copy constructor
	//	~hand(); // destructor
	//	void operator=(const hand &); // assignment operator overload
};
