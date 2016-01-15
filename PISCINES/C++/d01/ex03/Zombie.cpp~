// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 18:53:53 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:17:37 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

std::string randomName()
{
	std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string name;

	for (unsigned int i = 0; i < (rand() % 50 + 5); i++)
		name += chars[rand() % (chars.length() - 1)];
	return (name);
}

Zombie::Zombie(void) : _name(randomName()) {
	std::cout << "A new zombie named '" << _name << "' has been created" << std::endl;
}

Zombie::~Zombie(void) {
	std::cout << this->_name << " died ..." << std::endl;
}

void Zombie::announce(void) {
	std::cout << '<' << this->_name << "> Braiiiiiiinnnnnssss..." << std::endl;
}
