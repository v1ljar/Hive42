#include <deque>

class RPN{
	public:
		std::deque<char> _data;

		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
};