  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  
  delay:
  	jr $ra
  	nop
  	
  time2string:
    	# save registers, push stack
    	PUSH($ra)
    	PUSH($t0)
    	PUSH($t1)
    	PUSH($t2)
    	PUSH($t3)
    	PUSH($t4)
    
    	# create "write pointer" by copying a0 address
    	move $t5, $a0
    
    	# extract minutes and seconds
    	move $t0, $a1         # copy time into $t0
    	andi $t1, $t0, 0xF000 # extract first min digit
    	srl $t1, $t1, 12      # shift right to get the digit -> 0x000F
    	andi $t2, $t0, 0x0F00 # extract second min digit
    	srl $t2, $t2, 8      
    	andi $t3, $t0, 0x00F0 # extract first sec digit
    	srl $t3, $t3, 4     
    	andi $t4, $t0, 0x000F # extract second sec digit.
    
    	# convert and store first min digit
    	move $a0, $t1
    	jal hexasc
    	nop
    	sb $v0, 0($t5)       # store byte
    	addi $t5, $t5, 1     # increment pointer
    
    	# convert and store second min digit
    	move $a0, $t2
    	jal hexasc
    	nop
    	sb $v0, 0($t5)       # store byte
    	addi $t5, $t5, 1
    
    	# store colon ":"
    	li $t1, 0x3A         # 0x3A is hex for ":", reusing t1
    	sb $t1, 0($t5)       # store byte
    	addi $t5, $t5, 1
    
    	# convert and store first sec digit
    	move $a0, $t3
    	jal hexasc
    	nop
    	sb $v0, 0($t5)       # store byte
    	addi $t5, $t5, 1
    
    	# convert and store second sec digit
    	move $a0, $t4
    	jal hexasc
    	nop
    	sb $v0, 0($t5)       # store byte
    	addi $t5, $t5, 1
    
    	# store null byte to mark end of string
    	sb $0, 0($t5)
    
    	# restore stack
    	POP($t4)
    	POP($t3)
    	POP($t2)
    	POP($t1)
    	POP($t0)
    	POP($ra)

    	jr $ra
    	nop
    	
hexasc:
    andi $v0, $a0, 0x0000000f  # isolate the least significant 4 bits
    sltiu $t0, $v0, 10         # if the value is less than 10, set $t0 to 1, else 0
    beq $t0, $zero, overn      # if $t0 is 0 (value is 10 or more), go to overn
    addiu $v0, $v0, 0x30       # add 0x30 to the value (to convert 0-9 to '0'-'9')
    j done                      # jump to done
    nop
overn:
    addiu $v0, $v0, 0x07       # add 0x07 to the value (to convert 10-15 to 'A'-'F')
    addiu $v0, $v0, 0x30       # add 0x30 to the value (to convert 0-9 to '0'-'9')
    nop
done:
    jr $ra                     # return
    nop
  	
  
  
  
  #
