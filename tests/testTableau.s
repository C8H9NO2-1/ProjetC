# On ajoute 1 à chaque valeur d'un tableau dont on connait la taille

# a0 = adresse de base du tableau / a1 = taille du tableau
li a0, 1000
li a1, 10

# t0 est utilise pour parcourir le tableau / t1 = adresse courante lors du parcours du tableau / t2 = valeur de la premiere case du tableau
li t0, 0
addi t1, a0, 0
li t2, 37

# On écrit des valeurs dans toutes les cases du tableau
beq t0, a1, 20
sd t2, 0(t1)
add t2, t2, t2
addi t0, t0, 1
addi t1, t1, 8
j -24

# On ajoute 1 à chaque case du tableau
li t3, 0
addi t4, a0, 0

beq t3, a1, 24
ld t5, 0(t4)
addi t5, t5, 1
sd t5, 0(t4)
addi t3, t3, 1
addi t4, t4, 8
j -28

# On stocke les valeurs du tableau dans s0, ..., s9 pour pouvoir observer leurs valeurs
ld s0, 0(a0)
ld s1, 8(a0)
ld s2, 16(a0)
ld s3, 24(a0)
ld s4, 32(a0)
ld s5, 40(a0)
ld s6, 48(a0)
ld s7, 56(a0)
ld s8, 64(a0)
ld s9, 72(a0)

# EXPECTED
# sp: 16384
# a0: 1000
# a1: 10
# t0: 10
# t1: 1080
# t2: 37888
# s0: 38
# s1: 75
# s2: 149
# s3: 297
# s4: 593
# s5: 1185
# s6: 2369
# s7: 4737
# s8: 9473
# s9: 18945
# t3: 10
# t4: 1080
# t5: 18945
