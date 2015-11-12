/*
	Esse arquivo é onde a gente vai criar funções em assembly para fazer objdmp e descobrir os codigos
	de maquina de cada comando.
	
	Para fazer objdump:
	gcc -m32 -c funcao-desejada.s
	objdump -d funcao-desejada.o	
*/

.text
.globl	assemblyFoo

assemblyFoo:
	push	%ebp
	movl	%esp, %ebp
	
	pushl	$2000
	pushl	8(%ebp)
	call	soma
	
	movl	%ebp, %esp
	popl	%ebp
	ret
