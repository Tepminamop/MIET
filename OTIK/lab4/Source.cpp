#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

int write_bchain(bool& func_flag, unsigned char byte, FILE* w_file, std::vector<unsigned char>& byte_chain) {

	if (byte_chain.size()>128) {
		std::cout << "Error! chain size out of border" << std::endl;
		return -1;
	}
	else {
		switch (func_flag)
		{
			unsigned char flag_byte;
			
		case 0:
			flag_byte = byte_chain.size() - 1;
			fputc(flag_byte, w_file);
			//std::cout << (int)flag_byte<< " ";
			for (auto iter = byte_chain.begin(); iter != byte_chain.end(); ++iter) {
				fputc(*iter, w_file);
				//std::cout << (int)*iter<<" ";
			}
			byte_chain.clear();
			byte_chain.push_back(byte);
			byte_chain.push_back(byte);
			break;
		case 1:
			flag_byte = byte_chain.size() - 2;
			flag_byte |= (1 << 7);
			fputc(flag_byte, w_file);
			//std::cout << (int)flag_byte<<" ";
			fputc(byte_chain.back(), w_file);
			//std::cout << (int)byte_chain.back()<<" ";
			byte_chain.clear();
			byte_chain.push_back(byte);
			break;
		}
		func_flag = !func_flag;
	}

	return 0;
};

void zip(char file_name[40]) {

	FILE* file = fopen(file_name, "rb");
	FILE* archive = fopen("archive.imi", "wb");

	unsigned char byte;

	std::vector<unsigned char> byte_chain;

	bool func_flag = 0;

	byte = fgetc(file);
	byte_chain.push_back(byte);

	while (!feof(file)) {

		switch (func_flag) {

		case 0:
			byte = fgetc(file);
			if (byte != byte_chain.back()) {
				byte_chain.push_back(byte);
			}
			else if(byte_chain.size()>1){
				
				byte_chain.pop_back();
				write_bchain(func_flag, byte, archive, byte_chain);
			}
			else {
				byte_chain.push_back(byte);
				func_flag = !func_flag;
			}
			break;
		case 1:
			byte = fgetc(file);
			if (byte == byte_chain.back()) {
				byte_chain.push_back(byte);
			}
			else {
				write_bchain(func_flag, byte, archive, byte_chain);
			}
			break;
		}
	}

	if (!byte_chain.empty()) {
		byte_chain.pop_back();
		write_bchain(func_flag, byte, archive, byte_chain);
	}

	fclose(file);
	fclose(archive);
};

void unzip() {
	FILE* archive = fopen("archive.imi", "rb");
	FILE* file = fopen("unzip", "wb");

	unsigned char byte;
	int chain_size;

	while (!feof(archive)) {

		byte = fgetc(archive) + 1;

		if ((int)byte <= 128){
			chain_size = (int)byte;
			for (int i = 0; i < chain_size; ++i) {
				byte = fgetc(archive);
				//std::cout << (int)byte<<" ";
				fputc(byte, file);

			}
			//byte = fgetc(archive);
		}
		else {
			byte &= ~(1 << 7);
			chain_size = (int)byte + 1;
			byte = fgetc(archive);
			for (int i = 0; i < chain_size; ++i) {
				fputc(byte, file);
				//std::cout << (int)byte << " ";
			}
		}
	}
	fclose(file);
	fclose(archive);
};


int main() {

	std::cout << "Input filename: ";
	char file_name[40];
	std::cin >> file_name;

	zip(file_name);
	unzip();

	return 0;
}
