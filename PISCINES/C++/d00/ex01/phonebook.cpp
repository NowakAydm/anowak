#include <iostream>
#include <string.h>
#include "Contact.Class.hpp"

void	print_phonebook( Contacts tab[8] ) {
	int x = 0;

	while (std::strlen( tab[x].first_name ))
		
	return;
}

int		main( void ) {

	char		str[10];
	Contacts	tab[8];
	int			i = 0;

	std::cout << "....xxxx****   AWESOME PHONEBOOK 4000   ****xxxx...." << std::endl;
	std::cout << " \\/                                              \\/" << std::endl;
	std::cout << " ||       -   ADD    - add a contact             ||" << std::endl;
	std::cout << " ||       -   SEARCH - search a contact          ||" << std::endl;
	std::cout << " ||       -   EXIT   - exit program              ||" << std::endl;
	std::cout << " /\\                                              /\\" << std::endl;
	std::cout << "****xxxx....................................xxxx****" << std::endl;
	std::cout << "Your choice : ";
	std::cin >> str;

	while ( strcmp( str, "EXIT" ) )
	{
		if ( !strcmp( str, "ADD" ) )
		{
			tab[i++].add_a_contact();
			std::cout << "---- Added as contact n°" << i << " ----" << std::endl;
		}
		else if ( !strcmp( str, "SEARCH" ) )
			std::cout << "---- SEARCH IN PHONEBOOK ----" << std::endl;
		else
			std::cout << "This is not a valid answer." << std::endl;
		
		std::cout << "Your choice : ";
		std::cin >> str;
	}

	return (0);
}
