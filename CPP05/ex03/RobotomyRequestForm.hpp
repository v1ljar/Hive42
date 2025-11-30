// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RobotomyRequestForm.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/27 11:24:29 by vuljas            #+#    #+#             //
//   Updated: 2025/11/27 11:24:29 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		std::string _target;
	public:
		RobotomyRequestForm() = delete;
		RobotomyRequestForm(const std::string& target);
		RobotomyRequestForm(const RobotomyRequestForm& other) = delete;
		RobotomyRequestForm& operator=(const RobotomyRequestForm& other) = delete;
		~RobotomyRequestForm();

		// Member functions
		void execute(const Bureaucrat& executor) const override;
};
