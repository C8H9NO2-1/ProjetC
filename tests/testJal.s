addi a2, zero, 87
jal ra, 20
addi a0, a5, 6
add a4, a0, a0
add a2, a4, zero
add ra, a0, s7
addi t5, zero, 54

# Endroit ou on saute avec la deuxième ligne
addi a0, zero, -963

# EXPECTED
# sp: 16384
# ra: 8
# a0: -963
# a2: 87
