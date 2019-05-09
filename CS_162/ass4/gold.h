#include "./event.h"
#pragma once

class gold :public event {
	public:
		gold();

		string get_event_message();

		string get_adj_message();
		char get_id();

};
