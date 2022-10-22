
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <regex>

using namespace std;

struct Link 
{
	char s; // состояние
	string inp; // оставшаяся часть входной ленты
	string stack; // состояние магазина на данный момент
	int index; // индекс возможного значения функции
	bool term; // можно ли менять выбор ветви на данном ходе

	Link(char s, string p, string h, bool t) : s(s), inp(p), stack(h), index(-1), term(t) { }
	Link(char s, string p, string h) : s(s), inp(p), stack(h), index(-1) { }
};

struct Fargs 
{
	char s; // состояние
	char p; // символ со входной ленты
	char h; // магазинный символ

	Fargs(char s, char p, char h) : s(s), p(p), h(h) { }
};

struct Value 
{
	char s;		// состояние
	string c;	// заносимая цепочка

	Value(char s, string c) : s(s), c(c) { }
};

struct Command 
{
	Fargs f;
	vector<Value> values;

	Command(Fargs f, vector<Value> v) : f(f), values(v) { }
};

class Storage 
{
private:
	ifstream file;
	set<char> P; // терминальные символы
	set<char> H; // нетерминальные символы
	char s0 = '0', h0 = '|', empty_symbol = '\0';
	vector<Command> commands;
	vector<Link> chain; // цепочка конфигураций магазинного автомата, полученная в процессе его работы

public:

	Storage(const char* filename) : file(filename) 
	{
		if (!file.is_open())
			throw runtime_error("Не удалось открыть файл для чтения\n");
		string tmpStr;
		int vsize;
		const regex exp("([[:upper:]])>([[:print:]]+)");
		smatch match;
		while (getline(file, tmpStr)) 
		{
			if (tmpStr.size() == 0) 
				continue;
			if (!regex_match(tmpStr, match, exp) || tmpStr[tmpStr.size() - 1] == '|' || tmpStr[2] == '|') 
			{
				throw runtime_error("Не удалось распознать содержимое файла\n");
			}
			else 
			{
				H.insert(match[1].str()[0]);
				commands.push_back(Command(Fargs(s0, empty_symbol, match[1].str()[0]), vector<Value>()));
				commands[commands.size() - 1].values.push_back(Value(s0, ""));
				for (int i = 0; i < match[2].str().size(); i++)
				{
					if (match[2].str()[i] == '|')
					{
						if (match[2].str()[i - 1] != '|')
							commands[commands.size() - 1].values.push_back(Value(s0, ""));
					}
					else
					{
						P.insert(match[2].str()[i]);
						vsize = commands[commands.size() - 1].values.size();
						commands[commands.size() - 1].values[vsize - 1].c.push_back(match[2].str()[i]);
					}
				}

				for (int i = 0; i < commands[commands.size() - 1].values.size(); i++)
					reverse(commands[commands.size() - 1].values[i].c.begin(), commands[commands.size() - 1].values[i].c.end());
			}
		}
		for (const auto &c : H)
			P.erase(c);
		for (const auto& c : P)
			commands.push_back(Command(Fargs(s0, c, c), vector<Value>({ Value(s0, "\0") })));
		commands.push_back(Command(Fargs(s0, empty_symbol, h0), vector<Value>({ Value(s0, "\0") })));
	}

	void showInfo() 
	{
		cout << "Входной алфавит:\nP = {";
		for (const auto& c : P)
			cout << c << ", ";
		cout << "\b\b}\n\n";
		cout << "Алфавит магазинных символов:\nZ = {";
		for (const auto& c : H)
			cout << c << ", ";
		for (const auto& c : P)
			cout << c << ", ";
		cout << "h0}\n\n";

		cout << "Список команд:\n";
		for (const auto& c : commands)
		{
			cout << "f(s" << c.f.s << ", ";
			if (c.f.p == empty_symbol)
				cout << "lambda";
			else
				cout << c.f.p;
			cout << ", ";
			if (c.f.h == h0)
				cout << "h0";
			else
				cout << c.f.h;
			cout << ") = {";
			for (Value v : c.values)
			{
				cout << "(s" << v.s << ", ";
				if (v.c[0] == empty_symbol)
					cout << "lambda";
				else
					cout << v.c;
				cout << "); ";

			}
			cout << "\b\b}\n";
		}
		cout << endl;
	}

	void showChain() 
	{
		cout << "\nЦепочка конфигураций: \n";
		for (const auto& link : chain)
			cout << "(s" << link.s << ", " << ((link.inp.size() == 0) ? "lambda" : link.inp) << ", h0" << link.stack << ") |– ";
		cout << "(s0, lambda, lambda)" << endl;
	}

	bool push_link()
	{
		int ch_size = chain.size();
		int mag_size, j, i;
		for (i = 0; i < commands.size(); i++) {
			mag_size = chain[ch_size - 1].stack.size();
			if (chain[chain.size() - 1].inp.size() != 0 && chain[chain.size() - 1].stack.size() != 0 && chain[ch_size - 1].s == commands[i].f.s && (chain[ch_size - 1].inp[0] == commands[i].f.p || empty_symbol == commands[i].f.p) && chain[ch_size - 1].stack[mag_size - 1] == commands[i].f.h)
			{
				for (j = 0; j < commands[i].values.size(); j++)
				{
					if (commands[i].f.p == empty_symbol)
					{
						chain.push_back(Link(commands[i].values[j].s, chain[ch_size - 1].inp, string(chain[ch_size - 1].stack)));
					}
					else
					{
						chain.push_back(Link(commands[i].values[j].s, chain[ch_size - 1].inp, string(chain[ch_size - 1].stack)));
						reverse(chain[ch_size].inp.begin(), chain[ch_size].inp.end());
						chain[ch_size].inp.pop_back();
						reverse(chain[ch_size].inp.begin(), chain[ch_size].inp.end());
					}

					chain[ch_size].stack.pop_back();
					chain[ch_size].stack += commands[i].values[j].c;

					if (chain[ch_size].inp.size() < chain[ch_size].stack.size())
					{
						chain.pop_back();
						chain.pop_back();
						return false;
					}
					else
					{
						if (chain[chain.size() - 1].inp.size() == 0 && chain[chain.size() - 1].stack.size() == 0 || push_link())
							return true;
					}
				}
			}
		}
		if (i == commands.size())
		{
			chain.pop_back();
			return false;
		}
	}

	bool check_line(const string& str)
	{
		if (commands[0].values.size() == 1)
			chain.push_back(Link(s0, str, string(""), false));
		else
			chain.push_back(Link(s0, str, string(""), true));

		chain[0].stack.push_back(commands[0].f.h);

		bool res = push_link();
		if (res)
		{
			cout << "Валидная строка\n";
			showChain();
		}
		else {
			cout << "Невалидная строка\n";
		}
		chain.clear();
		return res;
	}

	~Storage() 
	{ 
		file.close(); 
	}
};

int main(int argc, char* argv[]) 
{
	setlocale(LC_ALL, "Russian");
	string str;
	try {
		Storage strg(argv[1]);
		strg.showInfo();
		while (true)
		{
			cout << "Введите строку: \n";
			getline(cin, str);
			strg.check_line(str);
			cout << endl;
		}
	}
	catch (const exception& err) {
		cerr << err.what() << endl;
	}
	return 0;
}
