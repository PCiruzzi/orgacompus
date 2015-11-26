	li $t1, 1
	beq $0, $0, fin2
	li $t5, 5
	j fin
	li $t2, 2
fin:
	li $t3, 3
fin2:
	li $t4, 4
	# al finalizar deberian quedar
	# - t1=1, t4=4
	# - t2, t3 y t5 no deberian ser modificados
