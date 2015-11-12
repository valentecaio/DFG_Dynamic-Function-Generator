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
	
	pushl	$0x1234		# empurra o parametro da direita (inteiro, 32 bits)
	pushl	$2		# empurra o parametro da direita (inteiro, 32 bits)
	call	soma
	
	movl	%ebp, %esp
	popl	%ebp
	ret
