#pragma once

#include <iostream>
#include <cmath>

class Fixed{
	private:
		int	_value;
		static const int	_nbr_frac_bits = 8;
	public:
		Fixed();
		Fixed(const int nbr);
		Fixed(const float float_nbr);
		Fixed(const Fixed &other);
		Fixed& operator=(const Fixed &other);
		~Fixed();
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;
};

std::ostream& operator<<(std::ostream& output,const Fixed &nbr);
