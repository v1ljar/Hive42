#include <iostream>
#include <string>
#include <fstream>

bool run_test(const std::string base, const std::string filename, const std::string content, const std::string s1, const std::string s2);

int main()
{
	bool	result;
	std::string base = "./sed_is_for_losers ";
	std::cout << "\n\t\t[ Running tests... ]\n" << std::endl;

	result = run_test(base,
					  "./tests/basic_test",
					  "This is the world\nworld world\nSo long, world",
					  "world", "universe");
	if (result)
		std::cout << "\t✅ Basic test passed!\n\n";
	else
		std::cout << "\t❌ Basic test failed!\n\n";
	
	result = run_test(base,
					  "./tests/no_space_test",
					  "This is the world\nworld world\nSo long,world",
					  "' '",
					  "''");
	if (result)
		std::cout << "\t✅ No space test passed!\n\n";
	else
		std::cout << "\t❌ No space failed!\n\n";
	
	result = run_test(base,
					  "./tests/alphabet",
					  "1:2:3lmnopqrstuvwxyz",
					  "1:2:3",
					  "abcdefghijk");
	if (result)
		std::cout << "\t✅ Alphabet test passed!\n\n";
	else
		std::cout << "\t❌ Alphabet test failed!\n\n";
	
	result = run_test(base,
					  "./tests/empty",
					  "1:2:3lmnopqrstuvwxyz",
					  "1:2:3lmnopqrstuvwxyz",
					  "' '");
	if (result)
		std::cout << "\t✅ Empty test passed!\n\n";
	else
		std::cout << "\t❌ Empty test failed!\n\n";
	
	return (0);
}

bool run_test(const std::string base, const std::string filename, const std::string content, const std::string s1, const std::string s2)
{

	std::cout << "\t\t️📝Running test: " + filename + "\n" << std::endl;
	
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

	std::string	sed_cmd = "sed 's/" + s1 + "/" + s2 + "/g' " + filename + " > " + expected_fn;
	std::system(sed_cmd.c_str());
	std::string cmd = base + filename + " " + s1 + " " + s2;
	std::system(cmd.c_str());

	std::string	str1;
	std::string	str2;

	std::ifstream	real_output(real_output_name);
	std::ifstream	expected_output(expected_fn);

	if (!real_output || !expected_output)
	{
		std::cerr << "Error! Test output file missing!" << std::endl;
		return (false);
	}
	while (std::getline(real_output, str1) && std::getline(expected_output, str2))
	{
		std::cout << "My output : " << str1 << "\nSed output: " << str2 + '\n' << std::endl;
		if (str1 != str2)
			break ;
	}
	real_output.close();
	expected_output.close();
	if (real_output.eof() && expected_output.eof() && str1 == str2)
		return (true);
	else
		return (false);
}