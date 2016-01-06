// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieEvent.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:03:45 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:14:18 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent(void) {
	std::cout << "A new ZombieEvent class has been created" << std::endl;
}

ZombieEvent::~ZombieEvent(void) {
	std::cout << "A ZombieEvent has been destroyed" << std::endl;
}

void	ZombieEvent::setZombieType(std::string type) {
	this->_type = type;
	std::cout << "The next Zombies will be of the type '" << this->_type << "'" << std::endl;
}

Zombie* ZombieEvent::newZombie(std::string name) {
	return (new Zombie(this->_type, name));
}

char randomChar()
{
	std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	return (chars[rand() % (chars.length() - 1)]);
}

void ZombieEvent::randomChump( void ) {
	std::string name;
	Zombie *random;

	for (unsigned int i = 0; i < (rand() % 50 + 5); i++)
		name += randomChar();
	random = newZombie(name);
	random->announce();
	delete random;
	return;
}
