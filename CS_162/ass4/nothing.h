#include "./event.h"
#pragma once

class nothing :public event{
	public:
		nothing();
		
		char get_id();
};	
