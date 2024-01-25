li a0, 123
li a1, -123

li s2, 1000

sd a0, 80(s2)
sd a1, -48(s2)

add a0, a0, a1
addi a1, a1, 3

ld a2, 80(s2)
ld a3, -48(s2)

# EXPECTED
# sp: 16384
# a0: 0
# a1: -120
# s2: 1000
# a2: 123
# a3: -123