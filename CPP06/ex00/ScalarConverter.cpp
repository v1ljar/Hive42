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
	std::cout << "char: " << c_res
			  << "\nint: " << i_res
			  << "\ndouble: " << d_res
			  << "\nfloat: " << f_res
			  << std::endl;
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
	if (literal == "-nanf" || literal == "-inff" || literal == "+inff")
		return (true);

	size_t	end;
	float	nbr = std::stof(literal, &end);
	if (literal[end] != 'f' || end != literal.length() - 1)
		return (false);
	return (nbr >= std::numeric_limits<float>::min() && nbr <= std::numeric_limits<float>::max());
}

bool isDouble(const std::string& literal)
{
	if (literal == "-nan" || literal == "-inf" || literal == "+inf")
		return (true);
	char*	end;
	double	nbr = std::strtod(literal.c_str(), &end);
	if (*end != '\0')
		return (false);
	return (nbr >= std::numeric_limits<double>::min() && nbr <= std::numeric_limits<double>::max());
}

void convertChar(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	std::cout << "CHAR [ " << literal << " ]\n";
	*c_res = literal[0];
	*i_res = static_cast<int>(literal[0]);
	*d_res = static_cast<double>(literal[0]);
	*f_res = static_cast<float>(literal[0]);
}

void convertInt(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	std::cout << "INT [ " << literal << " ]\n";
	*i_res = std::stoi(literal, nullptr, 10);
	*c_res = static_cast<char>(*i_res);
	*d_res = static_cast<double>(*i_res);
	*f_res = static_cast<float>(*i_res);;
}

void convertDouble(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	std::cout << "DOUBLE [ " << literal << " ]\n";
	*d_res = std::stod(literal, nullptr);
	*i_res = static_cast<int>(*d_res);
	*c_res = static_cast<char>(*d_res);
	*f_res = static_cast<float>(*d_res);;
}

void convertFloat(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	std::cout << "FLOAT [ " << literal << " ]\n";
	if (literal == "-nan" || literal == "-inf" || literal == "+inf")
		return ;
	*f_res = std::stof(literal, nullptr);
	*i_res = static_cast<int>(*f_res);
	*c_res = static_cast<char>(*f_res);
	*d_res = static_cast<double>(*f_res);
}
