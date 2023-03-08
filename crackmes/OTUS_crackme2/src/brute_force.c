/*
** Program to generate string by brute force
*/

#include <string.h>

#define VALID_SYMBOL_NUMBER 	62
#define STRING_LEN 				64

char valid_symbols[VALID_SYMBOL_NUMBER] = {0};
char indexes[STRING_LEN]  = {0};
char string[STRING_LEN+1] = {0};

int symbol_number = 0;
int len = 1;


void init_brute_force();
void create_string_by_indexes(char* indexes, int current_len, char* string);
int  brute_force(char* brute_force_string);
int  change_previos_index(int current_len);


void init_brute_force() 
{
	for (int i = 0; i < VALID_SYMBOL_NUMBER; i++) {
		if (i < 26) { valid_symbols[i] = 'A'+i; }
		else if (i < 52) { valid_symbols[i] = 'a'+i-26; }
		else {valid_symbols[i] = '0'+i-52; }
	}

	memset(indexes, 0, STRING_LEN);

	symbol_number = 0;
	len = 1;
}


void create_string_by_indexes(char* indexes, int current_len, char* string)
{
	for (int i = 0; i < current_len; i++) {
		string[i] = valid_symbols[indexes[i]];
	}
	string[current_len] = 0;
}

int brute_force(char* brute_force_string)
{
	int index = len-1;
	int err = 0;

	indexes[index] = symbol_number;
	create_string_by_indexes(indexes, len, brute_force_string);
	symbol_number++;
	if (symbol_number == VALID_SYMBOL_NUMBER) { 
		symbol_number = 0;
		err = change_previos_index(len);
		if (err == 1) {
			len++;
			if (len == STRING_LEN+1) {
				return -1;
			}
		}
	}

	return 0;
}


int change_previos_index(int current_len) 
{
	int index = current_len-1;
	indexes[index] = 0;
	if (current_len == 1) { return 1; }

	for (int j = index-1; j >= 0; j--) {
		if (indexes[j] == VALID_SYMBOL_NUMBER-1) {
			indexes[j] = 0;

			if (j == 0) {
				return 1;
			}
		} else {
			indexes[j]++;
			break;
		}
	}

	return 0;
}