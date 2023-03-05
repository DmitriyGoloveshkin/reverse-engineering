#include <stdio.h>
#include "brute_force.c"

#define LEN_NAME 74
#define LEN_PASSWORD 2*LEN_NAME


int form_name(char* name);
int control_sum_name(char* name);
int control_sum_password(char* password);


int main()
{
	int err = 0;

	int control_sum_name_value = 0;
	int control_sum_password_value = 0;

	char name[LEN_NAME] = {0};
	char password[LEN_PASSWORD] = {0};

	printf("Enter name: letter must be >= \'A\'\n");
	scanf("%s", name);

	err = form_name(name);
	if (err != 0) {
		printf("Name: %s is incorrect. Try again\n");
		return -1;
	}

	control_sum_name_value = control_sum_name(name);
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

int form_name(char* name)
{
	for (int i = 0; name[i] != 0; i++) {
		if (name[i] < 'A') {
			return -1;
		} else if (name[i] >= 'Z') {
			name[i] -= 0x20;
		}
	}

	return 0;
}

int control_sum_name(char* name)
{
	int sum = 0;

	for (int i = 0; name[i] != 0; i++) {
		sum += name[i];
	}

	return sum ^ 0x444C;	// 0x1234 xor 0x5678
}

int control_sum_password(char* password)
{
	int sum = 0;

	for (int i = 0; password[i] != 0; i++) {
		sum = (sum * 10) + (password[i] - 0x30);
	}

	return sum;
}

