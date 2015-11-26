	li $t6, 6
	subi $t5, $t6, 1
	blt $t5, $t6, fin
	li $t1, 1
	li $t2, 2
fin:
	li $t3, 3
	# al finalizar deberian quedar
	# - t5=5, t6=6, t3=3
	# - t1 y t2 no deberian ser modificados
