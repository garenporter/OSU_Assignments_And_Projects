#include "./card.h"
#pragma once

class deck {
	private:
		card cards[52];
		int num_cards;
		int deck_pos;
	public:
		deck(); // default constructor
	//	deck(card*, int); // constructor
		
		//accessors
		card * get_cards();
		int get_num_cards();
		
		//mutators	
		void set_cards(card*);
		void set_num_cards(int);
	
		void shuffle(card *); // shuffle function

		void set_deck_pos(int);

		card remove_top_card();
};
