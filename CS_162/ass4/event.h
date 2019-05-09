#include <iostream>
#pragma once

using namespace std;

class event {
	protected:
		string event_message;
		string adj_message;
		char id;
	public:
		event();
		virtual string get_event_message();
		virtual string get_adj_message();
		virtual char get_id();
};
