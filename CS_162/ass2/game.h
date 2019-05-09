#include "./card.h"
#include "./player.h"
#include "./deck.h"
#include "./dealer.h"


class game{
	private:
		deck cards;
		player *players;
		dealer game_dealer;
		int num_players;
	public:
		void set_num_players(int);

		game();

		player* get_players();

		void set_players(int);

		void set_cards(deck);

		game(const game &c);

		void operator=(const game &c);

		~game();

		void play_game();
};
