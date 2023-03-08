#include <stdio.h>
#include <ctype.h>
#include "brute_force.c"

#define LEN_NAME 64
#define LEN_PASSWORD 2*LEN_NAME
#define MAGIC_NUMBER 0x0edb88320

int is_correct_input(char* string);
int control_sum_login(char* name);
int control_sum_password(char* password);


int main()
{
	int err = 0;

	int control_sum_name_value = 0;
	int control_sum_password_value = 0;

	char name[LEN_NAME] = {0};
	char password[LEN_PASSWORD] = {0};

	printf("Enter name: \n");
	scanf("%s", name);

	err = is_correct_input(name);
	if (err != 0) {
		printf("Name: %s is incorrect. Try again\n");
		return -1;
	}

	control_sum_name_value = control_sum_login(name);
	init_brute_force();

	while (1) {
		err = brute_force(password);
		control_sum_password_value = control_sum_password(password);
		if (control_sum_password_value == control_sum_name_value) {
			printf("Password found\n");
			printf("name:\t%s\n", name);
			printf("password\t%s\n", password);
			// comment out to not stop after finding the first password
			break;		
		}
		if (err == -1) { 
			printf("Password not found\n");
			break; 
		}
	}
	
	return 0;
}


int is_correct_input(char* string)
{
	while (*string != 0) {
		if (isdigit(*string) == 0 && isalpha(*string) == 0) {
			fprintf((stderr), "Incorrect symbol: %c\n", *string);
			return -1;
		}
		string++;
	}

	return 0;
}


int control_sum_login(char* login)
{
	int sum = 0xffffffff;

	for (int i = 0; login[i] != 0; i++) {
		sum ^= login[i];

		for (int j = 8; j > 0; j--) {
			sum = ((unsigned int)sum >> 1) ^ ((-1*(sum & 1)) & MAGIC_NUMBER);
		}
	}

	return ((~sum) & 0xff);
}

int control_sum_password(char* password)
{
	int sum = 0;

	for (int i = 0; password[i] != 0; i++) {
		sum += (password[i] ^ 0x99);
	}

	return (sum & 0xff);
}

