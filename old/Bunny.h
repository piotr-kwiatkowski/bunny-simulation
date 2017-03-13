#pragma once
#include <iostream>
#include <cstdlib> // rand
#include <list>
#include <vector>

class Bunny
{
public:
	std::string getName();
	std::string setSex();
	int getAge();
    void setOneMoreYear();
	void getAll(); // POTRZEBNE ?
    void setNamesList();
	std::vector<std::string> namesList;

	Bunny();
	~Bunny();

private:
    std::string name;
	std::string sex;
	int age;
};
