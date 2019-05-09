#include "./room.h"
#include "./wumpus.h"
#include "./gold.h"
#include "./pit.h"
#include "./bats.h"
#include "./nothing.h"

class map {
	private:
		int size;
		room** cave;
		bool w_dead;
		int w_x;
		int w_y;
	public:

		map();
		
		void set_w_x(int);

		void set_w_y(int);
		
		int get_w_x();
	
		int get_w_y();

		void shoot(int, int, char);

		bool get_w_dead();
	
		void set_w_dead(bool);
		
		void set_size(int);
	
		int get_size();

		void set_cave(int);

		room**& get_cave();

		char room_event_id(int, int);
		
		void check_adj(int, int);
	
		void check_adj_event(int, int);

		void play_game();

		~map();

		map(map& other);

		map& operator=(map& other);
};
