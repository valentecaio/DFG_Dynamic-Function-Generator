/*
	Esse arquivo é onde a gente vai criar funções em assembly para fazer objdmp e descobrir os codigos
	de maquina de cada comando.
*/

.text
.globl	assemblyFoo

assemblyFoo:
	push	%ebp
	movl	%esp,	%ebp
	
	
	
	movl	%ebp,	%esp
	popl	%ebp
	ret
	
	
	