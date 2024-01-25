li a4, 12
li x7, 564

addi x23, zero, 1054
addi a7, a4, -2047

ld a5, -25(x7)
ld a5, 89(x7)

addi t1, a5, 64

# EXPECTED
# sp: 16384
# a4: 12
# x7: 564
# x23: 1054
# a7: -2035
# a5: 0
# t1: 64
