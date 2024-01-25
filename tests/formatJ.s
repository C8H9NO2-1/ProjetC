li t5, 1870
li x5, 992
li x18, 0
li tp, 3

jal t5, 764
jal x5, -40704
jal x18, 397118
jal tp, -784

#! Ce programme n'entraîne pas de problème mais il pourrait car on envoie PC dans la mémoire

# EXPECTED
# sp: 16384
# t5: 20
# x5: 992
# x18: 0
# tp: 3

