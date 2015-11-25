li $t1,3
li $t2,4
sll $t3,$t1,$t2
li $t2,5
srl $t3,$t3,$t2
# 3 << 4 = 48, luego 48 >> 5 = 1