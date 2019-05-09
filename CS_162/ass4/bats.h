#include "./event.h"
#pragma once

class bats :public event {
	public:
		bats();

		string get_event_message();

		string get_adj_message();

		char get_id();
};
