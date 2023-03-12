.data 
	value:				.word 	0x7aaaaaaf
	# value:				.word 	0xaf
	bin_str_len:		.word 	33
	binary_string:		.space 	33
	quat_str_len:		.word 	17
	queaternary_string:	.space 	17
	oct_str_len:		.word 	13
	octal_string:		.space 	13
	
	msg_decimal:		.asciiz "decimal representation: d'"
	msg_new_line:		.asciiz "\n"
	msg_binary:			.asciiz "binary representation:  b'"
	msg_quaternary:		.asciiz "quater representation:  q'"
	msg_octal:			.asciiz "octal  representation:  o'"
	msg_err_convert:	.asciiz "incorrect numeral system. Numeral system must be 2, 4, 8\n"

.globl main
.text

main:
	# zero out string for binary representation
	la  $a0, binary_string
	xor $a1, $a1, $a1
	lw  $a2, bin_str_len
	jal memset
	
	# convert value to binary
	lw  $a0, value
	la  $a1, binary_string
	lw  $a2, bin_str_len
	li  $a3, 2
	jal convert_value
	
	# zero out string for quaternary representation
	la  $a0, queaternary_string
	xor $a1, $a1, $a1
	lw  $a2, quat_str_len
	jal memset
	
	# convert value to quaternary
	lw  $a0, value
	la  $a1, queaternary_string
	lw  $a2, quat_str_len
	li  $a3, 4
	jal convert_value
	
	# zero out string for octal representation
	la  $a0, octal_string
	xor $a1, $a1, $a1
	lw  $a2, oct_str_len
	jal memset
	
	# convert value to octal
	lw  $a0, value
	la  $a1, octal_string
	lw  $a2, oct_str_len
	li  $a3, 8
	jal convert_value

	# print value in decimal representation
	la  $a0, msg_decimal
	lw  $a1, value
	la  $a2, msg_new_line
	jal print_int
	
	# print value in binary representation
	la  $a0, msg_binary
	la  $a1, binary_string
	la  $a2, msg_new_line
	jal print_three_strings
	
	# print value in quaternary representation
	la  $a0, msg_quaternary
	la  $a1, queaternary_string
	la  $a2, msg_new_line
	jal print_three_strings
	
	# print value in octal representation
	la  $a0, msg_octal
	la  $a1, octal_string
	la  $a2, msg_new_line
	jal print_three_strings
		
	.end:
		li $v0, 10
		syscall

# .end main

#convert number to binary numeral system
# $a0 - value to convert
# $a1 - address of result string (ascii)
# $a2 - lenght  of result string
# $a3 - base of numeral_system (must be a power of two)
convert_value:
		li $t2, 2
		bne $a3, $t2, .not_binary
		li $t0, 1
		j .start
	.not_binary:
		li $t2, 4
		bne $a3, $t2, .not_fourth
		li $t0, 2
		j .start
	.not_fourth:
		li $t2, 8
		bne $a3, $t2, .incorrect_numeral_system
		li $t0, 3
		j .start

	.start:
		add  $a1, $a1, $a2
		subi $a1, $a1, 2				# address of current element in result string
		subi $a3, $a3, 1
	
		.convert:
			and $t1, $a0, $a3			# get the least bit(s)
			addi $t1, $t1, 0x30			# to char symbol
		
			sb $t1, ($a1)
			srlv $a0, $a0, $t0
			subi $a2, $a2, 1			# handle all elements of array!
			beqz $a2, .end_convert
				
			sub $a1, $a1, 1
			j .convert
		
	.end_convert:
		jr $ra
		
	.incorrect_numeral_system:
		la $a0, msg_err_convert
		li $v0, 4
		syscall
		
		li $v0, 10
		syscall
# end convert_value



# $a0 - address of array
# $a1 - filler
# $a2 - size in bytes
memset:
	add $a0, $a0, $a2
	sub $a0, $a0, 1					# address of current element in result string
	
	set_value:
		sb $a1, ($a0)
		subi $a2, $a2, 1
		
		beqz $a2, .end_memset 
		subi $a0, $a0, 1
		j set_value
	
	.end_memset:
	jr $ra

# .end memset


# print int and two message with it
# $a0 - address of the first string
# $a1 - value to print
# $a2 - address of the second string
print_int:
	li $v0, 4		# print string
	syscall
	
	move $a0, $a1
	li $v0, 1		# print int
	syscall
	
	move $a0, $a2
	li $v0, 4		# print string
	syscall

	jr $ra
# .end print_int

# print int and two message with it
# $a0 - address of the first string
# $a1 - address of the second string
# $a2 - address of the third string
print_three_strings:
	li $v0, 4		# print string
	syscall
	
	move $a0, $a1
	li $v0, 4		# print string
	syscall
	
	move $a0, $a2
	li $v0, 4		# print string
	syscall

	jr $ra

# .end print

