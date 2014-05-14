#pragma once
#ifndef _BUNNY_H_
#define _BUNNY_H_

#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Bunny
{
//public:
	
	int sex;
	int age = 0;
	bool rmvb = false; // radioactive_mutant_vampire_bunny

public:
	void printAge();
	void changeAge();
	void printAll();

	enum ESex { male = 0, female };

	//Bunny(int, int, bool);
};
#endif // _BUNNY_H_