.test
addi	$k0,	$zero,	0x10010000
addi	$k1,	$zero,	0x10010100
j F3

F1: 	
addi 	$s0,	$zero,	0
sw 	$s0,	12($k1)
movz 	$s1,	$a1,	$zero
add 	$s1,	$s1,	$a0
bgt 	$a2,	$s1,	Flag4
j 	Flag1
Flag1: 	
addi 	$s0,	$zero,	3
bnez 	$s0,	Flag2
j 	Flag3
Flag2: 	
beq 	$a2,	$a0,	Flag4
j 	Flag3
Flag3: 	
addi 	$s0,	$zero,	6
bnez 	$s0,	Flag4
j 	Flag5
Flag4: 	
movz 	$s0,	$a1,	$zero
mul 	$s0,	$s0,	$a0
mul 	$s0,	$s0,	$a0
addi 	$s1,	$zero,	1
add 	$s0,	$s0,	$s1
movz 	$s1,	$a2,	$zero
add 	$s1,	$s1,	$s0
sw 	$s1,	16($k1)
j 	Flag6
Flag5: 	
movz 	$s0,	$a2,	$zero
sw 	$s0,	16($k1)
Flag6: 	
lw 	$s0,	12($k1)
ble 	$s0,	100,	Flag7
j 	Flag8
Flag7: 	
lw 	$s0,	16($k1)
addi 	$s1,	$zero,	2
mul 	$s0,	$s0,	$s1
sw 	$s0,	12($k1)
j 	Flag6
Flag8: 	
lw 	$v0,	12($k1)
sub	$k1,	$k1,	0x00000100
jr 	$ra

F2: 	
movz 	$s0,	$a0,	$zero
addi 	$s1,	$zero,	2
add 	$s0,	$s0,	$s1
mul 	$s0,	$s0,	$s1
movz 	$v0,	$s0,	$zero
sub	$k1,	$k1,	0x00000100
jr 	$ra

F3: 	
addi 	$t0,	$zero,	3
sw 	$t0,	0($k1)
movz 	$t1,	$t0,	$zero
addi 	$t2,	$zero,	1
add 	$t1,	$t1,	$t2
sw 	$t1,	4($k1)
movz 	$t2,	$t0,	$zero
add 	$t2,	$t2,	$t1
sw 	$t2,	8($k1)
movz 	$a0,	$t2,	$zero
add	$k1,	$k1,	0x00000100
jal 	F2,	
movz 	$t3,	$v0,	$zero
movz 	$a0,	$t3,	$zero
movz 	$a1,	$t1,	$zero
movz 	$a2,	$t0,	$zero
add	$k1,	$k1,	0x00000100
jal 	F1,	
movz 	$t4,	$v0,	$zero
sw 	$t4,	12($k1)
sw 	$t4,	16($k1)
movz 	$v0,	$t4,	$zero
j end

end:
