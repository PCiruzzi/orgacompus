	li $t1,1
	j hola
	li $t2,2
	li $t5,5
	li $t6,6
hola:
	li $t3,3
	li $t4,4
	#al finalizar deberian quedar
	# - t1=1, t3=3, t4=4
	# - t2, t5 y t6 no deberian ser modificados