	li $t0, 1
	blt $t0, $0, fin
	li $t1, 1
	li $t2, 2
fin:
	li $t3, 3
#al finalizar el programa deberian quedar t0=1, t1=1, t2=2, t3=3
