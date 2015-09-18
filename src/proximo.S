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
#define PROXIMO_FP			XX
#define PROXIMO_GP			XX

#LTA
#define constante 			XX

#NO HAY ABA NI RA YA QUE LA FUNCION PROXIMO ES UNA FUNCION HOJA.
#UNA VEZ QUE ESTE TERMINADA LA FUNCION HAY QUE VER EL TAMAÑO DEL STACK DE PROXIMO Y
#REEMPLAZAR LAS "XX" POR LOS VALORES DE LAS CONSTANTES EN EL STACK

#Referencia de registros
# t0 = 

.text
.align	2
.globl	proximo
.ent	proximo

#unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N)
proximo:
	#Instrucciones que van siempre
	.frame 	$fp, PROXIMO_SS, ra
	.set	noreorder
	.cpload	t9
	.set	reorder
	#Creo el stack frame
	subu	sp,	sp,	PROXIMO_SS
	.cprestore PROXIMO_GP	
	sw		$fp,PROXIMO_FP(sp)
	sw		gp, PROXIMO_GP(sp)
	move 	$fp,sp

#Guardo los parametros que me pasaron
#	sw		a4, PROXIMO_ARG4($fp) #No estoy seguro si este esta en a4 o en otro registro.
	sw		a3, PROXIMO_ARG3($fp)
	sw		a2, PROXIMO_ARG2($fp)
	sw		a1, PROXIMO_ARG1($fp)
	sw		a0, PROXIMO_ARG0($fp)

#seguir aca


#Destruyo el stack frame
	move 	sp, $fp
	lw		$fp,PROXIMO_FP(sp)
	lw		gp, PROXIMO_GP(sp)
	addu	sp, sp,PROXIMO_SS
	j		ra

.end	proximo