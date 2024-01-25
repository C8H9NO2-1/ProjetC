# Ce fichier nous permet de tester différentes instructions liées à la gestion de la mémoire

li a0, 2047
li a1, -2048

li s2, 1000
li s3, 2043
li s4, 2045

addi t0, zero, 1
addi t1, zero, 4

# Boucle qui permet de decaler les bits de s4, qui atteint donc la valeur 16360
beq t0, t1, 12
add s4, s4, s4
addi t0, t0, 1
# Permet de revenir au début de la boucle
beq zero, zero, -16

sd a0, 0(s2)
sd a1, 0(s3)
sd a0, 0(s4)

# On modifie les variables pour vérifier qu'il n'y aucune corrélation avec la mémoire
add a0, a0, a1
addi a1, a1, 3

ld a2, 0(s2)
ld a3, 0(s3)
ld a4, 0(s4)

# EXPECTED
# sp: 16384
# a0: -1
# a1: -2045
# s2: 1000
# s3: 2043
# s4: 16360
# a2: 2047
# a3: -2048
# a4: 2047
# t0: 4
# t1: 4

