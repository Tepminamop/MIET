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

void stk_actions(std::stack<char>& stk, char symbol, std::string& rpn) {
	if (symbol == '-') {
		std::cout << '-' << '\n';
	}

	if (stk.empty()) {
		stk.push(symbol);
	}
	else if (symbol == ')') {
		while (stk.top() != '(') {
			rpn.push_back(stk.top());
			rpn.push_back(' ');
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
	std::stack<char> stk;
	std::string rpn = "";
	std::string check_str = "";


	for (int i = 0; i < str.size(); i++) {

		if (str[i] == '-') {
			std::cout << '-' << '\n';
		}

		if (::isdigit(str[i]) || str[i] == '.') {
			rpn.push_back(str[i]);
		}
		else if (str[i] == '-' && i == 0) {
			rpn.push_back(str[i]);
		}
		else if (str[i] == '-' && str[i - 1] == '(') {
				rpn.push_back(str[i]);
			
		}
		else if (::priority(str[i]) != -1) {
			if (rpn.size() != 0) {
				if (rpn[rpn.size() - 1] != ' ') {
					rpn.push_back(' ');
				}
			}
			stk_actions(stk, str[i], rpn);
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
	while (str.find("  ") && str.size() != 1) {
		std::size_t pos = str.find("  ");
		if (pos < 0 || pos >= str.size()) break;
		//vec.push_back(str.substr(0, pos));
		//std::cout << str.substr(0, pos) << std::endl;
		//str = str.substr(pos + 1);
		//std::cout << str << std::endl;
		str.erase(pos, 1);
	}

	while (str.find(' ') && str.size() != 1) {
		std::size_t pos = str.find(' ');
		vec.push_back(str.substr(0, pos));
		//std::cout << str.substr(0, pos) << std::endl;
		str = str.substr(pos + 1);
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
		if (i == "+" || i == "-" ||  i == "*" || i == "/") {
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

//double calculateRPN(std::vector<std::string>& tokens) {
//	std::stack<double> s;
//	for (auto& it : tokens) {
//		if (priority(it[0]) > 1) {
//			double e1 = s.top();
//			s.pop();
//
//			if (!s.empty()) {
//
//				double e2 = s.top();
//				s.pop();
//
//				switch (it[0]) {
//				case '+':
//					e1 = e1 + e2;
//					break;
//				case '-':
//					/*if (::isdigit(e1)) {e1 = e2 - e1;}
//					else
//					{
//						e1 = e2-e1;
//					}*/
//					e1 = e2 - e1;
//
//					break;
//				case '*':
//					e1 = e1 * e2;
//					break;
//				case '/':
//					if (e2 == 0) {
//						throw std::exception("X/0 - Error! Wrong argument");
//						break;
//					}
//					e1 = e1 / e2;
//					break;
//				case '^':
//					e1 = pow(e1, e2);
//					break;
//				}
//				s.push(e1);
//			}
//
//			else if (it == "-") {
//				std::cout << e1 << std::endl;
//				e1 = 0 - e1;
//				s.push(e1);
//			}
//		}
//		else {
//			s.push(stod(it));
//		}
//	}
//	return s.top();
//}


int main() {

	//std::string exp = "(1+(1+3))*(3+4)-5";

	std::string exp = "2+(1+(4))*(3+4)-5";//ans = 32
	std::string exp3 = "-15*(-9*(-1)+11)-0";
	//std::cin >> exp3;
	//std::string exp1;

	//getline(std::cin, exp1);

	std::string ret = "";
	ret += make_RPN(exp3);

	std::cout << ret << std::endl;

	std::vector<std::string> vec = split_str(ret);

	double top = calculateRPN(vec);

	std::cout << top << std::endl;

	return 0;
};
