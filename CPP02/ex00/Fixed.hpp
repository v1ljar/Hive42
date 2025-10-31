#pragma once

class Orthodox{
	private:
		int	value;
		static const int	nbr_frac_bits;
	public:
		Orthodox();
		~Orthodox();
		int getRawBits( void ) const;
		void setRawBits( int const raw );
};