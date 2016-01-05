// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Pony.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/05 18:44:12 by anowak            #+#    #+#             //
//   Updated: 2016/01/05 19:01:54 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PONY_HPP
# define PONY_HPP

#include <iostream>
#include <string>

class Pony {

private:
	std::string _name;

public:
	Pony(std::string name);
	~Pony(void);
	void doSomeStuff(void);
};

#endif
