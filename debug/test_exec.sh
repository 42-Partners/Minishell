#!/bin/bash

MINISHELL=./minishell

echo "===================="
echo " TESTES DE EXEC"
echo "===================="

printf "\n[1] Exec simples\n"
printf "echo hello\nexit\n" | $MINISHELL

printf "\n[2] Builtin\n"
printf "pwd\nexit\n" | $MINISHELL

printf "\n[3] Redirecionamento saída\n"
printf "echo hello > /tmp/ms_test\ncat /tmp/ms_test\nexit\n" | $MINISHELL

printf "\n[4] Exit status\n"
printf "false\necho $?\nexit\n" | $MINISHELL

printf "\n[5] Exec inválido\n"
printf "comando_inexistente\nexit\n" | $MINISHELL
