li s4, -273
li t2, 49
li x3, -282
li a5, 643
li s0, -186
li x15, 834
li s7, 948
li t4, -1063
li x10, -33
li x30, -1720
li a3, 677
li ra, -1982
li x17, 1952

beq s4, t2, -296
beq x3, a5, 3628

bne s0, x15, 2038
bne s7, t4, 464

blt x10, x30, -48
blt a3, ra, -1142

bge s4, x17, -3408
bge zero, zero, 52


# EXPECTED
# sp: 16384
# s4: -273
# t2: 49
# x3: -282
# a5: 643
# s0: -186
# x15: 834
# s7: 948
# t4: -1063
# x10: -33
# x30: -1720
# a3: 677
# ra: -1982
# x17: 1952