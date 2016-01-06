// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 18:53:53 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 19:30:40 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Zombie.hpp"

Zombie::Zombie(std::string type, std::string name) : _type(type), _name(name) {
	std::cout << "A new '" << type << "' zombie named '" << name << "' has been created" << std::endl;
}

Zombie::~Zombie(void) {
	std::cout << this->_name << " died ..." << std::endl;
}

void Zombie::announce(void) {
	std::cout << '<' << this->_name << " (" << this->_type << ")> Braiiiiiiinnnnnssss..." << std::endl;
}
