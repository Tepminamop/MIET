#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

vector<int> positions = { 1, 2, 4, 8, 16, 32 };

void make_hamming() {
	char file_name[40];
	cout << "Input filename" << '\n';
	cin >> file_name;
	//opening files to read and write
	FILE* from_file = fopen(file_name, "rb");
	FILE* to_file = fopen("ham.imi", "wb");

	//reading from file to vector of bitsets
	vector<string> blocks;
	unsigned char one_byte;
	string add;
	while (fread(&one_byte, sizeof(one_byte), 1, from_file)) {
		bitset<8> tmp(one_byte);
		for (int i = 0; i < 8; i++) {
			if (tmp[i] == 0) {
				add.push_back('0');
			}
			else {
				add.push_back('1');
			}
		}

		if (add.size() == 56) {
			blocks.push_back(add);
			add.clear();
		}
	}
	if (add.size() > 0 && add.size() < 56) {
		blocks.push_back(add);
	}

	//adding control bits (6 for every block)
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < positions.size(); j++) {
			int pos = positions[j];
			if (pos > blocks[i].size()) {
				break;
			}

			blocks[i].insert(pos, 1, '0');
		}
	}

	//calculate control bits
	for (int j = 0; j < blocks.size(); j++) {
		for (int i = 0; i < positions.size(); i++) {
			int current_position = positions[i];
			int counter = 0;
			if (current_position >= blocks[j].size()) {
				break;
			}
			while (current_position < blocks[j].size()) {
				for (int k = current_position; k < min((int)blocks[j].size(), current_position + positions[i]); k++) {
					if (blocks[j][k] == '1') {
						counter++;
					}
				}
				current_position += 2 * positions[i];
			}

			if (counter % 2 == 0) {
				blocks[j][positions[i]] = '0';
			}
			else {
				blocks[j][positions[i]] = '1';
			}
		}
	}

	for (int i = 0; i < blocks.size(); i++) {
		cout << blocks[i] << endl;
	}

	//wiriting result to file
	string all_bits;
	for (int i = 0; i < blocks.size(); i++) {
		all_bits.append(blocks[i]);
	}

	int pointer = 0;
	while (true) {
		if (pointer >= all_bits.size()) {
			break;
		}
		bitset<8> byte_to_write;
		int bitset_position = 0;
		for (int j = pointer; j < min((int)all_bits.size(), pointer + 8); j++) {
			if (all_bits[j] == '1') {
				byte_to_write[bitset_position] = 1;
				bitset_position++;
			}
			else {
				byte_to_write[bitset_position] = 0;
				bitset_position++;
			}
		}
		unsigned long ulong = byte_to_write.to_ulong();
		unsigned char c = static_cast<unsigned char>(ulong);
		fwrite(&c, 1, 1, to_file);
		pointer += 8;
	}


	fclose(from_file);
	fclose(to_file);
}

