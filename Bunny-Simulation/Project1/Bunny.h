#pragma once

class Bunny
{
	enum ESex {male, female};
	int age;
	bool rmvb;// radioactive_mutant_vampire_bunny

public:
	void printName(Bunny *oBunny);

	Bunny();
	~Bunny();
};