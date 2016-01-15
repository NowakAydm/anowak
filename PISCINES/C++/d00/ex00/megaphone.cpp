#include <iostream>
#include <string>

int		main ( int ac, char *av[] ) {

	int x = 0;

	while (++x < ac)
	{
		for (int i = 0; char c = av[x][i]; ++i)
		{
			c = toupper( c );
			std::cout << c;
		}
	}
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	std::cout << std::endl;

	return (0);
}
