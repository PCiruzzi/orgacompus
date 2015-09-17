#include <mips/regdef.h>
#include <sys/syscall.h>

#Argumentos de la funcion
#define PROXIMO_ARG4  		XX
#define PROXIMO_ARG3  		XX
#define PROXIMO_ARG2		XX
#define PROXIMO_ARG1  		XX
#define PROXIMO_ARG0		XX

#Stack Size
#define PROXIMO_SS			XX

#SRA
#define PROXIMO_RA  		XX
#define PROXIMO_FP			XX
#define PROXIMO_GP			XX

#LTA
#define constante 			XX

#Referencia de registros
# t0 = 

.text
.align	2
.globl	proximo
.ent	proximo

validate:
	.frame $fp, PROXIMO_SS, ra
	.set	noreorder
	.cpload	t9
	.set	reorder
	#Creo el stack frame
	subu	sp,	sp,	PROXIMO_SS
	.cprestore VALIDATE_GP
	sw		ra,	PROXIMO_RA(sp)	
	sw		$fp,PROXIMO_FP(sp)
	sw		gp, PROXIMO_GP(sp)
	move 	$fp,sp

#seguir aca