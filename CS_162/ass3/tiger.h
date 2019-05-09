#include "./animal.h"
#pragma once


class tiger : public animal {
	protected:
		int bonus;
	public:
		tiger();
		
		int get_bonus();

		void set_bonus(int);

};
