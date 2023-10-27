#include <stdio.h>

#define XOR_CONST_HIGH 0x00112233
#define XOR_CONST_LOW  0x44332211
#define MUL_CONST 0xFFFFFFFF80008001

#define MASK_UINT32 0xffffffff
#define MASK_UINT16 0xffff

#define SOLUTION_NUMBER 100

int main()
{
	unsigned int user_password_main = 0;
	unsigned int user_password = 0;
	unsigned short int bytes_7_6 = 0;
	unsigned short int bytes_5_4 = 0;

	long long int rax = 0;
	long long int rdx = 0;

	unsigned int high_bytes[SOLUTION_NUMBER] = {0};
	unsigned int  low_bytes[SOLUTION_NUMBER] = {0};

	int high_bytes_index = 0;
	int  low_bytes_index = 0;

	int eax = 0;
	int ecx = 0;
	int edx = 0;

	unsigned long long int result = 0;

	// calculate first SOLUTION_NUMBER high bytes
	user_password_main = 0;
	while (user_password_main <= MASK_UINT32 && high_bytes_index < SOLUTION_NUMBER) {
		user_password = user_password_main ^ XOR_CONST_HIGH;
		bytes_7_6 = (user_password >> 0x10) & MASK_UINT16;
		bytes_5_4 = user_password & MASK_UINT16;

		rdx = ((bytes_7_6 ^ bytes_5_4) & MASK_UINT32) * bytes_5_4;
		
		rax = bytes_7_6 * (rdx & MASK_UINT32);
		eax = rax & MASK_UINT32;

		rdx = eax;
		rdx = (rdx * MUL_CONST) >> 0x20;
		edx = (rdx & MASK_UINT32) + eax;

		edx >>= 0x0f;
		ecx = eax;
		ecx >>= 0x1f;

		edx -= ecx;
		ecx = edx << 0x10;
		ecx -= edx;
		eax -= ecx;
		edx = eax;
		
		if (edx == 0xDEAD) {
			high_bytes[high_bytes_index++] = user_password_main;
		}

		user_password_main++;
	}

	// calculate first SOLUTION_NUMBER low bytes
	user_password_main = 0;
	while (user_password_main <= MASK_UINT32 && low_bytes_index < SOLUTION_NUMBER) {
		user_password = user_password_main ^ XOR_CONST_LOW;
		bytes_7_6 = (user_password >> 0x10) & MASK_UINT16;
		bytes_5_4 = user_password & MASK_UINT16;

		rdx = ((bytes_7_6 ^ bytes_5_4) & MASK_UINT32) * bytes_5_4;
		
		rax = bytes_7_6 * (rdx & MASK_UINT32);
		eax = rax & MASK_UINT32;

		rdx = eax;
		rdx = (rdx * MUL_CONST) >> 0x20;
		edx = (rdx & MASK_UINT32) + eax;

		edx >>= 0x0f;
		ecx = eax;
		ecx >>= 0x1f;

		edx -= ecx;
		ecx = edx << 0x10;
		ecx -= edx;
		eax -= ecx;
		edx = eax;
		
		if (edx == 0xBEEF) {
			low_bytes[low_bytes_index++] = user_password_main;
		}

		user_password_main++;
	}

	// print results
	for (int i = 0; i < SOLUTION_NUMBER; i++) {
		result = ((unsigned long long int)high_bytes[i] << 32);
		for (int j = 0; j < SOLUTION_NUMBER; j++) {
			result &= 0xffffffff00000000;
			result |= low_bytes[j];

			printf("%llu\n", result);
		}
	}

	return 0;
}