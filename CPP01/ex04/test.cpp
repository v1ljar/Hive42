#include <iostream>
#include <string>
#include <fstream>

bool run_test(const std::string base, const std::string filename, const std::string content, const std::string expected, const std::string s1, const std::string s2);

int main()
{
	bool	result;
	std::string base = "./sed_is_for_losers ";
	std::cout << "\n\t\t[ Running tests... ]\n" << std::endl;

	result = run_test(base, "./tests/basic_test", "This is the world\nworld world\nSo long, world", "This is the universe\nuniverse universe\nSo long, universe", "world", "universe");
	if (result)
	{
		std::cout << "✅ Basic test passed!" << std::endl;
	}
	else
		std::cout << "❌ Basic test failed!" << std::endl;
	return (0);
}

bool run_test(const std::string base, const std::string filename, const std::string content, const std::string expected, const std::string s1, const std::string s2)
{
	std::string	expected_fn = filename + "_expected";
	std::string	real_output_name = filename + ".replace";

	std::ofstream	infile(filename);

	if (!infile)
	{
		std::cerr << "Error! Infile creaton failed!" << std::endl;
		return (false);
	}
	infile << content;
	infile.close();
	std::ofstream	expected_file(expected_fn);

	if (!expected_file)
	{
		std::cerr << "Error! Expected_file creaton failed!" << std::endl;
		return (false);
	}
	expected_file << expected;
	expected_file.close();
	std::string cmd = base + filename + " " + s1 + " " + s2;
	std::system(cmd.c_str());
	std::string	str1;
	std::string	str2;

	std::ifstream	real_output(real_output_name);
	std::ifstream	expected_output(real_output_name);

	if (!real_output)
	{
		std::cerr << "Error! Real_output creaton failed!" << std::endl;
		return (false);
	}
	while (true)
	{
		std::getline(real_output, str1);
		std::getline(expected_output, str2);
		std::cout << "My output: " << str1 << "\nExpected : " << str2 + '\n' << std::endl;
		if (str1.empty() || str2.empty() || str1 != str2 )
			return (false);
		if (real_output.eof() && expected_output.eof())
			return (true);
	}
	real_output.close();
	expected_output.close();
	return (true);
}