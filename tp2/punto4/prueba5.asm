	li $t0, -1
	li $t1, -2
	blt $t1, $t0, fin
	li $t2, 2
fin:
	li $t3, 3
	# al finalizar deberian quedar
	# - t0=-1, t1=-2, t3=3
	# - t2 no deberia ser modificado