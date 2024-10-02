	.file	"To_Upper.s"
	.text
	.globl	To_Upper
	.type	To_Upper, @function

/* **********************
    Name:
    Wisc ID Number:
    Wisc Email:
************************ */


To_Upper:

# C version
/* **********************
    Write the equivalent C code to this function here (in the comment block)

************************ */


# Memory Layout
/* ************************ 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -4(%rbp)  |  int x
        -8(%rbp)  |  int y
        -16(%rbp  |  int *px
************************ */


# Prologue


# This code prints the letter 'a' (ascii value 97)
# Use this for debugging
# Comment out when finished - your function should not print anything
# Note putchar overwrites all caller saved registers including argument registers
	movl	$97, %eax
	movl	%eax, %edi
	call	putchar@PLT


# Body of function


# Epilogue
    ret
