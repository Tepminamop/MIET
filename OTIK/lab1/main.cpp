#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <vector>

using namespace std;

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
	uint8_t signature[6] = {0x69, 0x69, 0x6D, 0x61, 0x69, 0x61};

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
	while (fread(&one_byte, sizeof(one_byte), 1, file)) {
		fwrite(&one_byte, 1, 1, archive);
	}

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
	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
		fwrite(&one_byte, 1, 1, archive);
	}

	//close files
	fclose(archive);
	fclose(file);
}

int main() {
	bool mode;
	cout << "Input 0 if yow want to make archive from file, else input 1\n";
	cin >> mode;

	if (!mode) to_archive();
	else from_archive();

	return 0;
}
