#include "./event.h"
#pragma once

class pit : public event {
	public:
		pit();
		
		string get_event_message();
	
		string get_adj_message();
		char get_id();
};
