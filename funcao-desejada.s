/*
	Esse arquivo é onde a gente vai criar funções em assembly para fazer objdmp e descobrir os codigos
	de maquina de cada comando.
*/

.text
.globl	assemblyFoo

assemblyFoo:
	push	%ebp
	movl	%esp, %ebp
	
	pushl	12(%ebp)	# empurra o parametro da direita (float ou inteiro, 32 bits)
	pushl	8(%ebp)		# empurra o parametro da esquerda (float ou inteiro, 32 bits)
	call	pow
	
	movl	%ebp, %esp
	popl	%ebp
	ret
