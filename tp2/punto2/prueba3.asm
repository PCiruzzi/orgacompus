	li $t1, 1
	beq $0, $0, fin
	li $t5, 5
	j fin2
	li $t2, 2
fin:
	li $t3, 3
fin2:
	li $t4, 4
	# al finalizar deberian quedar
	# - t1=1, t3=3, t4=4
	# - t2 y t5 no deberian ser modificados
