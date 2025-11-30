#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <exception>

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

class NotValidLiteralException : public std::exception {
	public:
		const char* what() const noexcept override;
};

bool isChar(const std::string& literal);
bool isInt(const std::string& literal);
bool isDouble(const std::string& literal);
bool isFloat(const std::string& literal);
void convertChar(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);
void convertInt(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res);
