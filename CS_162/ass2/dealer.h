#include "./hand.h"
#pragma once

class dealer {
	private:
		hand d_hand;
		int card_total;
		
	public:
		dealer();
		
		hand& get_d_hand();

		int get_card_total();

		void set_card_total(int);
};
