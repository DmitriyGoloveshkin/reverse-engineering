#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "brute_force.c"

#define MIN_PASSWORD_LEN 8

int calculate_password_control_sum(int* key, int strlen_key);


int main()
{
	signed long long rax = 0;
	signed long long rdx = 0;
	signed long long rcx = 0;
	int r8d = 0;
	int eax = 0;
	int edx = 0;
	int ecx = 0;

	char entered_password[20] = {0};
	int* extended_password = NULL;
	int password_length = 0;


	init_brute_force(MIN_PASSWORD_LEN);

	while (1) {
		brute_force(entered_password);
		password_length = strlen(entered_password);

		extended_password = malloc(password_length * 4);

		if (extended_password == NULL) {
			printf("Error: extended_password == NULL\n");
			return 0;
		}

		for (int i = 0; i < password_length; i++) {
			extended_password[i] = (int)entered_password[i];
		}

		rax = calculate_password_control_sum(extended_password, password_length);
		rdx = rax * 0x66666667;

		rdx = (unsigned long long)rdx >> 0x20;
		rdx = rdx >> 0x01;

		r8d = (int)rax;
		r8d = r8d >> 0x1f;

		edx = (int)rdx;
		ecx = edx - r8d;

		edx = ecx;
		edx = edx << 2;
		edx = edx + ecx;

		eax = (int)rax;
		eax = eax - edx;

		free(extended_password);

		if (eax == 3) {
			printf("password: %s\n", entered_password);
			// break;
		}

		memset(entered_password, 0, 20);
	}

	return 0;
}

int calculate_password_control_sum(int* key, int strlen_key)
{
	int generated_key = strlen_key;
	int a = 0x5;
	int b = 0x31f;
	int c = 0x331f;
	int d = 0x14ac3;

	int eax = 0;
	int edx = 0;
	int ecx = 0;

	for (int i = 0; i < MIN_PASSWORD_LEN; i++) {
		eax = a + c;
		ecx = key[i];
		edx = eax / ecx;
		eax = d + edx;
		edx = eax * b;
		eax = a + edx;
		generated_key += eax;
	}

	return generated_key;
}