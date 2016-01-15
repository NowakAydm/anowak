#include <iostream>
#include <string>
#include "Contact.Class.hpp"

Contacts::Contacts( void ) {
	std::cout << ">> Contact CONSTRUCTOR CALLED" << std::endl;
	Contacts::_contactNb++;
	std::cout << "-- This is the ";
	std::cout << Contacts::_contactNb << "nth contact." << std::endl;

	std::string(this->first_name);
	std::string(this->last_name);
	std::string(this->nickname);
	std::string(this->login);
	std::string(this->adress);
	std::string(this->email);
	std::string(this->phone);
	std::string(this->birthday);
	std::string(this->fav_meal);
	std::string(this->underwear);
	std::string(this->secret);
}

Contacts::~Contacts ( void ) {
	std::cout << "<< Contact DESTRUCTOR CALLED" << std::endl;
}

void	Contacts::add_a_contact( void ) {
	std::cout << "---- ADD A CONTACT ----" << std::endl;
	std::cout << "Enter FIRST NAME : ";
	std::cin >> this->first_name;
	std::cout << "Enter LAST NAME : ";
	std::cin >> this->last_name;
	std::cout << "Enter NICKNAME : ";
	std::cin >> this->nickname;
	std::cout << "Enter LOGIN : ";
	std::cin >> this->login;
	std::cout << "Enter ADRESS : ";
	std::cin >> this->adress;
	std::cout << "Enter EMAIL : ";
	std::cin >> this->email;
	std::cout << "Enter PHONE : ";
	std::cin >> this->phone;
	std::cout << "Enter BIRTHDAY : ";
	std::cin >> this->birthday;
	std::cout << "Enter FAVORITE MEAL : ";
	std::cin >> this->fav_meal;
	std::cout << "Enter UNDERWEAR COLOR : ";
	std::cin >> this->underwear;
	std::cout << "Enter DARKEST SECRET : ";
	std::cin >> this->secret;
	return;
}

int Contacts::getContactNb ( void ) const {
	return (this->_contactNb);
}

int		Contacts::_contactNb = 0;
