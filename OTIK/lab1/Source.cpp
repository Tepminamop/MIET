//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <stdint.h>
//#include <windows.h>
//#include <vector>
//
//using namespace std;
//
//void to_archive() {
//	//input file_name
//	char archive_name[40];
//	int file_num;
//	cout << "Input archive name" << '\n';
//	cin >> archive_name;
//	cout << "Input file number" << '\n';
//	cin >> file_num;
//	char** files_name = new char* [file_num];
//	for (int i = 0; i < file_num; i++) {
//		cout << "Input " << i + 1 << " file name" << '\n';
//		files_name[i] = new char[40];
//		cin >> files_name[i];
//	}
//	//signature
//	uint8_t signature[6] = { 0x69, 0x69, 0x6D, 0x61, 0x69, 0x61 };
//	//open archive
//	FILE* archive = fopen(archive_name, "wb");
//	//write signature to archive
//	for (int i = 0; i < 6; i++)
//		fwrite(&signature[i], 1, 1, archive);
//	//write version to archive
//	uint8_t version = 0x01;
//	//write compress method code to archive
//	uint8_t code = 0x00;
//	//write stray code
//	uint8_t stray = 0x00;
//
//	fwrite(&version, 1, 1, archive);
//	fwrite(&code, 1, 1, archive);
//	fwrite(&stray, 1, 1, archive);
//	fwrite(&file_num, sizeof(int), 1, archive);
//
//	//many files
//	FILE** files = new FILE * [file_num];
//	uint8_t one_byte;
//	int file_size;
//	//write test file size to archive
//	for (int i = 0; i < file_num; i++) {
//		files[i] = fopen(files_name[i], "rb");
//		fseek(files[i], 0, SEEK_END); 
//		file_size = ftell(files[i]);
//		rewind(files[i]);
//		fwrite(&file_size, sizeof(int), 1, archive);
//		cout << file_size << endl;
//		//write file_name to archive
//		fwrite(files_name[i], 40, 1, archive);
//		//write data from file to archive
//		while (fread(&one_byte, sizeof(one_byte), 1, files[i])) {
//			fwrite(&one_byte, 1, 1, archive);
//		}
//		fclose(files[i]);
//	}
//	//close files
//	fclose(archive);
//	for (int i = 0; i < file_num; i++) {
//		delete files_name[i];
//	}
//	delete[] files_name;
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
//		if (current != signature[i]) {
//			cout << "error" << '\n';
//			return;
//		}
//	}
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
//	//read test file size from archive
//	uint32_t size;
//	char file_name[40];
//
//	uint32_t count;
//	fread(&count, sizeof(int), 1, archive);
//
//	//create file from archive
//	for (int j = 0; j < count; j++) {
//		fread(&size, sizeof(int), 1, archive);
//		fread(&file_name, 40, 1, archive);
//		FILE* file = fopen(file_name, "wb");
//		//write data from archive to file
//		for (uint32_t i = 0; i < size; i++) {
//			uint8_t one_byte;
//			fread(&one_byte, sizeof(one_byte), 1, archive);
//			fwrite(&one_byte, sizeof(one_byte), 1, file);
//		}
//		//close files
//		fclose(file);
//	}
//	fclose(archive);
//}
//
//int main() {
//	bool mode;
//	cout << "Input 0 if yow want to make archive from file, else input 1\n";
//	cin >> mode;
//	if (!mode) to_archive();
//	else from_archive();
//	return 0;
//}