# *********************************
# Aryan Agarwal  
# 19CS30005
# Assignment 1
# **********************************

	.file	"ass1.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Enter how many elements you want:"
.LC1:
	.string	"%d"
.LC2:
	.string	"Enter the %d elements:\n"
.LC3:
	.string	"\nEnter the item to search"
.LC4:
	.string	"\n%d found in position: %d\n"
	.align 8
.LC5:
	.string	"\nItem is not present in the list."
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64 # It stands for "End Branch 64 bit" -- or more precisely, Terminate Indirect Branch in 64 bit.
	pushq	%rbp # Push base pointer (rbp) in stack (rbp is the frame pointer on x86_64)
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp # Set rbp to be equal to rsp (rbp = rsp)
	.cfi_def_cfa_register 6
	subq	$432, %rsp # create space for local array and variables
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rdi # Loads the Effective Address (LEA quad) of LC0 inside of rdi
							 # (We load the memory address and not the value and the destination is a register)
	call	puts@PLT # puts() function is called via Procedure Linkage Table
					 # (PLT is used to call external procedures/functions whose address isn't known in the time of linking, and is left to be resolved by the dynamic linker at run time).
	leaq	-432(%rbp), %rax # loads address (rbp - 432) which is of variable 'n' at 'rax' register
	movq	%rax, %rsi # move value from rax(address of n) to rsi(second argumnet of scanf). 'rsi' is source index register
					   # thus rsi is set to address of 'n', which will be 2nd argument of scanf function 
	leaq	.LC1(%rip), %rdi # Loads the effective address of LC1 inside of rdi. 'rdi' is destination index register.
	movl	$0, %eax # Load the value 0 into the register eax
					 # set the return value to 0 for __isoc99_scanf function (register eax)
	call	__isoc99_scanf@PLT # calling scanf() function and getting 'n'
	movl	-432(%rbp), %eax # Loads the value at memory 432 bytes below base pointer to 'eax' register i.e., eax = Memory[rbp - 432]
							 # value of 'n' is loaded into register eax
	movl	%eax, %esi # Set the value of esi to be eax. esi is the 1st argument of the printf call to be made (esi in this case is set to 'n')
	leaq	.LC2(%rip), %rdi #  loads effective address of .LC2 inside rdi
							 # uses rip relative addressing,
							 # rdi is the first argument of the function (here printf), so rdi = &(*(rip + .LC2))
	movl	$0, %eax # Load the value 0 into the register eax
					 # set the return value to 0 for printf function (register eax)
	call	printf@PLT # calls printf with (rdi,esi) as arguments via Procedure Linkage Table
	                   # (PLT is used to call external procedures/functions whose address isn't known in the time of linking,
					   # and is left to be resolved by the dynamic linker at run time).
	movl	$0, -424(%rbp) # Loads the value 0 at memory 424 bytes below base pointer i.e., Memory[rbp - 424]=0
						   # 'i' of for loop for scanning array elements is initialised with 0
	jmp	.L2 # jump to .L2
.L3:
	leaq	-416(%rbp), %rax # loads address (rbp - 416) which is the base address of array 'a' at 'rax' register
	movl	-424(%rbp), %edx # Loads the value at memory 424 bytes below base pointer to 'edx' register i.e., edx = Memory[rbp - 424]
							 # value of 'i' is loaded into register edx
	movslq	%edx, %rdx  # edx is a 32 bit register, rdx is a 64 bit register.
						# movslq moves and sign-extends a 32-bit value to a 64 bit one, from a 32-bit source to a 64-bit destination.
						# value of 'i' of the for loop is loaded in rdx register
	salq	$2, %rdx    # left-shift destination by 2 bits
						# value stored in rdx register ('i') gets multiplied by 4
	addq	%rdx, %rax  # add value stored in rdx register (4*i) to rax (having base address of array 'a')
						# rax = (a + 4*i)
						# (the address of a[i] is accessed with (a+4*i) because each integer of this array is of 4 bytes)
	movq	%rax, %rsi  # set the value of rsi to be rax.
						# thus rsi is set to address of a[i], which will be 2nd argument of scanf function 
	leaq	.LC1(%rip), %rdi # Loads the effective address of LC1 inside of rdi, which will be first argument of scanf. 'rdi' is destination index register.
	movl	$0, %eax # Load the value 0 into the register eax
					 # set the return value to 0 for __isoc99_scanf function (register eax)
	call	__isoc99_scanf@PLT  # call scanf function with (rdi,rsi) as arguments via Procedure Linkage Table
								# (PLT is used to call external procedures/functions whose address isn't known in the time of linking, and is left to be resolved by the dynamic linker at run time).
	addl	$1, -424(%rbp)  # add 1 to value stored in address (rbp - 424) which is of variable 'i'
							# doing the i++ of the for loop  
