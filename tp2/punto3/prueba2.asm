	li $t8, 8 #direccion en bytes de la 
			  #instruccion de inicio (beq...)
	li $t0, 1
inicio:
	beq $t0, $0, fin
	li $t1, 1
	li $t2, 2
	li $t3, 3
	subi $t0, $t0, 1
	jr $t8
	li $t4, 4
	li $t5, 5
fin:
	li $t6, 6
	# al finalizar deberian quedar
	# - t0=0, t1=1, t2=2, t3=3, t6=6
	# - t4 y t5 no deberian ser modificados
