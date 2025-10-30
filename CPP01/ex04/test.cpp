// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   test.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2025/10/30 13:10:55 by vuljas            #+#    #+#             //
//   Updated: 2025/10/30 13:11:02 by vuljas           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <fstream>
#include <optional>

static bool	run_test(const std::string base, const std::string filename, const std::string content, const std::string s1, const std::optional<std::string> s3);

int	main()
{
	bool	result;
	std::string base = "./sed_is_for_losers";
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
					  " ",
					  "");
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
					  std::nullopt);
	if (result)
		std::cout << "\t✅ Empty test passed!\n\n";
	else
		std::cout << "\t❌ Empty test failed!\n\n";

	return (0);
}

static bool	run_test(const std::string base, const std::string filename, const std::string content, std::string s1, const std::optional<std::string> s3)
{
	if (s1.empty())
		s1 = "";
	std::string s2; 
	if (s3)
		s2 = *s3;
	else
		s2 = "";
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

	std::string	sed_cmd = "sed 's|" + s1 + "|" + s2 + "|g' " + filename + " > " + expected_fn;
	std::system(sed_cmd.c_str());
	std::string cmd = base + " " + filename + " \"" + s1 + "\" " + s2;
	if (std::system(cmd.c_str()) != 0)
		std::cout << "calling sed_for_losers failed!" << "[" << cmd << "]" << std::endl;

	std::string	str1 = "";
	std::string	str2 = "";

	std::ifstream	real_output(real_output_name);
	std::ifstream	expected_output(expected_fn);

	if (!real_output || !expected_output)
	{
		std::cerr << "Error! Test output file missing!" << std::endl;
		return (false);
	}

	if (real_output.peek() == expected_output.peek() == '\0')
		return (true);

	while (std::getline(real_output, str1) && std::getline(expected_output, str2))
	{
		std::cout << "My output : " << str1 << "\nSed output: " << str2 + '\n' << std::endl;
		if (str1 != str2)
			break ;
	}
	if (real_output.eof() && expected_output.eof() && str1 == str2)
		return (true);
	else
		return (false);
}
