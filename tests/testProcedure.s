# On va directement dans la procédure principale du programme
jal zero, 52

#========On définit une fonction========
# Fonction qui renvoie (a0 + a1) - (a2 + a3) dans a0
# On doit enregistrer les valeurs dans t0, t1 et s4
addi sp, sp, -32
sd t0, 16(sp)
sd t1, 8(sp)
sd s4, 0(sp)

add t0, a0, a1
add t1, a2, a3
sub s4, t0, t1
addi a0, s4, 0

ld s4, 0(sp)
ld t1, 8(sp)
ld t0, 16(sp)
addi sp, sp, 32

jal zero, 32
#========Fin de la fonction========

# On saute ici avec la première ligne
# On charge des valeurs dans les registres temporaires
li t0, 534
li t1, -923
li s4, 67

# On charge les arguements de la fonction
li a0, 236
li a1, -329
li a2, 98
li a3, 29

# On appelle la fonction: 
jal ra, -84

# EXPECTED
# sp: 16384
# ra: 88
# t0: 534
# t1: -923
# s4: 67
# a0: -220
# a1: -329
# a2: 98
# a3: 29
