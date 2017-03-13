#ifndef BUNNY_H
#define BUNNY_H

#include <string>

class Bunny
{
public:
	// ctor
	Bunny(std::string a_name, std::string a_sex, std::string a_color, int a_age, bool a_mutant);
	
	std::string getName();
	std::string getSex();
	std::string getColor();
	int getAge();
	bool getIsRadioactiveVampireMutant();


private:
	std::string name;
	std::string sex;
	std::string color;
	int age;
	bool isRadioactiveVampireMutant;
};

#endif  /* BUNNY_H */