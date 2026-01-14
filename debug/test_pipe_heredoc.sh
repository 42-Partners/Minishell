#!/bin/bash

# O que esses testes validam (de verdade)

# ✔ here-doc alimentando pipe
# ✔ ordem correta de criação de fds
# ✔ here-doc antes do fork
# ✔ dup2 correto em cadeia
# ✔ fechamento de fd (senão trava)
# ✔ precedência na AST
# ✔ integração com redirecionamento
# ✔ comportamento real de shell

MINISHELL=./minishell

if [ ! -x "$MINISHELL" ]; then
	echo "❌ minishell não encontrado na raiz"
	exit 1
fi

echo "============================"
echo " TESTES PIPE + HERE-DOC"
echo "============================"

# =========================
# Teste 1: heredoc -> pipe
# =========================
echo
echo "🧪 [1] here-doc | pipe"
echo "Esperado: 2"

printf \
"cat << EOF | wc -l
linha 1
linha 2
EOF
exit
" | $MINISHELL

# =========================
# Teste 2: pipe -> heredoc (inválido)
# =========================
echo
echo "🧪 [2] pipe antes do here-doc (erro)"
echo "Esperado: erro de sintaxe"

printf \
"| cat << EOF
teste
EOF
exit
" | $MINISHELL

# =========================
# Teste 3: heredoc no meio do pipe
# =========================
echo
echo "🧪 [3] cmd | here-doc | cmd"
echo "Esperado: TEXTO"

printf \
"echo texto | cat << EOF | tr a-z A-Z
ignored
EOF
exit
" | $MINISHELL

# =========================
# Teste 4: múltiplos here-docs no pipe
# =========================
echo
echo "🧪 [4] múltiplos here-docs"
echo "Esperado: dois blocos"

printf \
"cat << A | cat
primeiro
A
cat << B | cat
segundo
B
exit
" | $MINISHELL

# =========================
# Teste 5: heredoc + redir + pipe
# =========================
echo
echo "🧪 [5] heredoc | pipe > file"
echo "Esperado: arquivo com TEXTO"

printf \
"cat << EOF | tr a-z A-Z > /tmp/ms_hd_pipe
texto
EOF
cat /tmp/ms_hd_pipe
exit
" | $MINISHELL

# =========================
# Teste 6: CTRL+D no heredoc (manual)
# =========================
echo
echo "🧪 [6] CTRL+D no here-doc (manual)"
echo "Digite algo e finalize com CTRL+D"

$MINISHELL

echo
echo "✅ Testes PIPE + HERE-DOC finalizados"
