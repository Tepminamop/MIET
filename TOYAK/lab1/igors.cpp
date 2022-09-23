#include <iostream>
#include <string>
#include <vector>
#include <stack>

int get_symbol_priority(const char& symbol) {
	switch (symbol) {
		case '(': return 1;
		case ')': return 1;
		case '+': return 2;
		case '-': return 2;
		case '*': return 3;
		case '/': return 3;
		case '^': return 4;
		default: return -1;
	}
}

bool validate_expression() {
	return true;
}

void erase_double_unary_minus(std::string& s) {
	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		pos = s.find("--");
		if (pos < 0 || pos >= s.size()) break;
		s.replace(pos, 2, "");
	}
}

void add_zero_for_unary_minus(std::string& s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '-' && i == 0) {
			s.insert(0, "0");
			i++;
		}
		else if (s[i] == '-') {
			s.insert(i, "0");
			i++;
		}
	}
}

void parse_new_expression(std::string& s, std::string& exp) {
	int pos = -1;
	while (pos >= 0 && pos < s.size()) {
		int pos = s.find(exp);
		std::string string_first_argument;
		std::string string_second_argument;
		double first_argument;
		double second_argument;

		int tmp = pos + 4;
		while (s[tmp] != ',') {
			string_first_argument.push_back(s[tmp]);
			tmp++;
		}
		tmp++;
		while (s[tmp] != ')') {
			string_second_argument.push_back(s[tmp]);
			tmp++;
		}

	}
}

void push_element_to_stack(std::stack<char>& st, const char& symbol, std::string& polish) {
	if (st.empty()) {
		st.push(symbol);
		return;
	}

	if (symbol == ')') {
		while (st.top() != '(') {
			polish.push_back(st.top());
			polish.push_back(' ');
			st.pop();
		}

		st.pop();
		return;
	}

	if (symbol == '(') {
		st.push(symbol);
		return;
	}

	while (!st.empty()) {
		if (get_symbol_priority(st.top()) >= get_symbol_priority(symbol)) {
			polish.push_back(st.top());
			polish.push_back(' ');
			st.pop();
		}
		else break; 
	}

	st.push(symbol);
};

std::string make_polish(std::string s) {
	std::stack<char> st;
	std::string polish = "";

	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i]) || s[i] == '.') {
			polish.push_back(s[i]);
			continue;
		}

		if (s[i] == '-' && i == 0) {
			polish.push_back(s[i]);
			continue;
		}

		if (s[i] == '-' && s[i - 1] == '(') {
			polish.push_back(s[i]);
			continue;

		}

		if (get_symbol_priority(s[i]) != -1) {
			if (polish.size() != 0) {
				if (polish[polish.size() - 1] != ' ') {
					polish.push_back(' ');
				}
			}

			push_element_to_stack(st, s[i], polish);
		}
	}

	while (!st.empty()) {
		polish.push_back(' ');
		polish.push_back(st.top());
		st.pop();
	}

	return polish;
}

std::vector<std::string> make_vector_from_string(std::string s) {
	while (s[s.size() - 1] == ' ') {
		s.erase(s.end() - 1);
	}

	std::vector<std::string> vec;
	while (s.find("  ") && s.size() != 1) {
		int pos = s.find("  ");
		if (pos < 0 || pos >= s.size()) break;

		s.erase(pos, 1);
	}

	while (s.find(' ') && s.size() != 1) {
		int pos = s.find(' ');
		if (pos < 0 || pos >= s.size()) break;

		vec.push_back(s.substr(0, pos));
		s = s.substr(pos + 1);
	}

	vec.push_back(s);
	return vec;
}

double calculate_polish(std::vector<std::string>& tokens) {
	std::stack<double> st;
	for (auto& i : tokens) {
		if (i == "+" || i == "-" || i == "*" || i == "/") {
			double e1 = st.top();
			st.pop();

			double e2 = st.top();
			st.pop();

			if (i == "+")  e1 = e2 + e1;
			if (i == "-")  e1 = e2 - e1;
			if (i == "*")  e1 = e2 * e1;
			if (i == "/")  e1 = e2 / e1;

			st.push(e1);
		}
		else st.push(stod(i));
	}

	return st.top();
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
	std::string exp = "2+(1+(4))*(3+4)-5";//ans = 32
	std::string exp3 = "-15*(-9*(-1)+11)-0";
	exp3 = "-(-(-(5)))";
	exp3 = "((-(--5.45)))";
	exp3 = "-5";
	//std::cin >> exp3;

	erase_double_unary_minus(exp3);
	add_zero_for_unary_minus(exp3);
	std::cout << exp3 << std::endl;

	std::string ans;
	ans.append(make_polish(exp3));

	std::cout << ans << std::endl;

	std::vector<std::string> v = make_vector_from_string(ans);

	double top = calculate_polish(v);

	std::cout << top << std::endl;

	return 0;
};
