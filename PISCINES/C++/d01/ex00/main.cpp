// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/05 18:43:06 by anowak            #+#    #+#             //
//   Updated: 2016/01/05 19:55:29 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Pony.hpp"

void	ponyOnTheStack( void ){
	Pony bob = Pony("Bob");

	bob.doSomeStuff();
	return;
}

void	ponyOnTheHeap( void ){
	Pony * jimmy = new Pony("Jimmy");

	(*jimmy).doSomeStuff();
	delete jimmy;
	return;
}

int		main( void ) {
	ponyOnTheStack();
	std::cout << std::endl;
	ponyOnTheHeap();;

	return (0);
}
