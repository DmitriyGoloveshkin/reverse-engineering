# Simple programm to demonstrate using arithmetic 
# operatioins, arrays and float-point register
#  
# find min/max value in array
# find average value in array (int)
# fine number of elements with even value
.data
	array:			.word 1, 20, 3, 4, 5, 6, 7, 8, 9, 10
	array_length:	.word 10
	float_value:    .float 5.8
	
	msg_array:			.asciiz "arrays' elements: "
	msg_max_value:		.asciiz "max_value: "
	msg_min_value:		.asciiz "min_value: "
	msg_cnt_even:		.asciiz "cnt_even: "
	msg_ave_sum_int:	.asciiz "ave_sum_int: "
	msg_ave_sum_float:	.asciiz "ave_sum_float: "
	msg_new_line:		.asciiz "\n"
	
.globl main 
.text

main:
	# $t0 - array_address
	# $t1 - array_length
	# $t2 - max_value
	# $t3 - min_value
	# $t4 - cnt_even
	# $t5 - ave_sum_int
	# $t6 - sum
	# $t7 - current element
	#
	# $f12 - ave_sum_float 

	la $t0, array
	lw $t1, array_length

	lw $t2, ($t0)	# max_value
	lw $t3, ($t0)	# min_value

	xor $t4, $t4, $t4	# cnt_even
	xor $t5, $t5, $t5	# ave_sum
	xor $t6, $t6, $t6	# sum
	
	
	.next_element:
		lw $t7, ($t0) 				# current element
		add $t6, $t6, $t7
		
		ble $t7, $t2, .no_max
		move $t2, $t7				# set max value

		.no_max:
			bge $t7, $t3, .no_min
			move $t3, $t7			# set min value
		
		.no_min:
			andi $t8, $t7, 0x01
			bnez $t8, .no_even
			addi $t4, $t4, 1		# cnt_even++
			
		.no_even:
			subi $t1, $t1, 1
			beqz $t1, .end_elements
			addi $t0, $t0, 4		# to next element
			j .next_element
			
		.end_elements:
			lw $t2, array_length
			div $t5, $t6, $t2		# ave_sum_int
			
			# float average sum
			mtc1 $t6, $f16
			cvt.s.w $f12, $f16	
		
			mtc1 $t2, $f16
			cvt.s.w $f14, $f16	
			
			div.s $f16, $f12, $f14	
			mov.s $f12, $f16		# $fl2 = (float) average sum

		# print cnt_even
		la $a0, msg_cnt_even
		move $a1, $t4
		la $a2, msg_new_line
		jal print
		
		# print max_value
		la $a0, msg_max_value
		move $a1, $t2
		la $a2, msg_new_line
		jal print
					
		# print min_value
		la $a0, msg_min_value
		move $a1, $t3
		la $a2, msg_new_line
		jal print	
		
		# print ave_sum_int
		la $a0, msg_ave_sum_int
		move $a1, $t5
		la $a2, msg_new_line
		jal print
		
		# print ave_sum_float
		la $a0, msg_ave_sum_float
		la $a2, msg_new_line
		jal print_float
		
		
		.end:	
			li $v0, 10
			syscall
# .end main


# print int and two message with it
# $a0 - address of the first string
# $a1 - value to print
# $a2 - address of the second string
print:
	li $v0, 4		# print string
	syscall
	
	move $a0, $a1
	li $v0, 1		# print int
	syscall
	
	move $a0, $a2
	li $v0, 4		# print string
	syscall

	jr $ra

# .end print

# print float and two message with it
# $a0 - address of the first string
# $f12 - value to print
# $a2 - address of the second string
print_float:
	li $v0, 4		# print string
	syscall
	
	li $v0, 2		# print float
	syscall
	
	move $a0, $a2
	li $v0, 4		# print string
	syscall

	jr $ra

# .end print