.L2:
	movl	-432(%rbp), %eax # Loads the value at memory 432 bytes below base pointer to 'eax' register i.e., eax = Memory[rbp - 432]
							 # value of 'n' is loaded into register eax
	cmpl	%eax, -424(%rbp) # evaluate result = Memory[rbp - 424]-eax
							 # basically, result = 'i' - 'n'
	jl	.L3 # jumps to .L3 if the result is < 0 . (This is executed when SF!=OF)
			# SF = Signed Flag, OF = Overflow Flag
			# basically, (i<n) of the for loop for scanning array elements is checked
	movl	-432(%rbp), %edx # Loads the value at memory 432 bytes below base pointer to 'edx' register i.e., edx = Memory[rbp - 432]
							 # value of 'n' is loaded into register edx
	leaq	-416(%rbp), %rax # loads the effective address of 416 bytes below base pointer to rax register
	movl	%edx, %esi  # set esi to edx i.e., value of 'n'
						# second argument to function 
	movq	%rax, %rdi  # set rdi to rax i.e., base address of array 'a'
						# first argument to function
	call	inst_sort # insertion sort function is called
					  # array 'a' is call by refrence as we are passing its base address
					  # 'n' is call by value as we are passing a copy of its value
	leaq	.LC3(%rip), %rdi #  loads effective address of .LC3 inside rdi
							 #  uses rip relative addressing,
							 #  rdi is the first argument of the function (here printf), so rdi = &(*(rip + .LC3))
	call	puts@PLT # puts() function is called via Procedure Linkage Table
					 # (PLT is used to call external procedures/functions whose address isn't known in the time of linking,
					 # and is left to be resolved by the dynamic linker at run time).
	leaq	-428(%rbp), %rax # loads the effective address of 428 bytes below base pointer (variable 'item') to rax register
	movq	%rax, %rsi # set the value of rsi to be rax.
					   # thus rsi is set to address of 'item', which will be 2nd argument of scanf function 

	leaq	.LC1(%rip), %rdi # Loads the Effective Address (LEA quad) of LC1 inside of rdi, which will be first argument of scanf. ("%d" for scanf)
	movl	$0, %eax # Load the value 0 into the register eax
					 # set the return value to 0 for __isoc99_scanf function (register eax)
	call	__isoc99_scanf@PLT # call scanf function with (rdi,rsi) as arguments via Procedure Linkage Table
							   # (PLT is used to call external procedures/functions whose address isn't known in the time of linking, and is left to be resolved by the dynamic linker at run time).
	movl	-428(%rbp), %edx # set the value of edx register to be value stored at 428 bytes below base pointer (value of 'item')
							 # edx = Memory[rbp - 428]
							 #		or
							 # edx = item
	movl	-432(%rbp), %ecx # Loads the value stored at 432 bytes below base pointer to 'ecx' register i.e., ecx = Memory[rbp - 432]
							 # value of 'n' is loaded into register ecx
	leaq	-416(%rbp), %rax # set rax  = Memory[rbp - 416] i.e., setting rax to be base address of array 'a'
	movl	%ecx, %esi # set esi = ecx
					   # esi = 'n'
	movq	%rax, %rdi # set rdi = rax
					   # rdi = base address of array 'a'
	call	bsearch # call bsearch function
					# rdi = first argument to function = base address of array 'a' (call by refrence)
					# esi = second argument to function = value of 'n' (call by value)
					# edx = third argument to function = value of 'item' (call by value)
	movl	%eax, -420(%rbp) # move the value stored in regsiter eax (returned integer from bsearch) to 420 bytes below base pointer
							 # Memory[rbp - 420] = eax
							 #		or
							 # loc = eax
	movl	-420(%rbp), %eax # move the value stored at 420 bytes below base pointer in regsiter eax
							 # eax = Memory[rbp - 420]
							 #		or
							 # eax = loc
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	movl	-416(%rbp,%rax,4), %edx # set edx to (4*rax + rbp - 416)
									# edx = 4*loc + a
	movl	-428(%rbp), %eax # set the value of eax register to be value stored at 428 bytes below base pointer (value of 'item')
							 # eax = Memory[rbp - 428]
							 #		or
							 # eax = item
	cmpl	%eax, %edx # evaluate result = edx-eax
					   # basically, result = a[loc] - item
	jne	.L4 # jump to .L4 if result!=0 (This is executed when ZF is false)
	movl	-420(%rbp), %eax # move the value stored at 420 bytes below base pointer in regsiter eax
							 # eax = Memory[rbp - 420]
							 #		or
							 # eax = loc
	leal	1(%rax), %edx # move 1 + value stored at rax to edx
						  # edx = loc + 1 
						  # edx will be third argument of printf function
	movl	-428(%rbp), %eax # set the value of eax register to be value stored at 428 bytes below base pointer (value of 'item')
							 # eax = Memory[rbp - 428]
							 #		or
							 # eax = item
	movl	%eax, %esi # set esi = eax
					   # esi = item
					   # esi will be second argument of printf function
	leaq	.LC4(%rip), %rdi # Loads the effective address of LC4 inside of rdi, which will be first argument of printf. 'rdi' is destination index register.
	movl	$0, %eax # Load the value 0 into the register eax
					 # set the return value to 0 for printf function (register eax)
	call	printf@PLT # calls printf with (rdi,esi,edx) as arguments via Procedure Linkage Table
	                   # (PLT is used to call external procedures/functions whose address isn't known in the time of linking,
					   # and is left to be resolved by the dynamic linker at run time).
	jmp	.L5 # jump to .L5
