#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>

Base* generate(void)
{
	Base* res;
	
	srand(time(NULL));
	int	randint = rand() % 3 + 1;
	switch (randint)
	{
		case (1):
		{
			res = new A();
			std::cout << "Generated object A\n";
			break;
		}
		case (2):
		{
			res = new B();
			std::cout << "Generated object B\n";
			break;
		}
		case (3):
		{
			res = new C();
			std::cout << "Generated object C\n";
			break;
		}
	}
	return (res);
}

void identify(Base* p)
{
	(void)p;
	std::cout << "Identify pointer\n";
}

void identify(Base& p)
{
	(void)p;
	std::cout << "Identify reference\n";
}