void decode_hamming() {
	char file_name[40];
	cout << "Input filename" << '\n';
	cin >> file_name;
	//opening files to read and write
	FILE* hamming_file = fopen(file_name, "rb");
	FILE* decode_file = fopen("res", "wb");

	//reading from file to vector of bitsets
	vector<string> blocks;
	unsigned char one_byte;
	string add;
	string all_bits;
	while (fread(&one_byte, sizeof(one_byte), 1, hamming_file)) {
		bitset<8> tmp(one_byte);
		for (int i = 0; i < 8; i++) {
			if (tmp[i] == 0) {
				add.push_back('0');
			}
			else {
				add.push_back('1');
			}
		}

		all_bits.append(add);
		add.clear();
	}

	//make blocks with 62 bits (56 + 6) and then erase control bits
	string tmp;
	for (int i = 0; i < all_bits.size(); i++) {
		tmp.push_back(all_bits[i]);
		if (tmp.length() == 62) {
			blocks.push_back(tmp);
			tmp.clear();
		}
	}
	if (tmp.size() > 0) {
		blocks.push_back(tmp);
	}

	for (int i = 0; i < blocks.size(); i++) {
		cout << blocks[i] << endl;
	}

	//here we can change bit to wrong bit in order to check program
	if (blocks[0][3] == '1') {
		blocks[0][3] = '0';
	}
	else {
		blocks[0][3] = '1';
	}

	//erase control bits, but first save them
	vector<vector<char>> control_bits(blocks.size());
	for (int i = 0; i < blocks.size(); i++) {
		int erase_counter = 0;
		for (int j = 0; j < positions.size(); j++) {
			if (positions[j] >= blocks[i].size()) break;
			control_bits[i].push_back(blocks[i][positions[j] - erase_counter]);
			blocks[i].erase(positions[j] - erase_counter, 1);
			erase_counter++;
		}
	}

	//adding control bits (6 for every block)
	for (int i = 0; i < blocks.size(); i++) {
		for (int j = 0; j < positions.size(); j++) {
			int pos = positions[j];
			if (pos > blocks[i].size()) {
				break;
			}

			blocks[i].insert(pos, 1, '0');
		}
	}
	
	//calculating and checking control bits
	//calculate control bits
	vector<vector<char>> check_control_bits(blocks.size());
	for (int j = 0; j < blocks.size(); j++) {
		for (int i = 0; i < positions.size(); i++) {
			int current_position = positions[i];
			int counter = 0;
			if (current_position >= blocks[j].size()) {
				break;
			}
			while (current_position < blocks[j].size()) {
				for (int k = current_position; k < min((int)blocks[j].size(), current_position + positions[i]); k++) {
					if (blocks[j][k] == '1') {
						counter++;
					}
				}
				current_position += 2 * positions[i];
			}

			if (counter % 2 == 0) {
				check_control_bits[j].push_back('0');
				blocks[j][positions[i]] = '0';
			}
			else {
				check_control_bits[j].push_back('1');
				blocks[j][positions[i]] = '1';
			}
		}
	}

	//checking control bits and finding wrong bit if exists, sizes are equal
	vector<int> wrong_control_bits_places;
	for (int i = 0; i < control_bits.size(); i++) {
		for (int j = 0; j < control_bits[i].size(); j++) {
			cout << control_bits[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < check_control_bits.size(); i++) {
		for (int j = 0; j < check_control_bits[i].size(); j++) {
			cout << check_control_bits[i][j] << " ";
		}
		cout << endl;
	}

	//here we checking control bits
	for (int i = 0; i < check_control_bits.size(); i++) {
		for (int j = 0; j < check_control_bits[i].size(); j++) {
			if (check_control_bits[i][j] != control_bits[i][j]) {
				wrong_control_bits_places.push_back(pow(2, j));
			}
		}

		//end block check
		int wrong_position = 0;
		bool wrong = false;
		for (int k = 0; k < wrong_control_bits_places.size(); k++) {
			wrong_position += wrong_control_bits_places[k];
			wrong = true;
		}

		if (wrong) {
			cout << "wrong: " << wrong_position << endl;
			if (blocks[i][wrong_position] == '1') {
				blocks[i][wrong_position] = '0';
			}
			else {
				blocks[i][wrong_position] = '1';
			}
		}

		wrong_control_bits_places.clear();
	}

	//erasing control bits
	for (int i = 0; i < blocks.size(); i++) {
		int erase_counter = 0;
		for (int j = 0; j < positions.size(); j++) {
			if (positions[j] >= blocks[i].size()) break;
			blocks[i].erase(positions[j] - erase_counter, 1);
			erase_counter++;
		}
	}

	//wiriting result to file
	for (int i = 0; i < blocks.size(); i++) {
		int pointer = 0;
		while (true) {
			if (pointer >= blocks[i].size()) {
				break;
			}
			bitset<8> byte_to_write;
			int bitset_position = 0;
			for (int j = pointer; j < min((int)blocks[i].size(), pointer + 8); j++) {
				if (blocks[i][j] == '1') {
					byte_to_write[bitset_position] = 1;
					bitset_position++;
				}
				else {
					byte_to_write[bitset_position] = 0;
					bitset_position++;
				}
			}
			unsigned long ulong = byte_to_write.to_ulong();
			unsigned char c = static_cast<unsigned char>(ulong);
			fwrite(&c, 1, 1, decode_file);
			pointer += 8;
		}
	}

	fclose(hamming_file);
	fclose(decode_file);
}

int main() {
	cout << "Input 0 for code and 1 for decode: ";
	int code;
	cin >> code;
	cout << endl;
	if (code == 1) {
		decode_hamming();
	}
	else {
		make_hamming();
	}
	return 0;
}