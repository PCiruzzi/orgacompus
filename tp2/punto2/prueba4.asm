	li $t1, 1
	beq $0, $0, fin
	j fin2
	li $t2, 2
fin:
	li $t3, 3
fin2:
	li $t4, 4
	# al finalizar deberian quedar
	# - t1=1, t3=3, t4=4
	# - t2 no deberia ser modificado
