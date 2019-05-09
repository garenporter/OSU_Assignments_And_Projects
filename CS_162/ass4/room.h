#include "./event.h"
#pragma once

class room {
	private:
		event e;
		
	public:

		event get_event();
		void set_event(event);

};
