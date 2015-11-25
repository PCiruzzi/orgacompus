li $t1,32767
li $t2,17
sll $t3,$t1,$t2
li $t2,17
srl $t3,$t3,$t2
# 16385 << 17 = -131072 (Recordar complemento a la base),
# luego -131072 >> 17 = 16385 (No hace extension de signo)
