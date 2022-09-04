#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdint.h>
#include <windows.h>
#include <vector>

using namespace std;

void to_archive() {
	FILE* file = fopen("test.txt", "rb");
	FILE* archive = fopen("archive.imi", "wb");
	uint8_t signature[6];
	signature[0] = 0x69;
	signature[1] = 0x69;
	signature[2] = 0x6D;
	signature[3] = 0x61;
	signature[4] = 0x69;
	signature[5] = 0x61;

	//write signature to archive
	for (int i = 0; i < 6; i++) {
		uint8_t current = signature[i];
		fwrite(&current, 1, 1, archive);
	}

	//write version to archive
	uint8_t version = 0x01;
	fwrite(&version, 1, 1, archive);

	//write test file size to archive
	FILE* test = fopen("test.txt", "rb");
	int file_size = 0;

	uint8_t one_byte;
	while (fread(&one_byte, sizeof(one_byte), 1, test)) {
		file_size++;

		if (one_byte == 0xFF) {
			break;
		}
	}
	fwrite(&file_size, sizeof(int), 1, archive);
	fclose(test);

	//write data from file to archive
	while (fread(&one_byte, sizeof(one_byte), 1, file)) {
		if (one_byte == 0xFF)
			break;
		else
			fwrite(&one_byte, 1, 1, archive);
	}

	fclose(archive);
	fclose(file);
}

void from_archive() {
	FILE* file = fopen("result.txt", "wb");
	FILE* archive = fopen("archive.imi", "rb");
	uint8_t signature[6];
	signature[0] = 0x69;
	signature[1] = 0x69;
	signature[2] = 0x6D;
	signature[3] = 0x61;
	signature[4] = 0x69;
	signature[5] = 0x61;

	//check archive signature
	for (int i = 0; i < 6; i++) {
		uint8_t current;
		fread(&current, 1, 1, archive);

		if (current != signature[i]) {
			cout << "error" << '\n';
			return;
		}
	}

	//cout file version
	uint8_t version;
	fread(&version, 1, 1, archive);

	//read test file size to archive
	uint32_t size;
	fread(&size, sizeof(int), 1, archive);

	//write data from archive to file
	for (uint32_t i = 0; i < size; i++) {
		uint8_t one_byte;
		fread(&one_byte, sizeof(one_byte), 1, archive);
		fwrite(&one_byte, sizeof(one_byte), 1, file);
	}

	uint8_t one_byte;
	while (fread(&one_byte, sizeof(one_byte), 1, archive)) {
		if (one_byte == 0xFF)
			break;
		else
			fwrite(&one_byte, 1, 1, archive);
	}


	fclose(archive);
	fclose(file);
}

int main() {
	to_archive();
	from_archive();

	return 0;
}
