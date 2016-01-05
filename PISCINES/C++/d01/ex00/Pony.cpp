// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Pony.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/05 18:43:40 by anowak            #+#    #+#             //
//   Updated: 2016/01/05 19:58:06 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Pony.hpp"

Pony::Pony( std::string name ) : _name(name) {
	std::cout << "A lil' baby pony has born ! Shall he be called '" << this->_name << "' forever ..." << std::endl;
}

Pony::~Pony(void) {
	std::cout << "Oh noo ... " << this->_name << " just died ... Well, whos hungry ? :)" << std::endl;
}

void Pony::doSomeStuff(void) {
	std::cout << this->_name << " is frolicking joyfully in the fields" << std::endl;
}
