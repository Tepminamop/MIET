#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <stdio.h>
#include <locale.h>

#include <iostream>
#include <io.h>
#include <fcntl.h>

using std::vector;
using std::string;
using std::cin;
using std::endl;
using std::exception;
using std::cerr;
using std::invalid_argument;
using std::map;
using std::pair;
using std::back_inserter;

void count_frequency() {
	char file_name[40];
	std::wcout << "Input file name" << '\n';
	cin >> file_name;

	//open file
	FILE* archive = fopen(file_name, "rb");

	int size = 0;
	map<uint8_t, double> frequency;

	uint8_t one_byte;
	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
		size++;
		frequency[one_byte]++;
	}

	vector<pair<uint8_t, double>> vector_frequency;
	copy(frequency.begin(), frequency.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_frequency));

	sort(vector_frequency.begin(), vector_frequency.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
		return l.second > r.second;
		});

	//frequency
	std::wcout << "Frequency by value:\n";

	for (auto const& pair : vector_frequency) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	sort(vector_frequency.begin(), vector_frequency.end());

	std::wcout << "Frequency by alphabet:\n";
	for (auto const& pair : vector_frequency) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//file size
	std::wcout << "File size: " << size << '\n';

	map<uint8_t, double> probability;
	for (auto& it : frequency) {
		probability[it.first] = it.second / size;
	}

	vector<pair<uint8_t, double>> vector_probability;
	copy(probability.begin(), probability.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_probability));

	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
		return l.second > r.second;
		});

	//probability
	std::wcout << "Probability by value:\n";

	for (auto const& pair : vector_probability) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//probability
	std::wcout << "Probability by alphabet:\n";

	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
		return l.first < r.first;
		});

	for (auto const& pair : vector_probability) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//information count I(ai)
	map<uint8_t, double> info_count;
	for (auto& it : probability) {
		info_count[it.first] = -1 * (log(it.second) / log(2));
	}

	vector<pair<uint8_t, double>> vector_information;
	copy(info_count.begin(), info_count.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_information));

	sort(vector_information.begin(), vector_information.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
		return l.second > r.second;
		});

	std::wcout << "Information count by value:\n";
	for (auto const& pair : vector_information) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	sort(vector_information.begin(), vector_information.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
		return l.first < r.first;
		});

	std::wcout << "Information count by alphabet:\n";
	for (auto const& pair : vector_information) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//information sum
	double info_sum = 0;
	for (auto& it : info_count) {
		info_sum += it.second;
	}

	std::wcout << "Information sum: " << info_sum << '\n';
}

void unicode() {
	char file_name[40];
	std::wcout << "Input file name" << '\n';
	cin >> file_name;

	//open file
	FILE* archive = fopen(file_name, "rb");

	int size = 0;
	map<uint16_t, double> frequency;

	uint16_t one_byte;
	wchar_t uc;
	while (fread(&uc, 2, 1, archive)) {
		std::wcout << uc << endl;
		size++;
		frequency[one_byte]++;
	}

	vector<pair<uint16_t, double>> vector_frequency;
	copy(frequency.begin(), frequency.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_frequency));

	sort(vector_frequency.begin(), vector_frequency.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
		return l.second > r.second;
		});

	//frequency
	std::wcout << "Frequency by value:\n";

	for (auto const& pair : vector_frequency) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	sort(vector_frequency.begin(), vector_frequency.end());

	std::wcout << "Frequency by alphabet:\n";
	for (auto const& pair : vector_frequency) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//file size
	std::wcout << "File size: " << size << '\n';

	map<uint16_t, double> probability;
	for (auto& it : frequency) {
		probability[it.first] = it.second / size;
	}

	vector<pair<uint16_t, double>> vector_probability;
	copy(probability.begin(), probability.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_probability));

	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
		return l.second > r.second;
		});

	//probability
	std::wcout << "Probability by value:\n";

	for (auto const& pair : vector_probability) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//probability
	std::wcout << "Probability by alphabet:\n";

	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
		return l.first < r.first;
		});

	for (auto const& pair : vector_probability) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//information count I(ai)
	map<uint16_t, double> info_count;
	for (auto& it : probability) {
		info_count[it.first] = -1 * (log(it.second) / log(2));
	}

	vector<pair<uint16_t, double>> vector_information;
	copy(info_count.begin(), info_count.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_information));

	sort(vector_information.begin(), vector_information.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
		return l.second > r.second;
		});

	std::wcout << "Information count by value:\n";
	for (auto const& pair : vector_information) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	sort(vector_information.begin(), vector_information.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
		return l.first < r.first;
		});

	std::wcout << "Information count by alphabet:\n";
	for (auto const& pair : vector_information) {
		std::wcout << '{' << pair.first << "," << pair.second << '}' << endl;
	}

	//information sum
	double info_sum = 0;
	for (auto& it : info_count) {
		info_sum += it.second;
	}

	std::wcout << "Information sum: " << info_sum << '\n';
}

//int main() {
//	if (!setlocale(LC_CTYPE, ""))
//	{
//		fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
//		return 1;
//	}
//
//	unsigned short unicodeChar = 0x0985;
//	printf("%lc\n", unicodeChar);
//
//	unicode();
//	count_frequency();
//
//	return 0;
//}

int wmain(int argc, wchar_t* argv[])
{
	//if (!setlocale(LC_CTYPE, ""))
	//{
	//	fprintf(stderr, "Error:Please check LANG, LC_CTYPE, LC_ALL.\n");
	//	return 1;
	//}

	unsigned short unicodeChar = 0x0985;
	printf("%lc\n", unicodeChar);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"\x043a\x043e\x0448\x043a\x0430 \x65e5\x672c\x56fd\n");
	wprintf(L"\x2655\n");
	unicode();
	count_frequency();

	//setmode(_fileno(stdout), _O_BINARY);//back to normal

	return 0;
}