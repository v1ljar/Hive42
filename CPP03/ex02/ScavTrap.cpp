#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	this->_name = "Default";
	this->_hit_points = 100;
	this->_energy_points = 50;
	this->_attack_damage = 20;
	std::cout	<< "ScavTrap " << _name << " default constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	_hit_points = 100;
	_energy_points = 50;
	_attack_damage = 20;
	std::cout	<< "ScavTrap " << name << " parametrized constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	*this = other;
	std::cout	<< "ScavTrap " << _name << " copy constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	if (this != &other)
		ClapTrap::operator=(other);
	std::cout	<< "ScavTrap " << _name << " copy assignment operator called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and attack damage is " \
				<< _attack_damage << "." << std::endl;
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << _name << " destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
	if (!_hit_points)
		std::cout << "ScavTrap " << _name << " is dead already!" << std::endl;
	else if (!_energy_points)
		std::cout << "ScavTrap " << _name << " has no energy to attack!" << std::endl;
	else
	{
		_energy_points--;
		std::cout	<< "ScavTrap " << _name << " attacks " << target << ", causing "
					<< _attack_damage << " points of damage!\n\tEnergy points balance: " \
					<< _energy_points << std::endl;
	}
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode." << std::endl;
}