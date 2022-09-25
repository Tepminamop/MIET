#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

void write_bchain(bool& func_flag, unsigned char byte, FILE* w_file, std::vector<unsigned char>& byte_chain) {

	if (byte_chain.size()>128) {
		std::cout << "Error! chain size out of border" << std::endl;
	}
	else {
		switch (func_flag)
		{
			unsigned char flag_byte;
			
		case 0:
			flag_byte = byte_chain.size()-1;
			fputc(flag_byte, w_file);
			for (auto iter = byte_chain.begin(); iter != byte_chain.end(); ++iter) {
				fputc(*iter, w_file);
			}
			byte_chain.clear();
			byte_chain.push_back(byte);
			byte_chain.push_back(byte);
			break;
		case 1:
			flag_byte = byte_chain.size() - 2;
			flag_byte |= (1 << 7);
			fputc(flag_byte, w_file);
			for (auto iter = byte_chain.begin(); iter != byte_chain.end(); ++iter) {
				fputc(byte_chain.back(), w_file);
			}
			byte_chain.clear();
			byte_chain.push_back(byte);
			break;
		}
		func_flag = !func_flag;
	}
};

void zip() {

	FILE* file = fopen("salam.txt", "rb");
	FILE* archive = fopen("archive.imi", "ab+");

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

		if (byte = fgetc(archive) + 1 <= 128){
			chain_size = (int)byte + 1;
			for (int i = 0; i < chain_size; ++i) {
				byte = fgetc(archive);
				fputc(byte,file);
			}
		}
		else {
			byte &= ~(1 << 7);
			chain_size = (int)byte + 2;
			byte = fgetc(archive);
			for (int i = 0; i < chain_size; ++i) {
				fputc(byte, file);
			}
		}
	}
	fclose(file);
	fclose(archive);
};


int main() {


	zip();
	unzip();

	return 0;
}
