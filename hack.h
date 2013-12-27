#ifndef _HACK_H_
#define _HACK_H_

typedef int StatPoint;

class Person{
	protected:
		StatPoint strength;
		StatPoint attack;
		StatPoint defense;
		StatPoint vitality;
		bool is_fighting;

	public:
		Person();

		void set_fighting(bool fight);
};

#endif
