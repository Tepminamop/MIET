#include <iostream>
#include <string>
#include <vector>
#include <stack>
using std::vector;
using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::endl;

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

void erase_double_unary_minus(string& s) {
	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		pos = s.find("--");
		if (pos < 0 || pos >= s.size()) break;
		s.replace(pos, 2, "");
	}
}
//add brackets (use brackets count)
void add_zero_for_unary_minus(string& s) {
	/*for (int i = 0; i < s.size(); i++) {
		if (s[i] == '-' && i == 0) {
			s.insert(0, "0");
			s.insert(0, "(");
			i += 3;
		}
		else if (s[i] == '-' && s[i - 1] == '(') {
			s.insert(i, "0");
			s.insert(i, "(");
			i += 3;
			while (i < s.size()) {
				if (s[i] == '(' || s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == ')') break;
				i++;
				if (i == s.size()) break;
			}

			s.insert(i, ")");
			i++;
		}
	}

	cout << "after unary minus: " << s << endl;*/

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '-' && i == 0) {
			s.insert(0, "0");
			i++;
		}
		else if (s[i] == '-' && s[i - 1] == '(') {
			s.insert(i, "0");
			i++;
		}
	}
}

void parse_new_expression(string& s, string& exp) {
	////need to add brackets
	//for (int i = 0; i < s.size(); i++) {
	//	if (s[i] != 'p') continue;

	//	int left = 1;
	//	int right = 0;
	//	for (int j = i + 4; j < s.size(); j++) {
	//		if (s[j] == '(') left++;
	//		if (s[j] == ')') right++;

	//		if (left == right) break;
	//	}
	//}

	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		int pos = s.find(exp);
		if (pos < 0 || pos >= s.size()) break;

		string string_first_argument;
		string string_second_argument;

		int tmp = pos + 4;
		int tmp_left = pos - 1;
		int add_left = 0;
		/*while (tmp_left >= 0) {
			if (s[tmp_left] == '(') {
				add_left++;
				tmp_left--;
			}
			else {
				break;
			}
		}*/
		int left = 1 + add_left;
		int right = 0;
		while (s[tmp] != ',') {
			string_first_argument.push_back(s[tmp]);
			tmp++;
		}
		tmp++;
		while (left != right) {
			if (s[tmp] == '(') left++;
			if (s[tmp] == ')') right++;
			if (left != right) {
				string_second_argument.push_back(s[tmp]);
				tmp++;
			}
		}

		//now s[tmp] == ')'
		string replace;
		replace.append("((");
		replace.append(string_first_argument);
		replace.push_back(')');
		replace.push_back('^');
		replace.push_back('(');
		replace.append(string_second_argument);
		replace.append("))");

		s.replace(pos, tmp - pos + 1, replace);

		cout << "replace: " << replace << endl;
		cout << "after pow: " << s << endl;
	}
}

void push_element_to_stack(stack<char>& st, const char& symbol, string& polish) {
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

string make_polish(string s) {
	stack<char> st;
	string polish;

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

vector<string> make_vector_from_string(string s) {
	while (s[s.size() - 1] == ' ') {
		s.erase(s.end() - 1);
	}

	vector<string> vec;
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

double calculate_polish(vector<string>& tokens) {
	stack<double> st;
	for (auto& i : tokens) {
		if (i == "+" || i == "-" || i == "*" || i == "/" || i == "^") {
			double e1 = st.top();
			st.pop();

			double e2 = st.top();
			st.pop();

			if (i == "+")  e1 = e2 + e1;
			if (i == "-")  e1 = e2 - e1;
			if (i == "*")  e1 = e2 * e1;
			if (i == "/") {
				if (e1 == 0)  throw std::invalid_argument("zero division");
				e1 = e2 / e1;
			}
			if (i == "^")  e1 = pow(e2, e1);

			st.push(e1);
		}
		else st.push(stod(i));
	}

	return st.top();
}

int main() {
	string exp = "2+(1+(4))*(3+4)-5";//ans = 32
	string exp3 = "-15*(-9*(-1)+11)-0";
	//exp3 = "5-(-(-(5)))";
	//exp3 = "((-(--5.45)))";
	//exp3 = "5-5";
	//cin >> exp3;
	//exp3 = "5*(-pow(2,3))+7";
	//exp3 = "-5+5+(-5-6)";
	//exp3 = "pow(pow(2,2),2)";
	exp3 = "-pow(1+pow(2,2),-pow(1.,.1)+2*2)";//add brackets, -125
	//exp3 = "pow(-2,-2)";
	//exp3 = "((1+2*1+pow(2,2))*(2*2))";
	//exp3 = "pow(2,pow(2,1)+1)";
	cin >> exp3;
	string pow_expression = "pow";
	parse_new_expression(exp3, pow_expression);

	erase_double_unary_minus(exp3);
	add_zero_for_unary_minus(exp3);
	cout << exp3 << endl;

	string ans;
	ans.append(make_polish(exp3));

	cout << ans << endl;

	vector<string> v = make_vector_from_string(ans);

	double top = calculate_polish(v);

	cout << top << endl;

	return 0;
};
