# On recherche le maximum et le minimum dans un tableau

# On stocke le minimum dans a0 et son indice dans a1
addi a0, zero, 0
addi a1, zero, 0

# On stocke le maximum dans a2 et son indice dans a3
addi a2, zero, 0
addi a3, zero, 0

# On stocke l'adresse de base du tableau dans a4
# On va utiliser a5 pour parcourir le tableau
# On stocke la taille dans a6
addi a4, zero, 1000
addi a5, a4, 0
addi a6, zero, 6

# On créé un tableau d'éléments
li t0, 876
sd t0, 0(a5)
addi a5, a5, 8

li t0, 76
sd t0, 0(a5)
addi a5, a5, 8

li t0, -789
sd t0, 0(a5)
addi a5, a5, 8

li t0, 738
sd t0, 0(a5)
addi a5, a5, 8

li t0, -465
sd t0, 0(a5)
addi a5, a5, 8

li t0, 0
sd t0, 0(a5)

# On prend la première valeur du tableau comme minimum et comme maximum
addi a5, a4, 0
ld a0, 0(a5)
ld a2, 0(a5)
addi a5, a5, 8

# On fait une boucle pour parcourir le reste du tableau
addi t1, zero, 1
beq t1, a6, 44
# On récupère la valeur de la case courante du tableau dans t2
ld t2, 0(a5)
# Si la valeur est plus petite que le minimum, on change le minimum et sinon on change le maximum
bge t2, a0, 12
add a0, t2, zero
add a1, t1, zero
j 12

blt t2, a2, 8
add a2, t2, zero
add a3, t1, zero

addi t1, t1, 1
addi a5, a5, 8

j -48

#EXPECTED
# sp: 16384
# a4: 1000
# a5: 1048
# a6: 6
# t1: 6
# a0: -789
# a1: 2
# a2: 876
# a3: 0