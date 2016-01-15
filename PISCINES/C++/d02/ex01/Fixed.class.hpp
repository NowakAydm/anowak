#ifndef FIXED_CLASS_HPP
#define FIXED_CLASS_HPP

#include <iostream>

class	Fixed	{

private :
	int					_Value;
	const static int	_FractionalBits = 8;

public :
	const static char			verbose = 1;

	Fixed ( void );
	Fixed ( const Fixed & ref );
	~Fixed ( void );
	int		getRawBits ( void ) const ;
	void	setRawBits ( int raw );
	Fixed&	operator= ( const Fixed & f );
};


#endif