.L4:
	leaq	.LC5(%rip), %rdi # Loads the Effective Address (LEA quad) of LC5 inside of rdi, which will be first argument of printf.
	call	puts@PLT # puts function is called via via Procedure Linkage Table
					 # string in the .LC5 block is printed
						# (PLT is used to call external procedures/functions whose address isn't known in the time of linking,
						# and is left to be resolved by the dynamic linker at run time).
.L5:
	movl	$0, %eax # set return value of main function to 0 
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret # return from main function
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	inst_sort
	.type	inst_sort, @function
inst_sort:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp # push the base pointer (rbp) to stack
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp # Set rbp to be equal to rsp (rbp = rsp)
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp) # set the value at 24 bytes below base pointer to be value stored in rdi register (base adderss of array 'num')
							# Memory[rbp - 24] = num
	movl	%esi, -28(%rbp) # set the value at 28 bytes below base pointer to be value stored in esi register (value of 'n')
							# Memory[rbp - 28] = n 
	movl	$1, -8(%rbp) # set the value at 8 bytes below base pointer to 1
						 # Memory[rbp - 8] = 1
						 # set the variable 'j' of outer for loop to be 1
	jmp	.L9 # jump to .L9
.L13:
	movl	-8(%rbp), %eax # set the value of eax register to be value stored at 8 bytes below base pointer (variable 'j')
						   # eax = Memory[rbp - 8]
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx # moving 4*Memory[rax] (4*j) to rdx register
	movq	-24(%rbp), %rax # set rax  = Memory[rbp - 24] i.e., setting rax to be base address of array num
	addq	%rdx, %rax # add value of rdx register to rax register
						# rax = num + 4*j
	movl	(%rax), %eax # set eax to be equal to value of rax
						 # eax = num[j]
	movl	%eax, -4(%rbp) # set eax to be be value stored at 4 bytes below base pointer (Memory[rbp - 4] = eax).
						   # doing k = num[j]

	movl	-8(%rbp), %eax # set eax to be be value stored at 8 bytes below base pointer i.e., variable 'j' (eax = Memory[rbp - 8]).
	subl	$1, %eax # subtract 1 from value stored in eax. (j-1) gets stored in eax
	movl	%eax, -12(%rbp) # moving value stored in eax register to 12 bytes below base pointer
							# Memory[rbp - 12] = eax
							# doing i = j-1 of the inner for loop
	jmp	.L10 # jump to .L10
