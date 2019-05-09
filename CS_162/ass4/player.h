

class player {
	private: 
		int num_arrows;
		bool have_gold;
		int x_pos;
		int y_pos;
		int start_x;
		int start_y;

	public:
		player();
		int get_num_arrows();
		bool get_have_gold();
		int get_x_pos();
		int get_y_pos();
		int get_start_x();
		int get_start_y();

		void set_num_arrows(int);
		void set_have_gold(bool);
		void set_x_pos(int);
		void set_y_pos(int);
		void set_start_x(int);
		void set_start_y(int);

};
