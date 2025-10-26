#include <iostream>
#include <string>
#include <fstream>

int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << "Error! Program that takes three parameters in the "
				  <<"following order: a filename and two strings, s1 and s2." << std::endl;
	}
	std::ifstream	og_file;
	std::string		s1(av[2]);
	std::string		s2(av[3]);

	og_file.open(av[1], std::ifstream::in);
	if (!og_file.good())
	{
		std::cout << "Error opening file: " << av[1] << std::endl;
		return (1);
	}

	std::string	line;

	std::getline(og_file, line, '\n');
	if (line.empty())
	{
		std::cout << av[1] << " is empty!" << std::endl;
		return (0);
	}

	std::string		replace_filename = av[1];

	replace_filename.append(".replace");

	std::ofstream	replace_file(replace_filename);
	
	if (!replace_file.good())
	{
		std::cout << "Error creating file: " << replace_filename << std::endl;
		og_file.close();
		return (1);
	}
	std::size_t	position = std::string::npos;
	
	position = line.find(s1, 0);
	while (position != std::string::npos)
	{
		line.erase(position, s1.size());
		line.insert(position, s2);
		position = line.find(s1, 0);
	}
	replace_file << line;
	while (std::getline(og_file, line, '\n'))
	{
		position = std::string::npos;
		position = line.find(s1, 0);
		while (position != std::string::npos)
		{
			line.erase(position, sizeof(s1));
			line.insert(position, s2);
			position = line.find(s1, 0);
		}
			replace_file << '\n' + line;
	}

	og_file.close();
	replace_file.close();
	return 0;
}
