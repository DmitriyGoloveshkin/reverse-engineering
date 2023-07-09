// Solution: Enter the number 65

#include <stdio.h>

int main()
{
	char array[7] = {0};

	array[0] = 0x22;
	array[1] = 0x33;
	array[2] = 0x20;
	array[3] = 0x22;
	array[4] = 0x2a;
	array[5] = 0x2c;
	array[6] = 0x24;

	int data = 0x0;

	for (int i = 0; i < 256; i++) {
		printf("\n%4d. ", i);
		putchar(array[0] ^ i);
		putchar(array[1] ^ i);
		putchar(array[2] ^ i);
		putchar(array[3] ^ i);
		putchar(array[4] ^ i);
		putchar(array[5] ^ i);
		putchar(array[6] ^ i);
	}

	return 0;
}