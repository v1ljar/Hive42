// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RPN.hpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/02/12 10:38:00 by vuljas            #+#    #+#             //
//   Updated: 2026/02/12 10:38:02 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <stack>
#include <exception>
#include <climits>

class RPN{
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

	// ------------------- Helper functions
	void check_argv(std::string &str);
	void process_data(std::string &str);
	bool is_operator(char c);
	int  do_operation(int fir, int sec, char op);
};
