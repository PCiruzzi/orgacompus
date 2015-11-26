	li $t0, -1
	blt $t0, $0, fin
	li $t1, 1
fin:
	li $t2, 2
	# al finalizar deberian quedar
	# - t0=-1, t2=2
	# - t1 no deberia ser modificado