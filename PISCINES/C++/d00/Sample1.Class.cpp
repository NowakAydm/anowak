// 02 class

#include <iostream>
#include "Sample1.Class.hpp"

Sample1::Sample1(char p1, int p2, float p3)
{
	std::cout << ">> Constructor called" << std::endl;

	this->a1 = p1;
	std::cout << "a1 =" << this->a1 << std::endl;
	this->a2 = p2;
	std::cout << "a2 =" << this->a2 << std::endl;
	this->a3 = p3;
	std::cout << "a3 =" << this->a3 << std::endl;

	return;
}

Sample1::~Sample1(void)
{
	std::cout << "<< Detructor called" << std::endl;
	return;
}

void Sample::bar(void)
{
	std::cout << "-- bar called" << std::endl;
	return;
}
