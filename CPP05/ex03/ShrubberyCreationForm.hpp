// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/27 11:24:23 by vuljas            #+#    #+#             //
//   Updated: 2025/11/27 11:24:24 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		std::string _target;
	public:
		ShrubberyCreationForm() = delete;
		ShrubberyCreationForm(const std::string& target);
		ShrubberyCreationForm(const ShrubberyCreationForm& other) = delete;
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other) = delete;
		~ShrubberyCreationForm();

		// Member functions
		void execute(const Bureaucrat & executor) const override;
};