.L12:
	movl	-12(%rbp), %eax # set eax to be equal to value stored at 12 bytes below base pointer (variable 'i')
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx # moving 4*Memory[rax] to rdx register
							 # rdx = 4*i
	movq	-24(%rbp), %rax # set rax  = Memory[rbp - 24] i.e., setting rax to be base address of array num
	addq	%rdx, %rax # add value of rdx register to rax register
					   # rax = num + 4*i
	movl	-12(%rbp), %edx # set edx to be equal to value stored at 12 bytes below base pointer (variable 'i')
	movslq	%edx, %rdx # edx is a 32 bit register, rdx is a 64 bit register.
					   # movslq moves and sign-extends a 32-bit value to a 64 bit one, from a 32-bit source to a 64-bit destination.
					   # value of 'i' of the inner for loop is loaded in rdx register
	addq	$1, %rdx # add 1 to value stored in rdx register
					 # rdx = i + 1
	leaq	0(,%rdx,4), %rcx # moving 4*Memory[rdx] to rcx register
							 # rcx = 4*(i+1)
	movq	-24(%rbp), %rdx # set rdx  = Memory[rbp - 24] i.e., setting rdx to be base address of array num
	addq	%rcx, %rdx # add value of rcx register to rdx register
					   # rdx = num + 4*(i+1)
	movl	(%rax), %eax # set eax to be value stored in rax
						 # eax = num[i]
	movl	%eax, (%rdx) # set rdx to be value stored in eax
						 # num[i+1] = num[i]
	subl	$1, -12(%rbp) # subtract 1 from value stored at 12 bytes below base pointer (variable 'i')
						  # Memory[rbp - 12] = Memory[rbp - 12] - 1
						  # 	or
						  # doing i-- of inner for loop
.L10:
	cmpl	$0, -12(%rbp) # evaluate result = Memory[rbp - 12]-0
						  # basically, result = 'i' - 0
	js	.L11 # jump to .L11 if result < 0 (This is executed when SF is true)
			 # we are breaking from the inner for loop if 'i' is negative
	movl	-12(%rbp), %eax # moving value stored at 12 bytes below base pointer (variable 'i') to eax register
							# eax = Memory[rbp - 12]
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx # moving 4*Memory[rax] to rdx register
							 # rdx = 4*i
	movq	-24(%rbp), %rax # set rax  = Memory[rbp - 24] i.e., setting rax to be base address of array num
	addq	%rdx, %rax # add value of rdx register to rax register
					   # rax = num + 4*i
	movl	(%rax), %eax # set eax to be equal to value of rax
						 # eax = num[i]
	cmpl	%eax, -4(%rbp) # evaluate result = Memory[rbp - 4]-eax
						   # basically, result = 'k' - num[i]
	jl	.L12 # jumps to .L12 if the result is < 0 . (This is executed when SF!=OF)
			 # SF = Signed Flag, OF = Overflow Flag
			 # basically, (k<num[i]) of the inner for loop is checked
.L11:
	movl	-12(%rbp), %eax # moving value stored at 12 bytes below base pointer (variable 'i') to eax register
							# eax = Memory[rbp - 12]
							# 	or
							# eax = i
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	addq	$1, %rax # add 1 to value stored in rax register
					 # rax = i + 1
	leaq	0(,%rax,4), %rdx # moving 4*Memory[rax] to rdx register
							 # rdx = 4*(i+1)
	movq	-24(%rbp), %rax # set rax  = Memory[rbp - 24] i.e., setting rax to be base address of array num
	addq	%rax, %rdx # add value of rax register to rdx register
					   # rdx = num + 4*(i+1)
	movl	-4(%rbp), %eax # set eax to be equal to value stored at 4 bytes below base pointer (variable 'k')
						   # eax = Memory[rbp - 4]
						   #	or
						   # eax = k
	movl	%eax, (%rdx) # set rdx to be equal to value of eax
						 # num[i+1] = k 
	addl	$1, -8(%rbp) # add 1 to value stored at 8 bytes below base pointer (variable 'j')
						 # Memory[rbp - 8] = Memory[rbp - 8] +1
						 # doing j++ of outer for loop
