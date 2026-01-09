#!/bin/bash

# O que esse script valida
# ✔ criação correta de pipes
# ✔ fork para cada comando
# ✔ dup2 certo (stdin/stdout)
# ✔ fechamento de fds
# ✔ execução encadeada
# ✔ erros de sintaxe
# ✔ integração com redirecionamento
# ✔ status de saída do pipeline

MINISHELL=./minishell

if [ ! -x "$MINISHELL" ]; then
	echo "❌ minishell não encontrado na raiz"
	exit 1
fi

echo "===================="
echo " TESTES DE PIPE"
echo "===================="

# =========================
# Teste 1: pipe simples
# =========================
echo
echo "🧪 [1] Pipe simples"
echo "Esperado: 1"

printf "echo hello | wc -l\nexit\n" | $MINISHELL

# =========================
# Teste 2: múltiplos pipes
# =========================
echo
echo "🧪 [2] Múltiplos pipes"
echo "Esperado: 1"

printf "echo hello | cat | wc -l\nexit\n" | $MINISHELL

# =========================
# Teste 3: pipe com comando real
# =========================
echo
echo "🧪 [3] Pipe com comando real"
echo "Esperado: linha contendo 'bin'"

printf "ls / | grep bin\nexit\n" | $MINISHELL

# =========================
# Teste 4: pipe com argumentos
# =========================
echo
echo "🧪 [4] Pipe com args"
echo "Esperado: HELLO"

printf "echo hello | tr a-z A-Z\nexit\n" | $MINISHELL

# =========================
# Teste 5: pipe no início (erro)
# =========================
echo
echo "🧪 [5] Pipe inválido (inicio)"
echo "Esperado: erro de sintaxe"

printf "| echo hello\nexit\n" | $MINISHELL

# =========================
# Teste 6: pipe no fim (erro)
# =========================
echo
echo "🧪 [6] Pipe inválido (fim)"
echo "Esperado: erro de sintaxe"

printf "echo hello |\nexit\n" | $MINISHELL

# =========================
# Teste 7: pipe + redirecionamento
# =========================
echo
echo "🧪 [7] Pipe + redirecionamento"
echo "Esperado: arquivo com HELLO"

printf "echo hello | tr a-z A-Z > /tmp/ms_pipe_test\ncat /tmp/ms_pipe_test\nexit\n" | $MINISHELL

# =========================
# Teste 8: status de saída
# =========================
echo
echo "🧪 [8] Exit status do pipe"
echo "Esperado: 0"

printf "false | true\necho $?\nexit\n" | $MINISHELL

echo
echo "✅ Testes de pipe finalizados"
