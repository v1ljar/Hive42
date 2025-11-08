#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Default"), _hit_points(10), _energy_points(10), _attack_damage(0)
{
	std::cout << "ClapTrap " << _name << " default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) :	_name(name),
										_hit_points(10),
										_energy_points(10),
										_attack_damage(0)
{
	std::cout	<< "ClapTrap " << name << " parametrized constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and when attacking, makes " \
				<< _attack_damage << " damage." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
{
	*this = other;
	std::cout	<< "ClapTrap " << _name << " copy constructor called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and when attacking, makes " \
				<< _attack_damage << " damage." << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_hit_points = other._hit_points;
		this->_energy_points = other._energy_points;
		this->_attack_damage = other._attack_damage;
	}
	std::cout	<< "ClapTrap " << _name << " copy assignment operator called.\n\t" \
				<< _name << " has " << _hit_points << " hitpoints, " \
				<< _energy_points << " energy points and when attacking, makes " \
				<< _attack_damage << " damage." << std::endl;
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (!_hit_points)
		std::cout << "ClapTrap " << _name << " is dead already!" << std::endl;
	else if (!_energy_points)
		std::cout << "ClapTrap " << _name << " has no energy to attack!" << std::endl;
	else
	{
		_energy_points--;
		std::cout	<< "ClapTrap " << _name << " attacks " << target << ", causing "
					<< _attack_damage << " points of damage!\n\tEnergy points balance: " \
					<< _energy_points << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (!_hit_points)
	{
		std::cout << "ClapTrap " << _name << " is dead already!" << std::endl;
		return;
	}
	else
	{
		_hit_points -= amount;
		if (_hit_points < 0)
			_hit_points = 0;
		std::cout	<< "ClapTrap " << _name << " got attacked! Damage was: " << amount \
					<< ".\n\tHit points balance: " << _hit_points << "." << std::endl;
	}
	if (!_hit_points)
		std::cout<< "ClapTrap " << _name << " is dead!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (!_hit_points)
		std::cout << "ClapTrap " << _name << " is dead already!" << std::endl;
	else if (!_energy_points)
		std::cout << "ClapTrap " << _name << " has no energy to repair!" << std::endl;
	else
	{
		_energy_points--;
		_hit_points += amount;
		std::cout	<< "ClapTrap " << _name << " got repaired. Gained " << amount \
					<< " hit points. Hit points balance: " << _hit_points << "." << std::endl;
	}
}
