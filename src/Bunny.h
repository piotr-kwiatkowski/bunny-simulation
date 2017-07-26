#ifndef BUNNY_H
#define BUNNY_H

#include <string>

class Bunny
{
public:
	// constructor
	Bunny(std::string a_name, std::string a_sex, std::string a_color, int a_age, bool a_mutant);
	
    // getters
	std::string getName();
	std::string getSex();
	std::string getColor();
	int         getAge();
	bool        getIsRadioactiveVampireMutant();

    void incrementAge();


private:
	std::string m_name;
	std::string m_sex;
	std::string m_color;
	int         m_age;
	bool        m_isRadioactiveVampireMutant;
};

#endif  /* BUNNY_H */