#include "./hand.h"
#pragma once


class player {
	private:
		hand p_hand;
		int playing_total;
		int card_total;
		int bet;
	public:

		player();

		hand& get_p_hand();

		int get_playing_total();

		int get_card_total();

		int get_bet();

		void set_playing_total(int);

		void set_bet(int);

		void set_card_total(int);

};
