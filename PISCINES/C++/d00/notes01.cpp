// 01 stdio streams

#include <iostream>

int main (void)
{

	char buff[10];

	std::cout << "Hello World :)" << std::endl;

	std::cout << "Input: ";
	std::cin >> buff;
	std::cout << "OUtput: " << buff << std::endl;

	return (0);
}
