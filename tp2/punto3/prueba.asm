li $t0,20 #direccion en bytes de la sexta instruccion
li $t1,1
jr $t0
li $t2,2
li $t3,3
li $t4,4
addi $t5,$t4,3
# al finalizar deberian quedar
# - t1=1, t4=4, t5=7
# - t2 y t3 no deberian ser modificados
