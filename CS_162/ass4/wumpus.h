#include "./event.h"
#pragma once

class wumpus :public event{
	public:
		wumpus();

		string get_event_message();

		string get_adj_message();

		char get_id();
};
