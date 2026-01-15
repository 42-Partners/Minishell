# ============ BÁSICO ============
# Teste 1: Echo simples
echo hello

# Teste 2: Múltiplos argumentos
echo hello world test

# Teste 3: Sem argumentos
echo

# Teste 4: Só espaços (deveria imprimir linha vazia)
echo "   "

# ============ FLAG -n ============
# Teste 5: Echo sem newline
echo -n hello

# Teste 6: Múltiplos -n
echo -n -n -n hello world

# Teste 7: -n no meio (não funciona, vira literal)
echo hello -n world

# Teste 8: -n com string vazia
echo -n

# Teste 9: -n seguido de mais argumentos
echo -n "test" "abc"

# ============ QUOTES ============
# Teste 10: Aspas duplas
echo "hello world"

# Teste 11: Aspas simples
echo 'hello world'

# Teste 12: Quotes mistas
echo "it's working"
echo 'he said "hi"'

# Teste 13: Quotes vazias
echo ""
echo ''

# Teste 14: Múltiplas quotes
echo "hello" "world" 'test'

# ============ VARIÁVEIS ============
# Teste 15: Expansão simples
echo $USER
echo $HOME

# Teste 16: Expansão em aspas duplas
echo "User: $USER"

# Teste 17: Sem expansão em aspas simples
echo '$USER'

# Teste 18: Variável inexistente
echo $NAOEXISTE

# Teste 19: Exit status
ls
echo $?

# ============ EDGE CASES ============
# Teste 20: Múltiplos espaços
echo hello     world     test

# Teste 21: Tabs
echo hello	world

# Teste 22: Newline em aspas
echo "hello
world"

# Teste 23: Aspas grudadas
echo hello"world"
echo "hello"world

# Teste 24: Só -n
echo -n

# Teste 25: -n com newline literal
echo -n "test
next"

# ============ PIPELINES ============
# Teste 26: Echo com pipe
echo "hello world" | cat

# Teste 27: Echo com grep
echo "test line" | grep test

# Teste 28: Echo com wc
echo "one two three" | wc -w

# Teste 29: Múltiplos pipes
echo "hello" | cat | cat | cat

# Teste 30: Echo com redirect
echo "test" > output.txt
cat output.txt

# Teste 31: Echo append
echo "line1" > file.txt
echo "line2" >> file.txt
cat file.txt

# Teste 32: Pipeline complexo
echo "hello world test" | grep world | wc -l

# Teste 33: -n com pipe
echo -n "test" | cat

# Teste 34: Variável com pipe
echo $USER | grep $USER

# ============ COMPARAÇÃO BASH ============
# Rode no bash e compare saída:
bash -c 'echo -n hello; echo world'
# vs seu minishell
echo -n hello
echo world