#include "./tiger.h"
#include "./bear.h"
#include "./penguin.h"

class zoo {
	protected:
		tiger * ta;
		penguin * pa;
		bear * ba;
		int budget;
		int num_tiger;
		int num_bear;
		int num_penguin;
	public:
		zoo();

		tiger* get_ta();
		penguin* get_pa();
		bear* get_ba();
		int get_budget();
		int get_num_tiger();
		int get_num_bear();
		int get_num_penguin();

		void set_num_tiger(int);
		void set_num_bear(int);
		void set_num_penguin(int);
		void set_tiger(tiger);
		void set_bear(bear);
		void set_penguin(penguin);
		void set_budget(int);

		void remove_tiger(int);
		void remove_bear(int);
		void remove_penguin(int);

		tiger t_at(int) const;
		bear b_at(int) const;
		penguin p_at(int) const;

		~zoo();
		zoo(const zoo&);
		zoo& operator=(const zoo&);
		
		void get_starting_animals();
		void play_game();
};
