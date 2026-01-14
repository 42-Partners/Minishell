#!/bin/bash

MINISHELL=./minishell

echo "===================="
echo " TESTES DE LEXER"
echo "===================="

printf "\n[1] Tokens simples\n"
printf "ls -la\nexit\n" | $MINISHELL

printf "\n[2] Quotes simples\n"
printf "echo 'hello world'\nexit\n" | $MINISHELL

printf "\n[3] Quotes duplas\n"
printf "echo \"hello   world\"\nexit\n" | $MINISHELL

printf "\n[4] Redirecionamentos\n"
printf "cat < infile > outfile\nexit\n" | $MINISHELL

printf "\n[5] Operadores\n"
printf "ls && echo ok || echo fail\nexit\n" | $MINISHELL

printf "\n[6] Tokens colados\n"
printf "echo hello|cat\nexit\n" | $MINISHELL
