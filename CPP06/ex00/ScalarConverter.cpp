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
	else if (isDouble(literal))
		convertDouble(literal, &c_res, &i_res, &d_res, &f_res);
	else if (isFloat(literal))
		convertFloat(literal, &c_res, &i_res, &d_res, &f_res);
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
	return (literal.size() == 1 && !std::isdigit(literal[0]));
}

bool isInt(const std::string& literal)
{
	size_t i = 0;

	if (literal[i] == '-' || literal[i] == '+')
		i++;
	for (; i < literal.length(); i++)
	{
		if (!std::isdigit(literal[i]))
			return (false);
	}
	return (true);
}

bool isDouble(const std::string& literal)
{
	size_t	i = 0;
	bool	dot_found = false;

	if (literal[i] == '-' || literal[i] == '+')
		i++;
	for (; i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (dot_found)
				return (false);
			dot_found = true;
		}
		else if (!std::isdigit(literal[i]))
			return (false);
	}
	return (dot_found);
}

bool isFloat(const std::string& literal)
{
	size_t	i = 0;
	bool	dot_found = false;

	if (literal[i] == '-' || literal[i] == '+')
		i++;
	for (;i < literal.length(); i++)
	{
		if (literal[i] == '.')
		{
			if (dot_found)
				return (false);
			dot_found = true;
		}
		else if(!std::isdigit(literal[i]))
			break;
	}
	if (i == literal.length() - 1 && literal[i] == 'f')
		return (true);
	return (false);
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
	*f_res = std::stof(literal, nullptr);
	*i_res = static_cast<int>(*f_res);
	*c_res = static_cast<char>(*f_res);
	*d_res = static_cast<double>(*f_res);
}
