# Teste 1: Exit normal
$ exit
exit
# Status: 0 ✅

# Teste 2: Exit com número
$ exit 42
exit
# Status: 42 ✅

# Teste 3: Exit com overflow
$ exit 257
exit
# Status: 1 (257 % 256) ✅

# Teste 4: Exit com negativo
$ exit -1
exit
# Status: 255 ✅

# Teste 5: Argumento inválido
$ exit abc
exit
exit: abc: numeric argument required
# Status: 2 ✅

$ exit +
exit
exit: +: numeric argument required
# Status: 2 ✅

$ exit -
exit
exit: -: numeric argument required
# Status: 2 ✅

$ exit "12 34"
exit
exit: 12 34: numeric argument required
# Status: 2 ✅

# Teste 6: Muitos argumentos
$ exit 1 2 3
exit
exit: too many arguments
# NÃO sai, status 1 ✅
$ echo $?
1  ✅

# Teste 7: Em pipe (não imprime "exit")
$ exit | cat
# (sem output)
# Status: 0 ✅

# Teste 8: Espaços e sinais
$ exit "  +42  "
exit
# Status: 42 ✅

$ exit "  -42  "
exit
# Status: 214 (-42 % 256 + 256) ✅