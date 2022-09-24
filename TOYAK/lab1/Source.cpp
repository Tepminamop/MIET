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
using std::exception;
using std::cerr;
using std::invalid_argument;

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

void erase_spaces(string& s) {
	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		pos = s.find(' ');
		if (pos < 0 || pos >= s.size()) break;
		s.replace(pos, 1, "");
	}
}

bool validate_expression(string& s) {
	int left = 0;
	int right = 0;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') left++;
		if (s[i] == ')') right++;
	}

	if (left == right) return true;

	return false;
}

void erase_double_unary_minus(string& s) {
	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		pos = s.find("--");
		if (pos < 0 || pos >= s.size()) break;
		if (pos != 0) {
			if (isdigit(s[pos - 1])) {
				throw invalid_argument("invalid input");
			}
		}
		s.replace(pos, 2, "");
	}
}
//add brackets (use brackets count)
void add_zero_for_unary_minus(string& s) {
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

bool check_double_commas_in_new_expression(string& s) {
	string tmp = s;
	int pos = 0;
	int count_pow = 0;
	int count_commas = 0;
	while (pos >= 0 && pos < tmp.size()) {
		pos = tmp.find("pow");
		if (pos < 0 || pos >= s.size()) break;
		
		count_pow++;
		tmp.replace(pos, 3, "");
	}

	pos = 0;
	while (pos >= 0 && pos < tmp.size()) {
		pos = tmp.find(",");
		if (pos < 0 || pos >= tmp.size()) break;

		count_commas++;
		tmp.replace(pos, 1, "");
	}

	if (count_commas != count_pow) return false;

	return true;
}

void parse_new_expression(string& s, string& exp) {
	int pos = 0;
	while (pos >= 0 && pos < s.size()) {
		int pos = s.find(exp);
		if (pos < 0 || pos >= s.size()) break;

		string string_first_argument;
		string string_second_argument;

		int tmp = pos + 4;
		int left = 1;
		int right = 0;
		while (s[tmp] != ',') {
			string_first_argument.push_back(s[tmp]);
			tmp++;
			if (tmp == s.size()) throw invalid_argument("invalid input");
		}
		tmp++;
		while (left != right) {
			if (tmp == s.size()) throw invalid_argument("invalid input");
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

		if (string_first_argument == "" || string_second_argument == "") {
			throw invalid_argument("incorrect input");
		}

		s.replace(pos, tmp - pos + 1, replace);
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
	if (s.size() == 0) {
		throw invalid_argument("incorrect input\n");
	}

	if (s.size() == 1) {
		vector<string> vec;
		vec.push_back(s);
		return vec;
	}

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
			if (st.empty())  throw invalid_argument("incorrect input");
			double e1 = st.top();
			st.pop();

			if (st.empty())  throw invalid_argument("incorrect input");
			double e2 = st.top();
			st.pop();

			if (i == "+")  e1 = e2 + e1;
			if (i == "-")  e1 = e2 - e1;
			if (i == "*")  e1 = e2 * e1;
			if (i == "/") {
				if (e1 == 0)  throw invalid_argument("zero division");
				e1 = e2 / e1;
			}
			if (i == "^") {
				if (e2 == 0 && e1 == -1) throw invalid_argument("zero division");
				e1 = pow(e2, e1);
			}

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

	erase_spaces(exp3);
	cout << exp3 << endl;

	bool check_pow = check_double_commas_in_new_expression(exp3);
	if (!check_pow) {
		cerr << "invalid commas count";
		return 0;
	}

	bool check = validate_expression(exp3);
	if (!check) {
		cerr << "invalid brackets count";
		return 0;
	}

	string pow_expression = "pow";
	try {
		parse_new_expression(exp3, pow_expression);
	}
	catch (const exception& ex) {
		std::cerr << ex.what() << endl << "invalid input";
		return 0;
	}

	try {
		erase_double_unary_minus(exp3);
	}
	catch (const exception& ex) {
		std::cerr << ex.what();
		return 0;
	}

	try {
		add_zero_for_unary_minus(exp3);
	}
	catch (const exception& ex) {
		std::cerr << ex.what() << endl << "error with unary minus";
		return 0;
	}
	cout << exp3 << endl;

	string ans;
	try {
		ans.append(make_polish(exp3));
	}
	catch (const exception& ex) {
		std::cerr << ex.what() << endl << "error while parsing input string, incorrect input";
		return 0;
	}

	cout << ans << endl;

	vector<string> v;
	try {
		v = make_vector_from_string(ans);
	}
	catch (const exception& ex) {
		std::cerr << ex.what() << "incorrect input";
		return 0;
	}

	double top;
	try {
		top = calculate_polish(v);
	}
	catch (const exception& ex) {
		cerr << ex.what();
		return 0;
	}

	cout << top << endl;
	return 0;
}
