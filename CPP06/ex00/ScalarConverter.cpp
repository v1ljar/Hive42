#include "ScalarConverter.hpp"
#include <string>
#include <limits>
#include <cstdlib>

static bool isChar(const std::string& literal)
{
	return (literal.length() == 1 && !std::isdigit(literal[0]));
}

static bool isInt(const std::string& literal)
{
	char* end;
	long val;

	val = std::strtol(literal.c_str(), &end, 10);
	if (*end != '\0')
		return (false);
	if (val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max())
		return (false);
	return (true);
}

static bool isDouble(const std::string& literal)
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

static bool isFloat(const std::string& literal)
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

static void convertChar(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	*c_res = literal[0];
	*i_res = static_cast<int>(literal[0]);
	*d_res = static_cast<double>(literal[0]);
	*f_res = static_cast<float>(literal[0]);
}

static void convertInt(const std::string& literal, char *c_res, int *i_res, double *d_res, float *f_res)
{
	*i_res = std::atoi(literal.c_str());
	*c_res = static_cast<char>(*i_res);

	char	*end;

	*d_res = std::strtod(literal.c_str(), &end);
	*f_res = std::strtof(literal.c_str(), &end);
}

void ScalarConverter::convert(const std::string& literal)
{
	char	c_res;
	int		i_res;
	double	d_res;
	float	f_res;

	if (isChar)
		convertChar(literal, &c_res, &i_res, &d_res, &f_res);
	else if(isInt)
		convertInt(literal, &c_res, &i_res, &d_res, &f_res);
	std::cout << "char: "
			  << std::endl;
}