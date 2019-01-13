#pragma once
#include "../lab.h"

int search_in_file(char *filename, char *word);
int replace_in_file(char *filename, char *old_word, char *new_word);
int sort_file_ascii(char *filename);
int get_filesize(char *filename);
void get_additional_filedata(char *filename, int *data);