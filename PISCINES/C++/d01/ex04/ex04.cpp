// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ex04.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: anowak <anowak@student.42.fr>              +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/06 20:22:01 by anowak            #+#    #+#             //
//   Updated: 2016/01/06 20:28:32 by anowak           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>

int	main() {
	std::string Hi = "HI THIS IS BRAIN";

	std::string* ptr = &Hi;
	std::string& ref = Hi;

	std::cout << "Showing ptr : " << *ptr << std::endl;
	std::cout << "Showing ref : " << ref << std::endl;
	return (0);
}
