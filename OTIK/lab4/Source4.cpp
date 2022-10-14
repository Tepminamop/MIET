//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <stdint.h>
//#include <windows.h>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <bitset>
//#include <cmath>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include <math.h>
//
//using namespace std;
//
//int write_bchain(bool& func_flag, unsigned char byte, FILE* w_file, std::vector<unsigned char>& byte_chain) {
//
//	if (byte_chain.size() > 128) {
//
//		switch (func_flag)
//		{
//			unsigned char flag_byte;
//		case 0:
//			flag_byte = 127;
//			fputc(flag_byte, w_file);
//			for (int i = 0; i < 128; i++) {
//				fputc(byte_chain[0], w_file);
//				byte_chain.erase(byte_chain.begin());
//			}
//			write_bchain(func_flag, byte, w_file, byte_chain);
//			break;
//
//		case 1:
//			flag_byte = 255;
//			fputc(flag_byte, w_file);
//			fputc(byte_chain.back(), w_file);
//			for (int i = 0; i < 129; i++) {
//				byte_chain.erase(byte_chain.begin());
//			}
//			write_bchain(func_flag, byte, w_file, byte_chain);
//			break;
//		}
//	}
//	else {
//		switch (func_flag)
//		{
//			unsigned char flag_byte;
//
//		case 0:
//			flag_byte = byte_chain.size() - 1;
//			fputc(flag_byte, w_file);
//			for (auto iter = byte_chain.begin(); iter != byte_chain.end(); ++iter) {
//				fputc(*iter, w_file);
//			}
//			byte_chain.clear();
//			byte_chain.push_back(byte);
//			byte_chain.push_back(byte);
//			break;
//		case 1:
//			flag_byte = byte_chain.size() - 2;
//			flag_byte |= (1 << 7);
//			fputc(flag_byte, w_file);
//			fputc(byte_chain.back(), w_file);
//			byte_chain.clear();
//			byte_chain.push_back(byte);
//			break;
//		}
//		func_flag = !func_flag;
//	}
//
//	return 0;
//};
//
//void zip(char file_name[40]) {
//	FILE* file = fopen(file_name, "rb");
//	FILE* archive = fopen("archive.imi", "wb");
//
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//write signature to archive
//	for (int i = 0; i < 6; i++) {
//		fputc(signature[i], archive);
//	}
//
//	unsigned char byte;
//
//	std::vector<unsigned char> byte_chain;
//
//	bool func_flag = 0;
//
//	while (!feof(file)) {
//
//		byte = fgetc(file);
//
//		if (!feof(file)) {
//
//			switch (func_flag) {
//
//			case 0:
//				if (byte_chain.size() == 0 || byte != byte_chain.back()) {
//					byte_chain.push_back(byte);
//				}
//				else if (byte_chain.size() > 1) {
//					byte_chain.pop_back();
//					write_bchain(func_flag, byte, archive, byte_chain);
//				}
//				else {
//					byte_chain.push_back(byte);
//					func_flag = !func_flag;
//				}
//				break;
//			case 1:
//				if (byte == byte_chain.back()) {
//					byte_chain.push_back(byte);
//				}
//				else {
//					write_bchain(func_flag, byte, archive, byte_chain);
//				}
//				break;
//			}
//		}
//	}
//
//	if (!byte_chain.empty()) {
//		write_bchain(func_flag, 0, archive, byte_chain);
//	}
//	fclose(file);
//	fclose(archive);
//};
//
//void unzip() {
//	FILE* archive = fopen("archive.imi", "rb");
//	FILE* file = fopen("unzip", "wb");
//
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//check archive signature
//	for (int i = 0; i < 6; i++) {
//		uint8_t current;
//		fread(&current, 1, 1, archive);
//
//		if (current != signature[i]) {
//			std::cout << "error" << std::endl;
//			return;
//		}
//	}
//
//	unsigned char byte;
//	int chain_size;
//
//	while (!feof(archive)) {
//
//		byte = fgetc(archive);
//
//		if (!feof(archive)) {
//			if ((int)byte <= 127) {
//				chain_size = (int)byte + 1;
//				for (int i = 0; i < chain_size; ++i) {
//					byte = fgetc(archive);
//					//std::cout << (int)byte << " ";
//					fputc(byte, file);
//				}
//			}
//			else {
//				byte &= ~(1 << 7);
//				chain_size = (int)byte + 2;
//				byte = fgetc(archive);
//				for (int i = 0; i < chain_size; ++i) {
//					fputc(byte, file);
//					//std::cout << (int)byte << " ";
//				}
//			}
//		}
//	}
//	fclose(file);
//	fclose(archive);
//};
//
//size_t byte_of_file(char file_name[40]) {
//	std::ifstream file(file_name); // ôàéë
//
//	size_t s = 0; // ñ÷åò÷èê ñèìâîëîâ
//	if (!(file.is_open())) {
//		std::cout << "File not found" << std::endl;
//	}
//	while (!file.eof()) { // ïîêà íå äîñòèãíóò êîíåö ôàéëâ
//		file.get();       // ÷èòàòü ïî îäíîìó ñèìâîëó
//		s++;              // è óâåëè÷èâàòü ñ÷åò÷èê
//	}
//
//	file.close(); // îáÿçàòåëüíî çàêðûòü
//
//	s--; // óáèðàåì ëèøíþþ èòåðàöèþ
//
//	return s; // âåðíóòü ÷èñëî ñèìâîëîâ/áàéòîâ
//}
//
//void smart_archive(char file_name[40]) {
//	zip(file_name);
//	size_t file_s = byte_of_file(file_name);
//	char archive_name[40] = "archive.imi";
//	size_t archive_s = byte_of_file(archive_name);
//
//	if (archive_s > file_s) {
//		FILE* file = fopen(file_name, "rb");
//		FILE* archive = fopen("archive.imi", "wb");
//		while (!feof(file)) {
//			unsigned char byte = fgetc(file);
//			if (!feof(file)) {
//				fputc(byte, archive);
//			}
//		}
//	}
//	else {
//		unzip();
//	}
//}
//
//int entrances_ij_string(char path[40]) {
//	char aiaj[2];
//	std::cout << "Input ai: ";
//	std::cin >> aiaj[0];
//	std::cout << "Input aj: ";
//	std::cin >> aiaj[1];
//
//	std::string s1, s2 = "", s3 = "";
//
//	s2 += aiaj[0]; s2 += aiaj[1];
//
//	size_t cnt = 0;
//	std::ifstream file(path); // ôàéë
//
//	if (!(file.is_open())) {
//		std::cout << "File not found" << std::endl;
//	}
//
//	int arr[256] = {};
//
//	while (getline(file, s1)) {
//
//		for (std::string::size_type i = 0; i < s1.length(); ++i) {
//			if (s1[i] == s2[0])
//				if (s1.substr(i, s2.length()) == s2) {
//					++cnt;
//				}
//		}
//		for (int k = 0; k < 255; ++k) {
//			unsigned char ai = k;
//			s3 = aiaj[1];
//			s3 += ai;
//			for (std::string::size_type i = 0; i < s1.length(); ++i) {
//				if (s1[i] == s3[0])
//					if (s1.substr(i, s3.length()) == s3) {
//						arr[k]++;
//					}
//			}
//		}
//
//	}
//	for (int k = 0; k < 255; ++k) {
//		unsigned char ai = k;
//		if (arr[k] > 0) {
//			std::cout << aiaj[1] << ai << "= " << arr[k] << "; ";
//		}
//	}
//
//	file.close();
//	std::cout << cnt;
//	return 0;
//}
//
//int probability(char file_name[40]) {
//	char ai, aj;
//	std::cout << "Input ai: ";
//	std::cin >> ai;
//	std::cout << "Input aj: ";
//	std::cin >> aj;
//
//	std::ifstream file(file_name); // ôàéë
//
//	double aj_s = 0, ai_s = 0; // ñ÷åò÷èê ñèìâîëîâ
//	double ret1, ret2;
//	if (!(file.is_open())) {
//		std::cout << "File not found" << std::endl;
//	}
//	while (!file.eof()) { // ïîêà íå äîñòèãíóò êîíåö ôàéëâ
//		char scan = file.get();// ÷èòàòü ïî îäíîìó ñèìâîëó
//		if (!file.eof() && scan == aj) {
//			aj_s++;              // è óâåëè÷èâàòü ñ÷åò÷èê
//		}
//
//		if (!file.eof() && scan == ai) {
//			ai_s++;              // è óâåëè÷èâàòü ñ÷åò÷èê
//		}
//
//	}
//	file.close();
//
//	double file_s = byte_of_file(file_name);
//
//	std::cout << ai_s << " " << aj_s << " " << file_s << std::endl;
//
//	ret2 = ((ai_s / file_s) * (aj_s / (file_s - 1))) / (aj_s / (file_s - 1));
//	std::cout << "(ai|aj)= " << ret2 << std::endl;
//	ret1 = (double)(ai_s / file_s);
//	std::cout << "ai= " << ret1 << std::endl;
//	return 0;
//}
//
//int information_s(char file_name[40]) {
//
//	double bytes = byte_of_file(file_name);
//	std::string s1;
//	int arr[256] = {};
//	double infromation = 0;
//
//	std::ifstream file(file_name); // ôàéë
//
//	if (!(file.is_open())) {
//		std::cout << "File not found" << std::endl;
//	}
//
//	while (getline(file, s1)) {
//
//
//		for (int k = 0; k < 255; ++k) {
//			unsigned char ai = k;
//			for (std::string::size_type i = 0; i < s1.length(); ++i) {
//				if (s1[i] == k)
//					arr[k]++;
//			}
//		}
//
//	}
//
//	for (int k = 0; k < 255; ++k) {
//		if (arr[k] > 0) {
//			infromation += -1 * (log((double)arr[k] / bytes) / (log(2)));
//			//infromation += -1 * (log((double)arr[k] / 256) / (log(2)));
//		}
//	}
//
//	std::cout << "Information = " << infromation << std::endl;
//
//	return 0;
//}
//
////works for numbers between 0 and 1, number starts with 0.
//string to_binary(double num, int precision) {
//	string ans;
//	for (int i = 0; i < precision; i++) {
//		if (num == 0) break;
//
//		num *= 2;
//		if (num >= 1) {
//			ans.push_back('1');
//			num -= 1;
//		}
//		else {
//			ans.push_back('0');
//		}
//	}
//
//	return ans;
//}
//
//void to_archive() {
//	//input file_name
//	char file_name[40];
//	char archive_name[40];
//	cout << "Input filename" << '\n';
//	cin >> file_name;
//	cout << "Input archive name" << '\n';
//	cin >> archive_name;
//
//	//open files
//	FILE* file = fopen(file_name, "rb");
//	FILE* archive = fopen(archive_name, "wb");
//
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//write signature to archive
//	for (int i = 0; i < 6; i++)
//		fwrite(&signature[i], 1, 1, archive);
//
//	//write version to archive
//	uint8_t version = 0x01;
//	fwrite(&version, 1, 1, archive);
//
//	//write compress method code to archive
//	uint8_t code = 0x01;
//	//write stray code
//	uint8_t stray = 0x00;
//
//	fwrite(&code, 1, 1, archive);
//	fwrite(&stray, 1, 1, archive);
//
//	//write test file size to archive
//	FILE* test = fopen(file_name, "rb");
//	int file_size = 0;
//
//	uint8_t one_byte;
//	while (fread(&one_byte, sizeof(one_byte), 1, test))
//		file_size++;
//	fwrite(&file_size, sizeof(int), 1, archive);
//
//	//write file_name to archive
//	fwrite(&file_name, 40, 1, archive);
//	fclose(test);
//
//	//write data from file to archive
//	while (fread(&one_byte, sizeof(one_byte), 1, file))
//		fwrite(&one_byte, 1, 1, archive);
//
//
//	//close files
//	fclose(archive);
//	fclose(file);
//}
//
//void from_archive() {
//	//input archive name
//	char archive_name[40];
//	cout << "Input archive name" << '\n';
//	cin >> archive_name;
//
//	//open archive
//	FILE* archive = fopen(archive_name, "rb");
//
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//check archive signature
//	for (int i = 0; i < 6; i++) {
//		uint8_t current;
//		fread(&current, 1, 1, archive);
//
//		if (current != signature[i]) {
//			cout << "error" << '\n';
//			return;
//		}
//	}
//
//	//check file version
//	uint8_t version;
//	fread(&version, 1, 1, archive);
//
//	//check compress code version
//	uint8_t code;
//	fread(&code, 1, 1, archive);
//
//	//check stray code version
//	uint8_t stray;
//	fread(&stray, 1, 1, archive);
//
//	//read test file size to archive
//	uint32_t size;
//	fread(&size, sizeof(int), 1, archive);
//
//	//read file_name from archive
//	char file_name[40];
//	fread(&file_name, 40, 1, archive);
//
//	//create file from archive
//	FILE* file = fopen(file_name, "wb");
//
//	//write data from archive to file
//	for (uint32_t i = 0; i < size; i++) {
//		uint8_t one_byte;
//		fread(&one_byte, sizeof(one_byte), 1, archive);
//		fwrite(&one_byte, sizeof(one_byte), 1, file);
//	}
//
//	//????
//	uint8_t one_byte;
//	while (fread(&one_byte, sizeof(one_byte), 1, archive))
//		fwrite(&one_byte, 1, 1, archive);
//
//
//	//close files
//	fclose(archive);
//	fclose(file);
//}
//
//int compress_archive(map<uint8_t, string>& byte_to_code, map<string, uint8_t>& code_to_byte) {
//	//input archive name
//	char archive_name[40];
//	cout << "Input archive name" << '\n';
//	cin >> archive_name;
//
//	//open archive
//	FILE* archive = fopen(archive_name, "rb");
//
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//check archive signature
//	for (int i = 0; i < 6; i++) {
//		uint8_t current;
//		fread(&current, 1, 1, archive);
//
//		if (current != signature[i]) {
//			cout << "error" << '\n';
//			return -1;
//		}
//	}
//
//	//check file version
//	uint8_t version;
//	fread(&version, 1, 1, archive);
//
//	//check compress code version
//	uint8_t code;
//	fread(&code, 1, 1, archive);
//
//	//check stray code version
//	uint8_t stray;
//	fread(&stray, 1, 1, archive);
//
//	//read test file size to archive
//	uint32_t size;
//	fread(&size, sizeof(int), 1, archive);
//
//	//read file_name from archive
//	char file_name[40];
//	fread(&file_name, 40, 1, archive);
//
//	code = 0x02;
//	if (code == 0x01) {
//
//	}
//	else if (code == 0x00) {
//		from_archive();
//		return 0;
//	}
//	else if (code == 0x02) {
//		smart_archive(file_name);
//		return 2;
//	}
//	else {
//		cout << "invalid code";
//		return -1;
//	}
//
//	map<uint8_t, double> frequency;
//
//	for (uint32_t i = 0; i < size; i++) {
//		uint8_t one_byte;
//		fread(&one_byte, sizeof(one_byte), 1, archive);
//		frequency[one_byte]++;
//	}
//
//	vector<pair<double, uint8_t>> px;
//
//	for (auto const& x : frequency) {
//		pair<double, uint8_t> pair;
//		pair.first = x.second / size;
//		pair.second = x.first;
//		px.push_back(pair);
//	}
//	sort(px.begin(), px.end(), std::greater<pair<double, uint8_t>>());
//
//	vector<pair<double, uint8_t>> bx(px.size(), { 0, 0 });
//	bx[0].second = px[0].second;
//	for (int i = 1; i < bx.size(); i++) {
//		bx[i].first = bx[i - 1].first + px[i - 1].first;
//		bx[i].second = px[i].second;
//	}
//
//	vector<pair<string, uint8_t>> binary_bx;
//	binary_bx.push_back({ "000000000000000000000000000000", bx[0].second });
//	for (int i = 1; i < bx.size(); i++) {
//		string binary = to_binary(bx[i].first, 30);
//		binary_bx.push_back({ binary, bx[i].second });
//	}
//
//	//(Lx = ceil(-log(px)))
//	vector<pair<uint8_t, int>> lx;
//	for (int i = 0; i < px.size(); i++) {
//		int l = ceil(-1 * log(px[i].first) / log(2));
//		lx.push_back({ px[i].second, l });
//	}
//
//	for (int i = 0; i < lx.size(); i++) {
//		string code;
//		for (int j = 0; j < lx[i].second; j++) {
//			code.push_back(binary_bx[i].first[j]);
//		}
//		byte_to_code[lx[i].first] = code;
//		code_to_byte[code] = lx[i].first;
//	}
//
//	//open old archive amd new archive
//	char compressed_archive_name[40];
//	cout << "input compressed archive name" << '\n';
//	cin >> compressed_archive_name;
//	FILE* old_archive = fopen(archive_name, "rb");
//
//	//check old archive signature
//	for (int i = 0; i < 6; i++) {
//		uint8_t current;
//		fread(&current, 1, 1, old_archive);
//
//		if (current != signature[i]) {
//			cout << "error" << '\n';
//			return -1;
//		}
//	}
//
//	//check old file version
//	uint8_t old_version;
//	fread(&old_version, 1, 1, old_archive);
//
//	//check compress code version
//	uint8_t old_code;
//	fread(&old_code, 1, 1, old_archive);
//
//	//check stray code version
//	uint8_t old_stray;
//	fread(&old_stray, 1, 1, old_archive);
//
//	//read test file size from old archive
//	uint32_t old_size;
//	fread(&old_size, sizeof(int), 1, old_archive);
//
//	//read file_name from old archive
//	char old_file_name[40];
//	fread(&old_file_name, 40, 1, old_archive);
//
//	FILE* compressed_archive = fopen(compressed_archive_name, "wb");
//
//	//write signature to compressed archive
//	for (int i = 0; i < 6; i++)
//		fwrite(&signature[i], 1, 1, compressed_archive);
//
//	//write version to compressed archive
//	fwrite(&old_version, 1, 1, compressed_archive);
//
//	fwrite(&old_code, 1, 1, compressed_archive);
//	fwrite(&old_stray, 1, 1, compressed_archive);
//
//	//write file size to compressed archive
//	fwrite(&old_size, sizeof(int), 1, compressed_archive);
//
//	//write file_name to compressed archive
//	fwrite(&old_file_name, 40, 1, compressed_archive);
//
//	//compressing
//	bitset<8> byte;
//	int pointer = 0;
//	for (uint32_t i = 0; i < old_size; i++) {
//		uint8_t one_byte;
//		fread(&one_byte, sizeof(one_byte), 1, old_archive);
//		//write with codes
//		string code = byte_to_code[one_byte];
//		for (int j = 0; j < code.size(); j++) {
//			if (pointer > 7) {
//				pointer = 0;
//				unsigned long ulong = byte.to_ulong();
//				byte.reset();
//				unsigned char c = static_cast<unsigned char>(ulong);
//				fwrite(&c, 1, 1, compressed_archive);
//			}
//
//			if (code[j] == '1') {
//				byte[pointer] = 1;
//				pointer++;
//			}
//			else {
//				byte[pointer] = 0;
//				pointer++;
//			}
//		}
//	}
//
//	if (pointer <= 7) {
//		pointer = 7;
//		unsigned long ulong = byte.to_ulong();
//		byte.reset();
//		unsigned char c = static_cast<unsigned char>(ulong);
//		fwrite(&c, 1, 1, compressed_archive);
//	}
//
//	//end
//	fclose(archive);
//	fclose(old_archive);
//	fclose(compressed_archive);
//
//	FILE* file_dec = fopen(compressed_archive_name, "rb");
//	fseek(file_dec, 0, SEEK_END);
//	long int file_size = ftell(file_dec);
//	fclose(file_dec);
//	cout << file_size << " " << old_size << '\n';
//	if (file_size > old_size) {
//		cout << "dop" << '\n';
//
//		FILE* not_compressed_archive = fopen(compressed_archive_name, "wb");
//		FILE* not_archive = fopen(archive_name, "rb");
//		uint8_t one_byte;
//		while (fread(&one_byte, sizeof(one_byte), 1, not_archive)) {
//			fwrite(&one_byte, 1, 1, not_compressed_archive);
//		}
//
//		fclose(compressed_archive);
//		fclose(archive);
//	}
//
//	return 1;
//}
//
////stop with file size
//void decompress_archive(map<uint8_t, string>& byte_to_code, map<string, uint8_t>& code_to_byte) {
//	//input archive name
//	char archive_name[40];
//	cout << "Input compressed archive name" << '\n';
//	cin >> archive_name;
//
//	//open archive
//	FILE* archive = fopen(archive_name, "rb");
//
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//
//	//check archive signature
//	for (int i = 0; i < 6; i++) {
//		uint8_t current;
//		fread(&current, 1, 1, archive);
//
//		if (current != signature[i]) {
//			cout << "error" << '\n';
//			return;
//		}
//	}
//
//	//check file version
//	uint8_t version;
//	fread(&version, 1, 1, archive);
//
//	//check compress code version
//	uint8_t code;
//	fread(&code, 1, 1, archive);
//
//	//check stray code version
//	uint8_t stray;
//	fread(&stray, 1, 1, archive);
//
//	//read test file size to archive
//	uint32_t size;
//	fread(&size, sizeof(int), 1, archive);
//
//	//read file_name from archive
//	char file_name[40];
//	fread(&file_name, 40, 1, archive);
//
//	//create decompressed archive from compressed archive
//	char decompressed_archive_name[40];
//	cout << "Input decompressed archive name" << '\n';
//	cin >> decompressed_archive_name;
//	FILE* decompressed_archive = fopen(decompressed_archive_name, "wb");
//
//	//write data from archive to decomressed file
//	//write signature to decompressed archive
//	for (int i = 0; i < 6; i++)
//		fwrite(&signature[i], 1, 1, decompressed_archive);
//
//	//write version to decompressed archive
//	fwrite(&version, 1, 1, decompressed_archive);
//
//	fwrite(&code, 1, 1, decompressed_archive);
//	fwrite(&stray, 1, 1, decompressed_archive);
//
//	//write file size to decompressed archive
//	fwrite(&size, sizeof(int), 1, decompressed_archive);
//
//	//write file_name to decompressed archive
//	fwrite(&file_name, 40, 1, decompressed_archive);
//
//	uint8_t one_byte;
//	string all_bits;
//	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
//		bitset<8> byte(one_byte);
//		for (int i = 0; i < 8; i++) {
//			if (byte[i] == 1) {
//				all_bits.push_back('1');
//			}
//			else {
//				all_bits.push_back('0');
//			}
//		}
//	}
//	cout << all_bits.size() << endl;
//	string tmp;
//	int count = size;
//	for (int i = 0; i < all_bits.size(); i++) {
//		if (count == 0) break;
//		tmp.push_back(all_bits[i]);
//		if (code_to_byte.find(tmp) != code_to_byte.end()) {
//			fwrite(&code_to_byte[tmp], 1, 1, decompressed_archive);
//			count--;
//			tmp.clear();
//		}
//	}
//
//	//close files
//	fclose(archive);
//	fclose(decompressed_archive);
//}
//
//int main() {
//	int mode;
//	cout << "Input 0 if yow want to make archive from file, else input 1\n";
//	cin >> mode;
//
//	to_archive();
//
//	map<uint8_t, string> byte_to_code;
//	map<string, uint8_t> code_to_byte;
//	int mode_compress;
//	cout << "Input 0 if yow want to compress archive, else input 1\n";
//	cin >> mode_compress;
//	cout << "compress archive" << '\n';
//	int res = compress_archive(byte_to_code, code_to_byte);
//	if (res == 0) {
//		from_archive();
//	}
//	else if (res == 1) {
//		decompress_archive(byte_to_code, code_to_byte);
//	}
//	else if (res == 2) {
//		return 0;
//	}
//	else {
//		return 0;
//	}
//
//	return 0;
//}
