#pragma once
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Bunny
{
public:
	enum ESex {male = 0, female};
	int sex;
	int age = 0;
	bool rmvb = false; // radioactive_mutant_vampire_bunny

public:
	void printAge();
	void changeAge();
	void printAll();

	Bunny(int, int, bool);
};