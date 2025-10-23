#include "Account.hpp"
#include <iostream>

int	index = 0;

Account::Account(int initial_deposit) : _nbDeposits(0), _nbWithdrawals(0) {
	_amount = initial_deposit;
	_accountIndex = index++;
	std::cout 	<< "[Timestamp here] " << "index:" << _accountIndex
				<< ";amount:" << _amount << ";created" << std::endl;
}

Account::~Account(void) {}

int	Account::getNbAccounts( void )
{
	return (index + 1);
}
int	Account::getTotalAmount( void )
{
	return (0);
}
int	Account::getNbDeposits( void )
{
	return (0);
}
int	Account::getNbWithdrawals( void )
{
	return (0);
}
void	Account::displayAccountsInfos( void )
{

}

void	Account::makeDeposit( int deposit )
{
	(void)deposit;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	(void)withdrawal;
	return (false);
}

int		Account::checkAmount( void ) const
{
	return (0);
}

void	Account::displayStatus( void ) const
{

}

void	Account::_displayTimestamp( void )
{

}