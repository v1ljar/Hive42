#pragma once

#include <iostream>
#include <cmath>

class Fixed{
	private:
		int	_value;
		static const int	_nbr_frac_bits = 8;
	public:
		Fixed();
		Fixed(Fixed &other);
		Fixed& operator=(const Fixed &other);
		~Fixed();
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};