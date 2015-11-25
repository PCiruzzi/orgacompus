	li $t1,1
	j hola
	li $t2,2
hola:
	li $t3,3
	li $t4,4
	#al finalizar el programa deberian quedar t1=1, t3=3, t4=4 y t2 no deberia ser modificado
