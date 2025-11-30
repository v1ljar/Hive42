// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AForm.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/27 11:25:09 by vuljas            #+#    #+#             //
//   Updated: 2025/11/27 11:25:09 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <string>

class Bureaucrat;

class AForm
{
	private:
		const std::string	_name;
		bool	_isSigned;
		const int	_gradeToSign;
		const int	_gradeToExecute;

	public:
		AForm();
		AForm(const std::string& name, const int gradeToSign, const int	gradeToExecute);
		AForm(const AForm& other);
		AForm& operator=(const AForm& other) = delete;
		virtual ~AForm() = 0;

		// Exceptions
		class GradeTooHighException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class GradeTooLowException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class FormNotSignedException : public std::exception {
			public:
				const char* what() const noexcept override;
		};
		class FormIsSignedException : public std::exception {
			public:
				const char* what() const noexcept override;
		};

		// Getters
		const std::string& getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		// Member functions
		void beSigned(const Bureaucrat& bur);
		virtual void execute(Bureaucrat const & executor) const = 0;
};
// Overload insertion operator (<<)
std::ostream& operator<<(std::ostream& output, const AForm& f);
