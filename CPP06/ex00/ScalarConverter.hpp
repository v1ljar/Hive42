// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScalarConverter.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/12/09 11:34:34 by vuljas            #+#    #+#             //
//   Updated: 2025/12/09 11:34:35 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <exception>
#include <cmath>

class ScalarConverter
{
	private:
		ScalarConverter() = delete;
		ScalarConverter(const ScalarConverter& other) = delete;
		ScalarConverter& operator=(const ScalarConverter& other) = delete;
		~ScalarConverter() = delete;

	public:
		static void convert(const std::string& literal);
};

// Exception
class NotValidLiteralException : public std::exception {
	public:
		const char* what() const noexcept override;
};

// Type checkers
bool isChar(const std::string& literal);
bool isInt(const std::string& literal);
bool isDouble(const std::string& literal);
bool isFloat(const std::string& literal);

// Converters
void convertChar(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);
void convertInt(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);
void convertDouble(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);
void convertFloat(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);

// Print function
void print_res(char c_res, int i_res, double d_res, float f_res, bool int_impossible);
