# Cette condition est fausse
li t0, 23
beq zero, t0, 4
li a0, -34

# Cette condition est vraie
li t1, 23
beq t0, t1, 4
li a1, 135

# Cette condition est vraie
li t2, -2000
bne t2, t0, 12
li a3, 75
addi a3, a3, 5
add a3, a3, a3

# Cette condition est fausse
bne t0, t1, 2044
li a4, 1234

# Cette condition est vraie
blt t2, t1, 8
li a5, 43
addi a5, a5, -56

# Cette condition est fausse
blt t1, t2, -2048
li a6, 2047

# Cette condition est fausse
li t3, 321
bge t1, t3, 128
li a7, -2048

# Cette condition est vraie
bge t3, t1, 4
li s0, 267

# EXPECTED
# sp: 16384
# t0: 23
# t1: 23
# t2: -2000
# t3: 321
# a0: -34
# a4: 1234
# a6: 2047
# a7: -2048
