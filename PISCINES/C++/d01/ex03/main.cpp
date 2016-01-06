// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:14:29 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:20:49 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"
#include "ZombieHorde.hpp"

int		main() {
	ZombieHorde *Horde = new ZombieHorde(10);
	delete Horde;
	ZombieHorde *Hor2 = new ZombieHorde(2);
	Hor2->announce();
	delete Hor2;
	ZombieHorde *Hor0 = new ZombieHorde(0);
	delete Hor0;
	return (0);
}
