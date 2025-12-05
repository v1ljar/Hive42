#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal)
{
	static char		c_res;
	static int		i_res;
	static double	d_res;
	static float	f_res;

	if (isChar(literal))
		convertChar(literal, &c_res, &i_res, &d_res, &f_res);
	else if (isInt(literal))
		convertInt(literal, &c_res, &i_res, &d_res, &f_res);
	else if (isFloat(literal))
		convertFloat(literal, &c_res, &i_res, &d_res, &f_res);
	else if (isDouble(literal))
		convertDouble(literal, &c_res, &i_res, &d_res, &f_res);
	else
		throw NotValidLiteralException();
}

const char* NotValidLiteralException::what() const noexcept
{
	return ("Literal is not valid!");
}

bool isChar(const std::string& literal)
{
	return (literal.size() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0]));
}

bool isInt(const std::string& literal)
{
	char *end;
	long nbr = std::strtol(literal.c_str(), &end, 10);
	if (*end != '\0')
		return (false);
	return (nbr >= std::numeric_limits<int>::min() && nbr <= std::numeric_limits<int>::max());
}

bool isFloat(const std::string& literal)
{
	if (literal == "nanf" || literal == "-inff" || literal == "+inff")
		return (true);

	try {
		size_t	end;
		float	nbr = std::stof(literal, &end);
		if (literal[end] != 'f' || end != literal.length() - 1)
			return (false);
		return (nbr >= std::numeric_limits<float>::min() && nbr <= std::numeric_limits<float>::max());
	} catch (std::exception& e) {
		return (false);
	}
}

bool isDouble(const std::string& literal)
{
	if (literal == "nan" || literal == "-inf" || literal == "+inf")
		return (true);
	char*	end;
	double	nbr = std::strtod(literal.c_str(), &end);
	if (*end != '\0')
		return (false);
	return (nbr >= std::numeric_limits<double>::min() && nbr <= std::numeric_limits<double>::max());
}

void convertChar(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	*c_res = literal[0];
	*i_res = static_cast<int>(literal[0]);
	*d_res = static_cast<double>(literal[0]);
	*f_res = static_cast<float>(literal[0]);
	print_res(literal, *c_res, *i_res, *d_res, *f_res, false);
}

void convertInt(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	*i_res = std::stoi(literal, nullptr, 10);
	if (*i_res >= 0 && *i_res <= 127)
		*c_res = static_cast<char>(*i_res);
	else
		*c_res = '\0';
	*d_res = static_cast<double>(*i_res);
	*f_res = static_cast<float>(*i_res);
	print_res(literal, *c_res, *i_res, *d_res, *f_res, false);
}

void convertDouble(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	bool int_impossible = false;

	if (literal == "nan" || literal == "-inf" || literal == "+inf")
		int_impossible = true;
	*d_res = std::stod(literal, nullptr);
	*i_res = static_cast<int>(*d_res);
	*c_res = static_cast<char>(*d_res);
	*f_res = static_cast<float>(*d_res);
	if (floor(*d_res) == *d_res && *d_res >= 0 && *d_res <= 127)
		*c_res = static_cast<char>(*d_res);
	else
		*c_res = '\0';
	print_res(literal, *c_res, *i_res, *d_res, *f_res, int_impossible);
}

void convertFloat(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	bool int_impossible = false;

	if (literal == "nanf" || literal == "-inff" || literal == "+inff")
		int_impossible = true;
	*f_res = std::stof(literal, nullptr);
	*i_res = static_cast<int>(*f_res);
	*d_res = static_cast<double>(*f_res);
	if (floor(*f_res) == *f_res && *f_res >= 0 && *f_res <= 127)
		*c_res = static_cast<char>(*f_res);
	else
		*c_res = '\0';
	print_res(literal, *c_res, *i_res, *d_res, *f_res, int_impossible);
}

void print_res(const std::string& literal, char c_res, int i_res, double d_res, float f_res, bool int_impossible)
{
	std::cout << "char: ";
	if (c_res == '\0' && literal != "0")
		std::cout << "impossible";
	else if (!std::isprint(static_cast<unsigned char>(c_res)))
		std::cout << "Non displayable";
	else
		std::cout << "'" << c_res << "'";
	std::cout << "\nint: ";
	if (!int_impossible)
		std::cout << i_res;
	else
		std::cout << "impossible";
	std::cout << "\nfloat: " << f_res << "f"
			  << "\ndouble: " << d_res
			  << std::endl;
}
