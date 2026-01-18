#!/bin/bash

MINISHELL=./minishell

echo "===================="
echo " TESTES DE AST"
echo "===================="

printf "\n[1] Comando simples\n"
printf "ls\nexit\n" | $MINISHELL

printf "\n[2] Pipe\n"
printf "ls | wc -l\nexit\n" | $MINISHELL

printf "\n[3] Lógicos\n"
printf "echo a && echo b\nexit\n" | $MINISHELL

printf "\n[4] Pipe + lógico\n"
printf "ls | grep c && echo ok\nexit\n" | $MINISHELL

printf "\n[5] Redirs + cmd\n"
printf "cat < infile | grep a > out\nexit\n" | $MINISHELL
