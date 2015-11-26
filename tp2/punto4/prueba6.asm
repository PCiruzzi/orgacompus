	li $t0, -1
	li $t1, -2
	blt $t0, $t1, fin
	li $t2, 2
fin:
	li $t3, 3
	# al finalizar deberian quedar
	# - t0=-1, t1=-2, t2=2, t3=3