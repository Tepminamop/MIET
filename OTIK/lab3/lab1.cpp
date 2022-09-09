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

//workas for numbers between 0 and 1, number starts with 0.
string to_binary(double num, int precision) {
	string ans;
	for (int i = 0; i < precision; i++) {
		if (num == 0) break;

		num *= 2;
		if (num >= 1) {
			ans.push_back('1');
			num -= 1;
		}
		else {
			ans.push_back('0');
		}
	}

	return ans;
}

void to_archive() {
	//input file_name
	char file_name[40];
	char archive_name[40];
	cout << "Input filename" << '\n';
	cin >> file_name;
	cout << "Input archive name" << '\n';
	cin >> archive_name;

	//open files
	FILE* file = fopen(file_name, "rb");
	FILE* archive = fopen(archive_name, "wb");

	//signature
	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };

	//write signature to archive
	for (int i = 0; i < 6; i++)
		fwrite(&signature[i], 1, 1, archive);

	//write version to archive
	uint8_t version = 0x01;
	fwrite(&version, 1, 1, archive);

	//write test file size to archive
	FILE* test = fopen(file_name, "rb");
	int file_size = 0;

	uint8_t one_byte;
	while (fread(&one_byte, sizeof(one_byte), 1, test))
		file_size++;
	fwrite(&file_size, sizeof(int), 1, archive);

	//write file_name to archive
	fwrite(&file_name, 40, 1, archive);
	fclose(test);

	//write data from file to archive
	while (fread(&one_byte, sizeof(one_byte), 1, file))
		fwrite(&one_byte, 1, 1, archive);


	//close files
	fclose(archive);
	fclose(file);
}

void from_archive() {
	//input archive name
	char archive_name[40];
	cout << "Input archive name" << '\n';
	cin >> archive_name;

	//open archive
	FILE* archive = fopen(archive_name, "rb");

	//signature
	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };

	//check archive signature
	for (int i = 0; i < 6; i++) {
		uint8_t current;
		fread(&current, 1, 1, archive);

		if (current != signature[i]) {
			cout << "error" << '\n';
			return;
		}
	}

	//check file version
	uint8_t version;
	fread(&version, 1, 1, archive);

	//read test file size to archive
	uint32_t size;
	fread(&size, sizeof(int), 1, archive);

	//read file_name from archive
	char file_name[40];
	fread(&file_name, 40, 1, archive);

	//create file from archive
	FILE* file = fopen(file_name, "wb");

	//write data from archive to file
	for (uint32_t i = 0; i < size; i++) {
		uint8_t one_byte;
		fread(&one_byte, sizeof(one_byte), 1, archive);
		fwrite(&one_byte, sizeof(one_byte), 1, file);
	}

	//????
	uint8_t one_byte;
	while (fread(&one_byte, sizeof(one_byte), 1, archive))
		fwrite(&one_byte, 1, 1, archive);


	//close files
	fclose(archive);
	fclose(file);
}

