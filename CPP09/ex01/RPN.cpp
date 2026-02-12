// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RPN.cpp                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2026/02/12 10:38:17 by vuljas            #+#    #+#             //
//   Updated: 2026/02/12 10:38:19 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {
	*this = other;
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}

RPN::~RPN() {}

// ------------------- Helper functions
void RPN::check_argv(std::string &str) {
	size_t i;
	for (i = 0; i < str.length(); i++) {
		if (str[i] == ' ')
			continue;
		if (!is_nbr(str[i]) && !is_operator(str[i]))
			throw std::runtime_error("Error");
		if (str[i + 1] == '\0')
			break;
	}
	if (i < 2 || i != str.length() - 1)
		throw std::runtime_error("Error");

	if (!is_operator(str[str.length() - 1]))
		throw std::runtime_error("Error");
}

void RPN::process_data(std::string &str) {
	std::stack<int> stack;
	size_t i;
	for (i = 0; i < str.length(); i++) {
		char c = str[i];

		if (is_nbr(c)) {
			stack.push(c - '0');
		}
		else if (is_operator(c)) {
			if (stack.size() < 2)
				throw std::runtime_error("Error");
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();

			int res = do_operation(a, b, c);
			stack.push(res);
		}
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error");
	std::cout << stack.top() << "\n";
}

bool RPN::is_operator(char c) {
	std::string str = "+-*/";
	size_t found = str.find(c);
	if (found != std::string::npos)
		return (true);
	return (false);
}

bool RPN::is_nbr(char c) {
	std::string str = "0123456789";
	size_t found = str.find(c);
	if (found != std::string::npos)
		return (true);
	return (false);
}

int RPN::do_operation(int fir, int sec, char op) {
	if (op == '+')
		return (fir + sec);
	else if (op == '-')
		return (fir - sec);
	else if (op == '*')
		return (fir * sec);
	else {
		if (sec == 0)
			throw std::runtime_error("Error");
		return (fir / sec);
	}
}
