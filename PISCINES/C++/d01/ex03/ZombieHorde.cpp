// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieHorde.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:54:38 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:12:30 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int N) :_size(N) {
	this->_Horde = new Zombie[N];
	std::cout << "A new horde of " << N << " zombies has been created" << std::endl;
}

ZombieHorde::~ZombieHorde(void) {
	delete [] this->_Horde;
	std::cout << "The horde has died ..." << std::endl;
}

void ZombieHorde::announce(void) {
	for (unsigned int i = 0; i < this->_size; ++i)
		this->_Horde[i].announce();
}
