// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PresidentialPardonForm.hpp                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/11/24 10:31:28 by vuljas            #+#    #+#             //
//   Updated: 2025/11/24 10:31:28 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		const std::string _target;

	public:
		PresidentialPardonForm() = delete;
		PresidentialPardonForm(const std::string& target);
		PresidentialPardonForm(const PresidentialPardonForm& other) = delete;
		PresidentialPardonForm& operator=(const PresidentialPardonForm& other) = delete;
		~PresidentialPardonForm();

		// Member functions
		void execute(const Bureaucrat& executor) const override;
};
