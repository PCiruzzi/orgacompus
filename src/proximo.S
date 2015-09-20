#include <mips/regdef.h>
#include <sys/syscall.h>

#Argumentos de la funcion
#define PROXIMO_ARG4		40
#define PROXIMO_ARG3		36
#define PROXIMO_ARG2		32
#define PROXIMO_ARG1		28
#define PROXIMO_ARG0		24

#Stack Size
#define PROXIMO_SS			24

#SRA
#define PROXIMO_FP			20
#define PROXIMO_GP			16

#LTA
#define POSICION			12
#define ACTUAL				8
#define DERECHA				4
#define IZQUIERDA			0

#NO HAY ABA NI RA YA QUE LA FUNCION PROXIMO ES UNA FUNCION HOJA.

.text
.align	2
.globl	proximo
.ent	proximo

#unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N)
proximo:
	#Instrucciones que van siempre
	.frame	$fp, PROXIMO_SS, ra
	.set	noreorder
	.cpload	t9
	.set	reorder
	#Creo el stack frame
	subu	sp,	sp,	PROXIMO_SS
	.cprestore PROXIMO_GP	
	sw		$fp,PROXIMO_FP(sp)
	sw		gp, PROXIMO_GP(sp)
	move	$fp,sp

#Guardo los parametros que me pasaron
#El parametro a4 ya esta en la pos 40 del stack -> 40($fp)
	sb		a3, PROXIMO_ARG3($fp)	#Guardo a regla como byte
	sw		a2, PROXIMO_ARG2($fp)	#J
	sw		a1, PROXIMO_ARG1($fp)	#I
	sw		a0, PROXIMO_ARG0($fp)	#A[0][0]

#Arranca la funcion con el primer if (j==0)
	lw		t0, PROXIMO_ARG2($fp)	#Cargo j en t0
	bne		t0, zero, izqNoBorde	#Si j!=0 no es caso borde

izqBorde:
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	lw		t1, PROXIMO_ARG1($fp)	#Cargo I en t1
	mult	t0, t1					#N*i
	mflo	t2						#Guardo en t2 el resultado
	lw		t0, PROXIMO_ARG0($fp)	#Cargo A[0][0] en t0
	addu	t3, t2, t0				#En t3 = N*i + A[0][0]
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	addu	t3, t3, t0				#En t3 = t3(a[0][0] + N*i) + t0(N)
	addu	t4, t3, -1				#En t4 = t3 - 1
	lbu		t4, 0(t4)				#Cargo en t4 = *(t4)
	sb		t4, IZQUIERDA($fp)		#Guardo t4 (celda izquierda) en pos 0 del stack
	b		derBorde				#Salto al calculo de la celda derecha	

izqNoBorde:
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	lw		t1, PROXIMO_ARG1($fp)	#Cargo I en t1
	mult	t0, t1					#N*i
	mflo	t2						#Guardo en t2 el resultado
	lw		t0, PROXIMO_ARG0($fp)	#Cargo A[0][0] en t0	
	addu	t3, t2, t0				#En t3 = N*i + A[0][0]
	lw		t0, PROXIMO_ARG2($fp)	#Cargo J en t0
	addu	t3, t3, t0				#En t3 = t3(a[0][0] + N*i) + t0(J)
	addu	t4, t3, -1				#En t4 = t3 - 1	
	lbu		t4, 0(t4)				#Cargo en t4 = *(t4)
	sb		t4, IZQUIERDA($fp)		#Guardo t4 (celda izquierda) en pos 0 del stack

derBorde:
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	addu	t0, t0, -1				#t0 = N - 1
	lw		t1, PROXIMO_ARG2($fp)	#Cargo J en t1
	bne		t0, t1, derNoBorde		#Si j!= N-1 no es caso borde

	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	lw		t1, PROXIMO_ARG1($fp)	#Cargo I en t1
	mult	t0, t1					#N*i
	mflo	t2						#Guardo en t2 el resultado
	lw		t0, PROXIMO_ARG0($fp)	#Cargo A[0][0] en t0	
	addu	t3, t2, t0				#En t3 = N*i + A[0][0]
	lbu		t3, 0(t3)				#Cargo en t3 = *(t3)
	sb		t3, DERECHA($fp)		#Guardo t3 (celda derecha) en pos 4 del stack

derNoBorde:
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	lw		t1, PROXIMO_ARG1($fp)	#Cargo I en t1
	mult	t0, t1					#N*i
	mflo	t2						#Guardo en t2 el resultado
	lw		t0, PROXIMO_ARG0($fp)	#Cargo A[0][0] en t0	
	addu	t3, t2, t0				#En t3 = N*i + A[0][0]
	lw		t0, PROXIMO_ARG2($fp)	#Cargo J en t0
	addu	t3, t3, t0				#En t3 = t3(a[0][0] + N*i) + t0(J)
	addu	t4, t3, 1				#En t4 = t3 + 1	
	lbu		t4, 0(t4)				#Cargo en t4 = *(t4)
	sb		t4, DERECHA($fp)		#Guardo t4 (celda derecha) en pos 4 del stack

actual:
	lw		t0, PROXIMO_ARG4($fp)	#Cargo N en t0
	lw		t1, PROXIMO_ARG1($fp)	#Cargo I en t1
	mult	t0, t1					#N*i
	mflo	t2						#Guardo en t2 el resultado
	lw		t0, PROXIMO_ARG0($fp)	#Cargo A[0][0] en t0	
	addu	t3, t2, t0				#En t3 = N*i + A[0][0]
	lw		t0, PROXIMO_ARG2($fp)	#Cargo J en t0
	addu	t3, t3, t0				#En t3 = t3(a[0][0] + N*i) + t0(J)
	lbu		t3, 0(t3)				#Cargo en t3 = *(t3)
	sb		t3, ACTUAL($fp)			#Guardo t3 (celda actual) en pos 8 del stack

posicion:
	lbu		t0, IZQUIERDA($fp)		#Cargo celda izquierda en t0
	lbu		t1, DERECHA($fp)		#Cargo celda derecha en t1
	lbu		t2, ACTUAL($fp)			#Cargo celda actual en t2
	sll		t3, t0, 2				#En t3 = izquierda * 4
	sll		t4, t2, 1				#En t4 = actual * 2
	addu	t5, t3, t4				#En t5 = t3(4izq) + t4(2*act)
	addu	t5, t5, t1				#En t5 = t5 + t1(der)
	sb		t5, POSICION($fp)		#Guardo t5 (pos) en pos 12 del stack

comparacion:
	lbu		t0, PROXIMO_ARG3($fp)	#Cargo Regla en t0
	lbu		t1, POSICION($fp)		#Cargo Pos en t1
	li		t2, 1					#Cargo 1 en t2
	sll		t3, t2, t1				#En t3 = (1<<(pos))
	and		t4, t0, t3				#En t4 = (regla & t3) 
	beq		t4, zero, devuelvo0		#Si t4 = 0, return 0
	li		v0, 1					#Sino return 1
	b		salir					#Salgo de la funcion

devuelvo0:
	move	v0, zero				#Return 0

salir:
#Destruyo el stack frame
	move	sp, $fp
	lw		$fp,PROXIMO_FP(sp)
	lw		gp, PROXIMO_GP(sp)
	addu	sp, sp,PROXIMO_SS
	j		ra

.end	proximo
