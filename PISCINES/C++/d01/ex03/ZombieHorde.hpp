// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieHorde.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 19:54:27 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:12:51 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ZOMBIEHORDE_HPP
#define ZOMBIEHORDE_HPP

#include "Zombie.hpp"
#include <iostream>
#include <string>

class ZombieHorde {

private:
	Zombie*		 _Horde;
	unsigned int _size;

public:
			ZombieHorde( int N );
			~ZombieHorde( void );
	void	announce( void );
};

#endif
