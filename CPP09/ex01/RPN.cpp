#include "RPN.hpp"

RPN::RPN() : _data() {}

RPN::RPN(const RPN& other) : _data(other._data) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_data.clear();
		for (auto x : other._data) {
			_data.push_back(x);
		}
	}
	return *this;
}

RPN::~RPN() {}

// ------------------- Helper functions
void RPN::check_argv(std::string &str) {
	size_t i;
	for (i = 0; i < str.length();) {
		if (str[i + 1] != ' ' && str[i + 1] != '\0')
			throw std::runtime_error("Error");
		if (!is_nbr(str[i]) && !is_operator(str[i]))
			throw std::runtime_error("Error");
		_data.push_back(str[i]);
		if (str[i + 1] == '\0')
			break;
		else
			i += 2;
	}

	if (_data.size() < 3 || i != str.length() - 1)
		throw std::runtime_error("Error");

	char e_c = _data[_data.size() - 1];
	if (!is_operator(e_c))
		throw std::runtime_error("Error");
}

void RPN::process_data() {
	std::deque<int> stack;
	size_t i;
	for (i = 0; i < _data.size(); i++) {
		char c = _data[i];

		if (is_nbr(c)) {
			stack.push_back(c - '0');
		}
		else if (is_operator(c)) {
			if (stack.size() < 2)
				throw std::runtime_error("Error");
			int b = stack.back();
			stack.pop_back();
			int a = stack.back();
			stack.pop_back();

			int res = do_operation(a, b, c);
			stack.push_back(res);
		}
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error");
	std::cout << stack.back() << "\n";
}

bool RPN::is_operator(char c) {
	std::string str = "+-*/";
	size_t found = str.find(c);
	if (found != std::string::npos)
		return (true);
	return (false);
}

bool RPN::is_nbr(char c) {
	std::string str = "0123456789";
	size_t found = str.find(c);
	if (found != std::string::npos)
		return (true);
	return (false);
}

int RPN::do_operation(int fir, int sec, char op) {
	if (op == '+')
		return (fir + sec);
	else if (op == '-')
		return (fir - sec);
	else if (op == '*')
		return (fir * sec);
	else {
		if (sec == 0)
			throw std::runtime_error("Error");
		return (fir / sec);
	}
}
