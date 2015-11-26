	li $t0, -1
	blt $t0, $t0, fin
	li $t2, 2
fin:
	li $t3, 3
	# al finalizar deberian quedar
	# - t0=-1, t2=2, t3=3