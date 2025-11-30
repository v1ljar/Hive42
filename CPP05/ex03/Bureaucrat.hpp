// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bureaucrat.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/27 11:25:00 by vuljas            #+#    #+#             //
//   Updated: 2025/11/27 11:25:01 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <exception>
#include "AForm.hpp"

class Bureaucrat
{
	private:
		const std::string _name;
		int	_grade;

	public:
		Bureaucrat();
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();

		// Exceptions
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const noexcept override;
		};

		// Getters
		const std::string& getName() const;
		int	getGrade() const;

		// Member functions
		void increment_grade();
		void decrement_grade();
		void signAForm(AForm& form);
		void executeForm(AForm const & form);
};

// Overload of the insertion operator (<<)
std::ostream& operator<<(std::ostream& output, const Bureaucrat& bur);
