#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name) {};

void	HumanB::attack()
{
	if (weapon)
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
	else
		std::cout << name << " has no weapon!" << std::endl;
}

void	HumanB::setWeapon(Weapon &club)
{
	weapon = &club;
}