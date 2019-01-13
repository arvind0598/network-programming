#include "server.h"

int search_in_file(char *filename, char *word) {
	char command[50];
	sprintf(command, "grep -o -i %s %s | wc -l", word, filename);
	int count = get_popen_result(command);
	return count;
}

int replace_in_file(char *filename, char *old_word, char *new_word) {
	int wordcount = search_in_file(filename, old_word);
	if(wordcount < 1) return 0;
	
	char command[50];
	sprintf(command, "sed -i 's/%s/%s/g' %s", old_word, new_word, filename);
	system(command);
	return 1;
}

int sort_file_ascii(char *filename) {
	char command[50];
	sprintf(command, "cat %s | grep -o . | sort | tr -d '\n' > %s", filename, filename);
	system(command);
	return 1;
}

int get_filesize(char *filename) {
	char command[50];
	sprintf(command, "wc -c %s", filename);
	int count = get_popen_result(command);
	return count;
}

void get_additional_filedata(char *filename, int *data) {
	FILE *output = NULL;

	char alphabets[50];
	sprintf(alphabets, "cat %s | grep -o '[a-zA-Z]' | wc -l", filename);
	data[0] = get_popen_result(alphabets);

	char lines[50];
	sprintf(lines, "wc -l < %s", filename);
	data[1] = get_popen_result(lines);

	char spaces[50];
	sprintf(spaces, "cat %s | grep -o ' ' | wc -l", filename);
	data[2] = get_popen_result(spaces);

	char numbers[50];
	sprintf(numbers, "cat %s | grep -o '[0-9]' | wc -l", filename);
	data[3] = get_popen_result(numbers);

	data[4] = get_filesize(filename) - (data[0] + data[1] + data[2] + data[3]);
}