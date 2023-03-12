.data
	a:			.word		12356
	b:			.word 		32
	
	new_line :	.asciiz 	"\n"
	msg_sum:	.asciiz		"sum  a+b: "
	msg_sumu:	.asciiz		"sumu a+b: "
	msg_subu:	.asciiz		"subu a-b: "
	msg_mulo:	.asciiz		"mulo a*b: "
	msg_mul:	.asciiz		"mul a*b: "
	msg_divu:	.asciiz		"divu a/b: "
	msg_remu:	.asciiz		"remu a%b: "
	msg_a:		.asciiz 	"a: "
	msg_b: 		.asciiz 	"b: "

.globl main 
.text

main:
	lw $t0, a
	lw $t1, b
	
	# print variable 'a' and two help messages
	la $a0, msg_a
	move $a1, $t0
	la $a2, new_line
	jal print
	
	# print variable 'b' and two help messages
	la $a0, msg_b
	move $a1, $t1
	la $a2, new_line
	jal print
	
	# (unsigned)a+b
	addu $t2, $t0, $t1
	# print sum and two correspong messages
	la $a0, msg_sumu
	move $a1, $t2
	la $a2, new_line
	jal print
	
	# (signed)a+b
	add $t2, $t0, $t1
	# print sum and two correspong messages
	la $a0, msg_sum
	move $a1, $t2
	la $a2, new_line
	jal print
	
	# a-b
	subu $t2, $t0, $t1
	# print sum and two correspong messages
	la $a0, msg_subu
	move $a1, $t2
	la $a2, new_line
	jal print
	
	# (without OF)a*b
	mul $t2, $t0, $t1
		# two parts
		la $a0, msg_mul
		li $v0, 4
		syscall
		
		mfhi $a2
		mflo $a3
		
		move $a0, $a2
		li $v0, 1
		syscall
		
		move $a0, $a3
		li $v0, 1
		syscall
		
		la $a0, new_line
		li $v0, 4
		syscall
		
	# print sum and two correspong messages
#	la $a0, msg_mul
#	move $a1, $t2
#	la $a2, new_line
#	jal print

	
	# a/b
	divu $t2, $t0, $t1
	# print sum and two correspong messages
	la $a0, msg_divu
	move $a1, $t2
	la $a2, new_line
	jal print
	
	# a%b
	remu $t2, $t0, $t1
	# print sum and two correspong messages
	la $a0, msg_remu
	move $a1, $t2
	la $a2, new_line
	jal print

	.end:	
	li $v0, 10
	syscall
	
#.end main

# print string function
# $a0 - string address
print_string:
	li $v0, 4
	syscall

	jr $ra
#.end print_string

# print int function
# $a0 - int value	
print_int:
	li $v0, 1
	syscall

	jr $ra
#.end print_int

# print int and two message with it
# $a0 - address of the first string
# $a1 - value to print
# $a2 - address of the second string
print:
	li $v0, 4
	syscall
	
	move $a0, $a1
	li $v0, 1
	syscall
	
	move $a0, $a2
	li $v0, 4
	syscall

	jr $ra

# .end print
