addi t2, zero, 78
addi t3, zero, -56
addi a7, t2, 2000

add t6, a7, t3
add t2, t2, t3

sub s10, t2, t3
sub t3, t3, a7

# EXPECTED
# sp: 16384
# t2: 22
# t3: -2134
# a7: 2078
# t6: 2022
# s10: 78