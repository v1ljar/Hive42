#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main()
{
	Base* og = generate();

	identify(og);
	identify(*og);
	return (0);
}