void compress_archive() {
	//input archive name
	char archive_name[40];
	cout << "Input archive name" << '\n';
	cin >> archive_name;

	//open archive
	FILE* archive = fopen(archive_name, "rb");

	//signature
	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };

	//check archive signature
	for (int i = 0; i < 6; i++) {
		uint8_t current;
		fread(&current, 1, 1, archive);

		if (current != signature[i]) {
			cout << "error" << '\n';
			return;
		}
	}

	//check file version
	uint8_t version;
	fread(&version, 1, 1, archive);

	//read test file size to archive
	uint32_t size;
	fread(&size, sizeof(int), 1, archive);

	//read file_name from archive
	char file_name[40];
	fread(&file_name, 40, 1, archive);

	//посчитать частоту каждого байта (как в лр1 по зи) и записать частоту в мапу, сопоставить каждому байту свой код и записать это все в другую мапу, при декодирвоании находить первый (при чтении слева направо) набор символов, который удовлетворяет коду какого-го байта и записать в файл декодированный байт, проверить работоспособность

	//считываем байты из архива и находим частоту каждого байта, записывая в мапу
	map<uint8_t, double> frequency;//double чтобы потом поделить полученное значение на size

	for (uint32_t i = 0; i < size; i++) {
		uint8_t one_byte;
		fread(&one_byte, sizeof(one_byte), 1, archive);
		frequency[one_byte]++;
	}

	//переписываем частоты из мапы в вектор и соритруем по невозрастанию (greater or reverse) (vector<pair<double, byte>>)
	vector<pair<double, uint8_t>> px;

	for (auto const& x : frequency) {
		pair<double, uint8_t> pair;
		pair.first = x.second / size;
		pair.second = x.first;
		px.push_back(pair);
	}
	sort(px.begin(), px.end(), std::greater<pair<double, uint8_t>>());

	//нашли массив Px, теперь найдем массив Bx (формулы на сайте)
	vector<pair<double, uint8_t>> bx(px.size(), { 0, 0 });
	bx[0].second = px[0].second;
	for (int i = 1; i < bx.size(); i++) {
		bx[i].first = bx[i - 1].first + px[i - 1].first;
		bx[i].second = px[i].second;
	}

	//переводим bx в двоичную систему
	vector<pair<string, uint8_t>> binary_bx;
	for (int i = 0; i < bx.size(); i++) {
		string binary = to_binary(bx[i].first, 30);
		binary_bx.push_back({ binary, bx[i].second });
	}

	//считаем Lx по формуле (Lx = cell(-log(px)))
	vector<pair<uint8_t, int>> lx;
	for (int i = 0; i < px.size(); i++) {
		int l = ceil(-log(px[i].first));
		lx.push_back({ px[i].second, l });
	}

	//записываем коды в мапу
	map<uint8_t, string> byte_to_code;
	map<string, uint8_t> code_to_byte;

	for (int i = 0; i < lx.size(); i++) {
		string code;
		for (int j = 0; j < lx[i].second; j++) {
			code.push_back(binary_bx[i].first[j]);
		}
		byte_to_code[lx[i].first] = code;
		code_to_byte[code] = lx[i].first;
	}

	//
	//сожмем архив и запишем результат в отдельынй файл
	//

	//open old archive amd new archive
	char compressed_archive_name[40];
	cout << "input compressed archive name" << '\n';
	cin >> compressed_archive_name;
	FILE* old_archive = fopen(archive_name, "rb");

	//check old archive signature
	for (int i = 0; i < 6; i++) {
		uint8_t current;
		fread(&current, 1, 1, old_archive);

		if (current != signature[i]) {
			cout << "error" << '\n';
			return;
		}
	}

	//check old file version
	uint8_t old_version;
	fread(&old_version, 1, 1, old_archive);

	//read test file size from old archive
	uint32_t old_size;
	fread(&old_size, sizeof(int), 1, old_archive);

	//read file_name from old archive
	char old_file_name[40];
	fread(&old_file_name, 40, 1, old_archive);

	FILE* compressed_archive = fopen(compressed_archive_name, "wb");

	//write signature to compressed archive
	for (int i = 0; i < 6; i++)
		fwrite(&signature[i], 1, 1, compressed_archive);

	//write version to compressed archive
	fwrite(&old_version, 1, 1, compressed_archive);

	//write file size to compressed archive
	fwrite(&old_size, sizeof(int), 1, compressed_archive);

	//write file_name to compressed archive
	fwrite(&old_file_name, 40, 1, compressed_archive);

	//compressing
	bitset<8> byte;
	int pointer = 7;
	for (uint32_t i = 0; i < old_size; i++) {
		uint8_t one_byte;
		fread(&one_byte, sizeof(one_byte), 1, old_archive);
		//write with codes
		string code = byte_to_code[one_byte];
		for (int j = 0; j < code.size(); j++) {
			if (pointer < 0) {
				pointer = 7;
				unsigned long ulong = byte.to_ulong();
				byte.reset();
				unsigned char c = static_cast<unsigned char>(ulong);
				fwrite(&c, 1, 1, compressed_archive);
			}

			if (code[j] == '1') {
				byte[pointer] = 1;
				pointer--;
			}
			else {
				byte[pointer] = 0;
				pointer--;
			}
		}
	}

	if (pointer != 7) {
		pointer = 7;
		unsigned long ulong = byte.to_ulong();
		byte.reset();
		unsigned char c = static_cast<unsigned char>(ulong);
		fwrite(&c, 1, 1, compressed_archive);
	}

	//end?
}

void decompress_archive() {

}

int main() {
	//to binary
	/*
	double a = 1.0;
	unsigned long long bx = 0;
	// убедимся, что у нас они одинакового размера.
	static_assert(sizeof(a) == sizeof(bx), "sizeof(double) == sizeof(ull)");
	// скопируем. Умные компиляторы могут сделать этот код не хуже сишного каста
	std::memcpy(&bx, &a, sizeof(bx));
	// а дальше уже по классике
	auto b = std::bitset<64>(bx);
	cout << b << '\n';
	*/

	bool mode;
	cout << "Input 0 if yow want to make archive from file, else input 1\n";
	cin >> mode;

	if (!mode) to_archive();
	else from_archive();

	bool mode_compress;
	cout << "Input 0 if yow want to compress archive, else input 1\n";
	cin >> mode_compress;

	if (!mode_compress) compress_archive();
	else decompress_archive();

	return 0;
}
