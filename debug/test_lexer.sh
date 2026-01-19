#!/bin/bash

# Rode: ./debug/test_lexer.sh

# Vai para raiz do projeto (caso rode de outro lugar)
cd "$(dirname "$0")/.." || exit 1

# Verifica se minishell existe
if [ ! -f "./minishell" ]; then
    echo "Erro: ./minishell não encontrado!"
    echo "Compile primeiro com: make"
    exit 1
fi

echo "=========================================="
echo "TESTANDO LEXER DO MINISHELL"
echo "=========================================="

# Função auxiliar
test_cmd() {
    echo ""
    echo "TEST: $1"
    echo "$1" | ./minishell
    echo "---"
}

# ============ BÁSICO ============
echo ""
echo "=== COMANDOS BÁSICOS ==="

test_cmd "echo hello"
test_cmd "ls -la"
test_cmd "cat file.txt"
test_cmd "grep pattern"

# ============ PIPES ============
echo ""
echo "=== PIPES ==="

test_cmd "ls | grep test"
test_cmd "cat file | sort | uniq"
test_cmd "echo hello | cat | cat | cat"

# ============ REDIRECTS ============
echo ""
echo "=== REDIRECTS ==="

test_cmd "cat < input.txt"
test_cmd "ls > output.txt"
test_cmd "echo test >> file.txt"
test_cmd "cat << EOF"
test_cmd "ls > out.txt 2>&1"

# ============ COMBINAÇÕES ============
echo ""
echo "=== COMBINAÇÕES ==="

test_cmd "cat < in.txt > out.txt"
test_cmd "ls | grep test > result.txt"
test_cmd "echo hello | cat > file.txt"
test_cmd "cat << EOF | grep test"

# ============ QUOTES ============
echo ""
echo "=== QUOTES ==="

test_cmd 'echo "hello world"'
test_cmd "echo 'single quotes'"
test_cmd 'echo "it'\''s working"'
test_cmd 'echo '\''quote inside'\'''
test_cmd 'echo "hello" world "test"'
test_cmd 'echo hello"world"test'

# ============ VARIÁVEIS ============
echo ""
echo "=== VARIÁVEIS ==="

test_cmd 'echo $USER'
test_cmd 'echo $HOME $PATH'
test_cmd 'echo "$USER is here"'
test_cmd 'echo '\''$USER'\'''
test_cmd 'echo $?'

# ============ EDGE CASES ============
echo ""
echo "=== EDGE CASES ==="

test_cmd ""                          # vazio
test_cmd "   "                       # só espaços
test_cmd "echo"                      # comando só
test_cmd "echo          test"        # múltiplos espaços
test_cmd "|||"                       # múltiplos pipes
test_cmd ">>>"                       # múltiplos redirects
test_cmd "< > << >>"                 # só operadores
test_cmd "echo|cat"                  # sem espaços
test_cmd "echo>file"                 # redirect grudado
test_cmd "echo<file|cat>out"         # tudo grudado

# ============ QUOTES COMPLEXAS ============
echo ""
echo "=== QUOTES COMPLEXAS ==="

test_cmd 'echo "test'"'"'mixed'"'"'"'
test_cmd 'echo """'                  # múltiplas quotes
test_cmd 'echo "a"b"c"'              # alternadas
test_cmd 'echo '\'''\'''             # simples dentro de simples
test_cmd 'echo " " " "'              # espaços em quotes

# ============ PATHS ============
echo ""
echo "=== PATHS ==="

test_cmd "cat /home/user/file.txt"
test_cmd "ls ../test"
test_cmd "./script.sh"
test_cmd "echo ~/Documents"

# ============ CARACTERES ESPECIAIS ============
echo ""
echo "=== ESPECIAIS ==="

test_cmd 'echo $USER@$HOSTNAME'
test_cmd 'echo test-file_2024'
test_cmd 'echo "!@#$%^&*()"'
test_cmd 'echo path/to/file.txt'

# ============ ERROS ============
echo ""
echo "=== ERROS (devem falhar) ==="

test_cmd 'echo "unclosed'            # quote não fechada
test_cmd "echo 'unclosed"            # quote não fechada
test_cmd "ls ; pwd"                  # token inválido
test_cmd "echo && ls"                # token inválido
test_cmd "echo (test)"               # parênteses

# ============ NEWLINES ============
echo ""
echo "=== NEWLINES ==="

printf "echo hello\nls\nexit\n" | ./minishell

# ============ HEREDOC ============
echo ""
echo "=== HEREDOC ==="

test_cmd "cat << EOF"
test_cmd "cat << 'EOF'"
test_cmd "grep test << END"

echo ""
echo "=========================================="
echo "TESTES CONCLUÍDOS"
echo "Resultados salvos em: debug/results.txt"
echo "=========================================="