#include <iostream>
#include <deque>
#include <exception>

class RPN{
	public:
		std::deque<char> _data;

		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

	// ------------------- Helper functions
	void check_argv(std::string &str);
	void process_data();
	bool is_operator(char c);
	bool is_nbr(char c);
	int  do_operation(int fir, int sec, char op);
};