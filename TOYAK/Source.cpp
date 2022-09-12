#include <iostream>
#include <string>
#include <vector>
#include <stack>


int priority(char symbol) {
	switch (symbol) {
		

		case '(': return 1;
		case ')': return 1;
		case '+': return 2;
		case '-': return 2;
		case '*': return 3;
		case '/': return 3;
		case '^': return 4;
	}
	return -1;
}

void stk_actions(std::stack<char> &stk, char symbol, std::string &rpn) {
	if (stk.empty()) {
		stk.push(symbol);
	}
	else if (symbol == ')') {
		while (stk.top() != '(') {
			rpn.push_back(stk.top());
			stk.pop();
		}
		stk.pop();
	}
	else if (symbol == '(') {

		stk.push(symbol);
	}
	else {
		while (!stk.empty()) {
			if (priority(stk.top()) >= priority(symbol)) {
				//std::cout << stk.top() << " " << symbol << std::endl;
				rpn.push_back(stk.top());
				rpn.push_back(' ');
				stk.pop();
			}
			else { break; }
		}
		stk.push(symbol);
	}
};

std::string make_RPN(std::string str) {
	std:: stack<char> stk;
	std::string rpn = "";
	std::string check_str = "";

	for(std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (::isdigit(*it) || *it == '.') {
			rpn.push_back(*it);
		}
		else if(::priority(*it)!=-1){
			if (rpn.size() != 0) {
				if (rpn[rpn.size() - 1] != ' ') {
					rpn.push_back(' ');
				}
			}
			//rpn.push_back(' ');
			stk_actions(stk, *it, rpn);
		}
	}
	while (!stk.empty()) {
		rpn.push_back(' ');
		rpn.push_back(stk.top());
		stk.pop();
	}
	return rpn;
}

std::vector<std::string> split_str(std::string str) {
	std::vector<std::string> vec;
	while (str.find(' ') && str.size() != 1) {
		std::size_t pos = str.find(' ');
		vec.push_back(str.substr(0, pos));
		//std::cout << str.substr(0, pos) << std::endl;
		str = str.substr(pos+1);
		std::cout << str << std::endl;
	}

	vec.push_back(str);
	for (std::string n : vec) {
		std::cout << n << ", ";
	}
	std::cout << std::endl;
	return vec;
}

double calculateRPN(std::vector<std::string>& tokens) {
	std::stack<double> s;
	for (auto& i : tokens) {
		if (i == "+" || i == "-" || i == "*" || i == "/") {
			int e1 = s.top();
			s.pop();

			int e2 = s.top();
			s.pop();

			if (i == "+")  e1 = e2 + e1;
			if (i == "-")  e1 = e2 - e1;
			if (i == "*")  e1 = e2 * e1;
			if (i == "/")  e1 = e2 / e1;

			s.push(e1);
		}
		else {
			s.push(stoi(i));
		}
	}

	return s.top();
}

int main() {

	std::string exp = "-5";

	//std::string exp1;

	//getline(std::cin, exp1);

	std::string ret = "";
	ret += make_RPN(exp);

	std::cout << ret << std::endl;

	std::vector<std::string> vec = split_str(ret);

	double top = calculateRPN(vec);

	std::cout << top << std::endl;
	
	return 0;
};