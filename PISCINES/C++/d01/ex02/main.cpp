// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:14:29 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 19:51:47 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"
#include "ZombieEvent.hpp"


int		main() {
	ZombieEvent Event;
	Zombie		*z;

	Event.setZombieType("normal");
	z = Event.newZombie("Bob");
	z->announce();
	delete z;
	std::cout << std::endl;
	Event.randomChump();
	std::cout << std::endl;
	z = new Zombie("jumper", "Davis");
	z->announce();
	delete z;
	std::cout << std::endl;
	Event.randomChump();
	Event.randomChump();
	std::cout << std::endl;
	return (0);
}
