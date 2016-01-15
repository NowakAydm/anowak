// 02 class

#include <iostream>
#include "Sample.Class.hpp"

Samplé::Sample2(char p1, int p2, float p3) : a1(p1), a2(p2), a3(p3)
{
	std::cout << ">> Constructor called" << std::endl;

	std::cout << "a1 =" << this->a1 << std::endl;
	std::cout << "a2 =" << this->a2 << std::endl;
	std::cout << "a3 =" << this->a3 << std::endl;

	return;
}

Sample2::~Sample2(void)
{
	std::cout << "<< Detructor called" << std::endl;
	return;
}

void Sample::bar(void)
{
	std::cout << "-- bar called" << std::endl;
	return;
}
