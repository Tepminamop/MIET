//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <stdint.h>
//#include <windows.h>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <bitset>
//#include <cmath>
//
//using namespace std;
//
//void count_frequency() {
//	char file_name[40];
//	cout << "Input file name" << '\n';
//	cin >> file_name;
//
//	//open file
//	FILE* archive = fopen(file_name, "rb");
//
//	int size = 0;
//	map<uint8_t, double> frequency;
//
//	uint8_t one_byte;
//	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
//		size++;
//		frequency[one_byte]++;
//	}
//
//	vector<pair<uint8_t, double>> vector_frequency;
//	copy(frequency.begin(), frequency.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_frequency));
//
//	sort(vector_frequency.begin(), vector_frequency.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	//frequency
//	cout << "Frequency by value:\n";
//
//	for (auto const& pair : vector_frequency) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	sort(vector_frequency.begin(), vector_frequency.end());
//
//	cout << "Frequency by alphabet:\n";
//	for (auto const& pair : vector_frequency) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//file size
//	cout << "File size: " << size << '\n';
//
//	map<uint8_t, double> probability;
//	for (auto& it : frequency) {
//		probability[it.first] = it.second / size;
//	}
//
//	vector<pair<uint8_t, double>> vector_probability;
//	copy(probability.begin(), probability.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_probability));
//
//	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	//probability
//	cout << "Probability by value:\n";
//
//	for (auto const& pair : vector_probability) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//probability
//	cout << "Probability by alphabet:\n";
//
//	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
//		return l.first < r.first;
//		});
//
//	for (auto const& pair : vector_probability) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//information count I(ai)
//	map<uint8_t, double> info_count;
//	for (auto& it : probability) {
//		info_count[it.first] = -1 * (log(it.second) / log(2));
//	}
//
//	vector<pair<uint8_t, double>> vector_information;
//	copy(info_count.begin(), info_count.end(), back_inserter<vector<pair<uint8_t, double>>>(vector_information));
//
//	sort(vector_information.begin(), vector_information.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	cout << "Information count by value:\n";
//	for (auto const& pair : vector_information) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	sort(vector_information.begin(), vector_information.end(), [](const pair<uint8_t, double>& l, const pair<uint8_t, double>& r) {
//		return l.first < r.first;
//		});
//
//	cout << "Information count by alphabet:\n";
//	for (auto const& pair : vector_information) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//information sum
//	double info_sum = 0;
//	for (auto& it : info_count) {
//		info_sum += it.second;
//	}
//
//	cout << "Information sum: " << info_sum << '\n';
//}
//
//void unicode() {
//	char file_name[40];
//	cout << "Input file name" << '\n';
//	cin >> file_name;
//
//	//open file
//	FILE* archive = fopen(file_name, "rb");
//
//	int size = 0;
//	map<uint16_t, double> frequency;
//
//	uint16_t one_byte;
//	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
//		size++;
//		frequency[one_byte]++;
//	}
//
//	vector<pair<uint16_t, double>> vector_frequency;
//	copy(frequency.begin(), frequency.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_frequency));
//
//	sort(vector_frequency.begin(), vector_frequency.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	//frequency
//	cout << "Frequency by value:\n";
//
//	for (auto const& pair : vector_frequency) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	sort(vector_frequency.begin(), vector_frequency.end());
//
//	cout << "Frequency by alphabet:\n";
//	for (auto const& pair : vector_frequency) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//file size
//	cout << "File size: " << size << '\n';
//
//	map<uint16_t, double> probability;
//	for (auto& it : frequency) {
//		probability[it.first] = it.second / size;
//	}
//
//	vector<pair<uint16_t, double>> vector_probability;
//	copy(probability.begin(), probability.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_probability));
//
//	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	//probability
//	cout << "Probability by value:\n";
//
//	for (auto const& pair : vector_probability) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//probability
//	cout << "Probability by alphabet:\n";
//
//	sort(vector_probability.begin(), vector_probability.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
//		return l.first < r.first;
//		});
//
//	for (auto const& pair : vector_probability) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//information count I(ai)
//	map<uint16_t, double> info_count;
//	for (auto& it : probability) {
//		info_count[it.first] = -1 * (log(it.second) / log(2));
//	}
//
//	vector<pair<uint16_t, double>> vector_information;
//	copy(info_count.begin(), info_count.end(), back_inserter<vector<pair<uint16_t, double>>>(vector_information));
//
//	sort(vector_information.begin(), vector_information.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
//		return l.second > r.second;
//		});
//
//	cout << "Information count by value:\n";
//	for (auto const& pair : vector_information) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	sort(vector_information.begin(), vector_information.end(), [](const pair<uint16_t, double>& l, const pair<uint16_t, double>& r) {
//		return l.first < r.first;
//		});
//
//	cout << "Information count by alphabet:\n";
//	for (auto const& pair : vector_information) {
//		cout << '{' << pair.first << "," << pair.second << '}' << endl;
//	}
//
//	//information sum
//	double info_sum = 0;
//	for (auto& it : info_count) {
//		info_sum += it.second;
//	}
//
//	cout << "Information sum: " << info_sum << '\n';
//}
//
//int main() {
//	unicode();
//	count_frequency();
//
//	return 0;
//}