.L9:
	movl	-8(%rbp), %eax # set the value of eax register to be value stored at 8 bytes below base pointer (variable 'j')
						   # eax = Memory[rbp - 8]
	cmpl	-28(%rbp), %eax  # evaluate result = eax - Memory[rbp - 28]
							 # basically, result = 'j' - 'n'
	jl	.L13 # jumps to .L13 if the result is < 0 . (This is executed when SF!=OF)
			 # SF = Signed Flag, OF = Overflow Flag
			 # basically, (j<n) of the outer for loop for inst_sort is checked
	nop
	nop
	popq	%rbp # pops rbp (base pointer) from stack
	.cfi_def_cfa 7, 8
	ret # returns from the inst_sort function
	.cfi_endproc
.LFE1:
	.size	inst_sort, .-inst_sort
	.globl	bsearch
	.type	bsearch, @function
bsearch:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp # push the base pointer (rbp) to stack
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp # Set rbp to be equal to rsp (rbp = rsp)
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp) # Move the value stored at rdi register at 24 bytes below base pointer
							# Memory[rbp - 24] = rdi
							# Memory[rbp - 24] = base address of array 'a'
	movl	%esi, -28(%rbp) # Move the value stored at esi register at 28 bytes below base pointer
							# Memory[rbp - 28] = esi
							# Memory[rbp - 28] = n
	movl	%edx, -32(%rbp) # Move the value stored at edx register at 32 bytes below base pointer
							# Memory[rbp - 32] = edx
							# Memory[rbp - 32] = item
	movl	$1, -8(%rbp) # set the value stored at 8 bytes below base pointer to 1
						 # Memory[rbp - 8] = 1
						 # bottom = 1
	movl	-28(%rbp), %eax # Move the value stored at 28 bytes below base pointer to eax register
							# eax = Memory[rbp - 28]
							# eax = n
	movl	%eax, -12(%rbp) # set the value stored at 12 bytes below base pointer to eax register
							# Memory[rbp - 12] = eax
							# Memory[rbp - 12] = n
							# top = n
.L18:
	movl	-8(%rbp), %edx  # Move the value stored at 8 bytes below base pointer to edx register
							# edx = Memory[rbp - 8]
							# edx = bottom
	movl	-12(%rbp), %eax # Move the value stored at 12 bytes below base pointer to eax register
							# eax = Memory[rbp - 12]
							# eax = top
	addl	%edx, %eax # add value stored in edx register to eax register
					   # eax = eax + edx
					   # eax = top + bottom
	movl	%eax, %edx # move value stored in eax register to edx register
					   # edx = eax
					   # edx = top + bottom

	shrl	$31, %edx # logical right shift the value stored at edx register by 31 bits
					  # edx = (top+bottom)>>31
					  # edx = 1 if (top+bottom) is negative else 0
	addl	%edx, %eax # add value of edx regsiter to eax register
					   # eax = eax + edx
					   # eax = (top+bottom) + (top+bottom)>>31
	sarl	%eax # arithmetic right shift of value stored in eax register by 1 bit
				 # eax = eax>>1
				 # eax = ((top+bottom) + (top+bottom)>>31)/2
				 # we are adding (top+bottom)>>31 because (top+bottom) can be negative
	movl	%eax, -4(%rbp) # Move the value stored at eax register to 4 bytes below base pointer
						   # Memory[rbp - 4] = eax
						   # Memory[rbp - 4] = (top+bottom)/2
						   # mid = (top+bottom)/2
	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx c
							 # rdx = 4*mid
	movq	-24(%rbp), %rax # Move the value stored at 24 bytes below base pointer to rax register
							# rax = Memory[rbp - 24]
							# rax = base address of array 'a'
	addq	%rdx, %rax # add value of rdx regsiter to rax register
					   # rax = rax + rdx
					   # rax = a + 4*mid
	movl	(%rax), %eax # reads a 32-bit value from that memory address(rax), and stores it in the eax register. ( eax <-- a[mid] )
	cmpl	%eax, -32(%rbp) # evaluate result = Memory[rbp - 32]-eax
						    # basically, result = item - a[mid]
	jge	.L15 # jump to .L15 if result >=0
			 # (This is executed when SF==OF)
			 # SF = Signed Flag, OF = Overflow Flag
	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
	subl	$1, %eax # subtract 1 to value stored at eax register
					 # eax = eax - 1
					 # eax = mid - 1
	movl	%eax, -12(%rbp) # Move the value stored at eax register to 12 bytes below base pointer
						    # Memory[rbp - 12] = eax
						    # top = mid - 1
	jmp	.L16 # jump to .L16
