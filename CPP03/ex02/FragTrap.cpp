#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("Default")
{
	this->_hit_points = 100;
	this->_energy_points = 100;
	this->_attack_damage = 30;
	std::cout	<< "FragTrap " << _name << " default constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	_hit_points = 100;
	_energy_points = 100;
	_attack_damage = 30;
	std::cout	<< "FragTrap " << _name << " parametrized constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap()
{
	*this = other;
	std::cout	<< "FragTrap " << _name << " copy constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &other)
{
	if (this != &other)
	{
		_name = other._name;
		_hit_points = other._hit_points;
		_energy_points = other._energy_points;
		_attack_damage = other._attack_damage;
	}
	std::cout	<< "FragTrap " << _name << " copy assignment operator called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap " << _name << " destructor called." << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << _name << " requests high fives! Let's do it!" << std::endl;
}
