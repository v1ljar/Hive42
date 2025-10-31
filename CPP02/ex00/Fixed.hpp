#pragma once

#include <iostream>

class Fixed{
	private:
		int	value;
		static const int	nbr_frac_bits = 8;
	public:
		Fixed();
		Fixed(Fixed &old);
		Fixed &operator=(const Fixed &old);
		~Fixed();
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};