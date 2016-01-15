#include "Fixed.Class.hpp"

Fixed::Fixed(void) : _Value(0) {
	if (verbose)
		std::cout << ">> Fixed constructor has been called" << std::endl;
	return;
}

Fixed::Fixed(const Fixed & ref) {
	if (verbose)
		std::cout << ">> Fixed copy constructor has been called" << std::endl;

	*this = ref;
	return;
}

Fixed::~Fixed (void){
	if (verbose)
		std::cout << "<< Fixed destructor has been called" << std::endl;
	return;
}

int			Fixed::getRawBits (void) const {
	if (verbose)
		std::cout << "-- getRawBits has been called" << std::endl;
	return (this->_Value);
}

void		Fixed::setRawBits (int const raw){
	this->_Value = raw;
	return;
}

Fixed&		Fixed::operator= (const Fixed & f){
	if (verbose)
		std::cout << "-- Fixed assignation operator has been called" << std::endl;

	if (&f == this)
		return (*this);
	this->_Value = f.getRawBits();
	return (*this);
}
