#include <iostream>
#include <stack>
#include <exception>

class RPN{
	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

	// ------------------- Helper functions
	void check_argv(std::string &str);
	void process_data(std::string &str);
	bool is_operator(char c);
	bool is_nbr(char c);
	int  do_operation(int fir, int sec, char op);
};