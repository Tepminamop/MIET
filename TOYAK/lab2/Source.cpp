#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <map>
using std::vector;
using std::string;
using std::stack;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::set;
using std::queue;
using std::map;

set<char> alphabet;
map<pair<string, char>, set<string>> nd;//not determenistic
map<pair<string, char>, string> d;//deterministic
queue<string> q;
set<string> used;

//not usable
void erase_duplicates() {
	set<string> duplicates;
	for (auto it = nd.begin(); it != nd.end(); it++) {
		
	}
}

//not usable
void update_fa(set<string> old, string new_name) {
	map<pair<string, char>, set<string>> new_nd;
	for (auto it = nd.begin(); it != nd.end(); it++) {
		set<string> new_set;
		pair<string, char> new_rule;
		for (const string& s : it->second) {
			if (old.find(s) != old.end()) {
				new_set.insert(new_name);
			}
			else {
				new_set.insert(s);
			}
		}

		if (old.find(it->first.first) != old.end()) {
			new_rule.first = new_name;
			new_rule.second = it->first.second;
		}
		else {
			new_rule.first = it->first.first;
			new_rule.second = it->first.second;
		}
	}

	nd = new_nd;
}

string make_new_state(set<string> states) {
	string new_name;
	for (auto& s : states) {
		new_name.append(s);
	}

	//add [to] from states to new_state
	for (auto& state : states) {
		for (auto& c : alphabet) {
			pair<string, char> old_rule = { state, c };
			if (nd.find(old_rule) != nd.end()) {
				auto tmp_add = nd[old_rule];
				pair<string, char> new_rule = { new_name, c };
				nd[new_rule].insert(tmp_add.begin(), tmp_add.end());
			}
		}
	}

	return new_name;
}

void make_dfa_from_nfa() {
	set<string> used = {"q0"};
	q.push("q0");
	used.insert("q0");
	while (!q.empty()) {
		string cur = q.front();
		q.pop();
		for (const auto& c : alphabet) {
			if (nd.find({ cur, c }) == nd.end()) continue;
			set<string> to = nd[{cur, c}];
			string new_state = make_new_state(to);
			if (used.find(new_state) == used.end()) {
				q.push(new_state);
			}
			d[{cur, c}] = new_state;
		}

		used.insert(cur);
	}
}

void out(const map<pair<string, char>, string>& d)
{
	for (const auto& [k, v] : d)
	{
		cout << k.first << "," << k.second << "=" << v << endl;
	}
}

void make_fa_from_input() {
	string s;
	char c;
	string q, f;

	while (getline(cin, s)) {
		if (s.size() <= 1) break;
		q = s.substr(0, s.find(','));
		c = s.substr(s.find(',') + 1, s.find_last_of('='))[0];
		f = s.substr(s.find_last_of('=') + 1);
		nd[{q, c}].insert(f);
		alphabet.insert(c);
	}
	bool is_deterministic = true;
	for (const auto& [k, v] : nd) {
		if (v.size() >= 2) {
			is_deterministic = false;
			break;
		}
	}

	cout << "Determine: " << is_deterministic << endl;

	if (is_deterministic) {
		for (const auto& [k, v] : nd) {
			d[k] = *v.begin();
		}
	}
	else {
		make_dfa_from_nfa();
		out(d);
	}
}


/*
void make_graph_from_input(vector<vector<pair<char, int>>>& g) {
	string input;
	while (true) {
		getline(cin, input);
		if (input.size() <= 1) break;

		//getting q number
		int first_comma = -1;
		string string_from;
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == ',') {
				first_comma = i;
				break;
			}
			if (isdigit(input[i])) string_from.push_back(input[i]);
		}

		//getting letter
		char letter = input[first_comma + 1];
		alphabet.insert(letter);

		//getting f number
		string string_to;
		for (int i = first_comma + 2; i < input.size(); i++) {
			if (isdigit(input[i])) string_to.push_back(input[i]);
		}

		//writing to vector
		int from = stoi(string_from);
		int to = stoi(string_to);
		g[from].push_back({letter, to});
	}
}

bool check_deterministic(const vector<vector<pair<char, int>>>& g) {
	for (int i = 0; i < g.size(); i++) {
		set<char> letters;
		for (int j = 0; j < g[i].size(); j++) {
			if (letters.find(g[i][j].first) != letters.end()) {
				return false;
			}
			letters.insert(g[i][j].first);
		}
	}

	return true;
}

//simple linear check or use recursion
bool check_word(const vector<vector<pair<char, int>>>& g, string word) {
	int current_pos = 0;
	string cur_word;
	while (true) {

	}
}

set<int> e_closure_one(const vector<vector<pair<char, int>>>& g, int start) {
	set<int> answer;
	for (int i = 0; i < g[start].size(); i++) {
		if (g[start][i].first == ' ') {
			answer.insert(g[start][i].second);
		}
	}

	return answer;
}

set<int> e_closure_multiple(const vector<vector<pair<char, int>>>& g, set<int> states) {
	set<int> reachable_states;
	set<int> next_states;

	for (auto& state : states) {
		next_states = e_closure_one(g, state);
		if (!next_states.empty()) {
			for (auto it = next_states.begin(); it != next_states.end(); it++) {
				reachable_states.insert(*it);
			}
		}
	}

	return reachable_states;
}

set<int> move(const vector<vector<pair<char, int>>>& g, set<int> states, char letter) {
	set<int> reachable_states;

	for (auto& state : states) {
		for (int i = 0; i < g[state].size(); i++) {
			if (g[state][i].first == letter) {
				reachable_states.insert(g[state][i].second);
			}
		}
	}

	return reachable_states;
}

void make_dfa_from_nfa(vector<vector<pair<char, int>>>& g) {
	set<int> Q1;
	map<int, pair<char, int>> S1;
	queue<set<int>> q;
	set<int> current_states;
	set<int> new_states;

	set<int> tmp = { 0 };
	q.push(tmp);
	while (!q.empty()) {
		current_states = q.front();
		q.pop();

		set<int> tmp = e_closure_multiple(g, current_states);
		for (auto it = tmp.begin(); it != tmp.end(); it++) {
			current_states.insert(*it);
		}

		check whole alphabet
		for (auto it = alphabet.begin(); it != alphabet.end(); it++) {
			new_states = move(g, current_states, *it);

			set<int> check = e_closure_multiple(g, new_states);
			bool first = true;
			for (auto it = check.begin(); it != check.end(); it++) {
				if (Q1.find(*it) == Q1.end()) {
					if (first) {
						q.push(new_states);
						first = false;
					}
					Q1.insert(*it);
				}
			}

			if (!new_states.empty()) {

			}
		}
	}
}
*/
int main() {
	make_fa_from_input();

	return 0;
};
