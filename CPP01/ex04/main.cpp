#include <iostream>
#include <string>
#include <fstream>

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Error! Usage: ./sed_is_for_losers <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	std::string		fname(av[1]);
	std::string		s1(av[2]);
	std::string		s2(av[3]);

	if (s1.empty())
	{
		std::cerr << "Error! s1 cannot be empty!" << std::endl;
		return (1);
	}
	std::ifstream	og_file(fname);

	if (!og_file)
	{
		std::cerr << "Error opening file: " << fname << std::endl;
		return (1);
	}
	std::ofstream	replace_file(fname + ".replace");

	if (!replace_file)
	{
		std::cerr << "Error opening file: " << fname + ".replace" << std::endl;
		return (1);
	}
	std::string	line;

	while (std::getline(og_file, line))
	{
		std::size_t position = 0;
		position = line.find(s1, 0);
		while ((position = line.find(s1, position)) != std::string::npos)
		{
			line.erase(position, s1.size());
			line.insert(position, s2);
			position += s2.size();
		}
		replace_file << line;
		if (!og_file.eof())
			replace_file << '\n';
	}
	og_file.close();
	replace_file.close();
	return 0;
}
