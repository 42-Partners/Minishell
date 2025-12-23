#!/bin/bash

export MYVAR="hello"
export EMPTY=""
unset UNDEF

tests=(
'echo $MYVAR'
'echo "$MYVAR"'
'echo $EMPTY'
'echo "$EMPTY"'
'echo $UNDEF'
'echo "$UNDEF"'
'echo $1 $2 $9'
'echo "Hello $MYVAR"'
'echo Hello$MYVAR'
'echo "$EMPTY-$UNDEF"'
'echo $'
'echo "price is $"'
'echo "$A-$B-$C-$D"'
)

for t in "${tests[@]}"; do
    echo "-----------------------------------"
    echo "Running: $t"
    ../minishell <<< "$t"
done