.L15:
	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx # set rdx to (4*rax)
							 # rdx = 4*mid
	movq	-24(%rbp), %rax # Move the value stored at 24 bytes below base pointer to rax register
							# rax = Memory[rbp - 24]
							# rax = base address of array 'a'
	addq	%rdx, %rax # add value of rdx regsiter to rax register
					   # rax = rax + rdx
					   # rax = a + 4*mid
	movl	(%rax), %eax # reads a 32-bit value from that memory address(rax), and stores it in the eax register. ( eax <-- a[mid] )
	cmpl	%eax, -32(%rbp) # evaluate result = Memory[rbp - 32]-eax
						    # basically, result = item - a[mid]
	jle	.L16 # jump to .L15 if result <=0
			 # (This is executed when SF!=OF or ZF is true)
			 # SF = Signed Flag, OF = Overflow Flag, ZF = Zero Flag
			 # basically the else-if (item>a[mid]) getf false

	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
	addl	$1, %eax # add 1 to value stored at eax register
					 # eax = eax + 1
					 # eax = mid + 1
	movl	%eax, -8(%rbp) # Move the value stored at eax register to 8 bytes below base pointer
						   # Memory[rbp - 8] = eax
						   # bottom = mid + 1
.L16:
	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
	cltq # Convert doubleword in ​ %eax​ to quadword in ​ %rax​ ​ (sign-extended)
	leaq	0(,%rax,4), %rdx # set rdx to (4*rax)
							 # rdx = 4*mid
	movq	-24(%rbp), %rax # Move the value stored at 24 bytes below base pointer to rax register
							# rax = Memory[rbp - 24]
							# rax = base address of array 'a'
	addq	%rdx, %rax # add value of rdx regsiter to rax register
					   # rax = rax + rdx
					   # rax = a + 4*mid
	movl	(%rax), %eax # reads a 32-bit value from that memory address(rax), and stores it in the eax register. ( eax <-- a[mid] )
	cmpl	%eax, -32(%rbp) # evaluate result = Memory[rbp - 32]-eax
						    # basically, result = item - a[mid]
	je	.L17 # jump to .L17 if result ==0
			 # (This is executed when ZF is true)
			 # ZF = Zero Flag
	movl	-8(%rbp), %eax # Move the value stored at 8 bytes below base pointer to eax register
						   # eax = Memory[rbp - 8]
						   # eax = bottom
	cmpl	-12(%rbp), %eax # evaluate result = eax - Memory[rbp - 12]
						    # basically, result = bottom - top
	jle	.L18 # jump to .L18 if result <=0
			 # (This is executed when SF!=OF or ZF is true)
			 # SF = Signed Flag, OF = Overflow Flag, ZF = Zero Flag
			 # basically we are re-entering in the do-while loop
.L17:
	movl	-4(%rbp), %eax # Move the value stored at 4 bytes below base pointer to eax register
						   # eax = Memory[rbp - 4]
						   # eax = mid
						   # eax will be the return value of bsearch function
	popq	%rbp # pop base pointer from stack
	.cfi_def_cfa 7, 8
	ret # return from bsearch function
	.cfi_endproc
.LFE2:
	.size	bsearch, .-bsearch
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0" 
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
