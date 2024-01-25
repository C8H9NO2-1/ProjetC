li t0, 756
li x20, -57
li s3, 24
li s7, 789

add s5, t0, x20
sub x8, s3, s7

# EXPECTED
# sp: 16384
# t0: 756
# x20: -57
# s3: 24
# s7: 789
# s5: 699
# x8: -765
