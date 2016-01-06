// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieEvent.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:03:32 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 19:38:14 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ZOMBIEEVENT_HPP
#define ZOMBIEEVENT_HPP

#include <iostream>
#include <string>
#include <stdlib.h>
#include "Zombie.hpp"

class ZombieEvent {

private:
	std::string	_type;

public:
			ZombieEvent( void );
			~ZombieEvent( void );
	void	setZombieType( std::string type );
	Zombie* newZombie( std::string name );
	void	randomChump( void );
};

#endif
