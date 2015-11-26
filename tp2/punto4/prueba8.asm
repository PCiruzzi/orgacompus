	li $t0, -1
	li $t1, 1
	blt $t0, $t1, fin
	li $t2, 2
fin:
	li $t3, 3
	# al finalizar deberian quedar
	# - t0=-1, t1=1, t3=3
	# - t2 no deberia ser modificado