#!/bin/bash

MINISHELL=./minishell

echo "===================="
echo " TESTES DE PARSER"
echo "===================="

printf "\n[1] Comando simples\n"
printf "ls\nexit\n" | $MINISHELL

printf "\n[2] Redirecionamentos\n"
printf "cat < infile > outfile\nexit\n" | $MINISHELL

printf "\n[3] Pipe simples\n"
printf "ls | wc -l\nexit\n" | $MINISHELL

printf "\n[4] Lógicos\n"
printf "ls && echo ok\nexit\n" | $MINISHELL

printf "\n[5] Precedência\n"
printf "echo a && echo b || echo c\nexit\n" | $MINISHELL

printf "\n[6] Erro de sintaxe\n"
printf "ls ||| wc\nexit\n" | $MINISHELL
