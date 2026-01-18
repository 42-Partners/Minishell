# ============ BÁSICO ============
# Teste 1: cd para diretório relativo
cd src
pwd

# Teste 2: cd para diretório absoluto
cd /tmp
pwd

# Teste 3: cd volta para anterior (..)
cd ..
pwd

# Teste 4: cd para HOME (sem argumentos)
cd
pwd

# Teste 5: cd para HOME explícito
cd ~
pwd

# Teste 6: cd para diretório anterior (-)
cd /tmp
cd /home
cd -
pwd

# Teste 7: cd - múltiplas vezes (alterna entre dois dirs)
cd /tmp
cd /home
cd -
cd -
pwd

# ============ VARIÁVEIS ============
# Teste 8: Verificar PWD atualiza
cd /tmp
echo $PWD

# Teste 9: Verificar OLDPWD atualiza
cd /home
cd /tmp
echo $OLDPWD

# Teste 10: cd com variável
cd $HOME
pwd

# ============ ERROS ============
# Teste 11: Diretório não existe
cd /diretorio/inexistente

# Teste 12: Sem permissão (se possível)
cd /root

# Teste 13: Muitos argumentos
cd /tmp /home

# Teste 14: cd para arquivo (não é diretório)
touch testfile
cd testfile
rm testfile

# Teste 15: HOME não setado
unset HOME
cd
export HOME=/home/$USER

# Teste 16: OLDPWD não setado (primeira vez)
# (novo shell - não há OLDPWD ainda)
cd -

# ============ EDGE CASES ============
# Teste 17: cd com espaços no nome
mkdir "test dir"
cd "test dir"
pwd
cd ..
rmdir "test dir"

# Teste 18: cd . (fica no mesmo)
cd .
pwd

# Teste 19: cd com path complexo
cd ./src/../includes
pwd

# Teste 20: cd com múltiplos ..
cd ../../..
pwd

# Teste 21: cd / (raiz)
cd /
pwd

# Teste 22: cd ~ seguido de path
cd ~/Documents
pwd

# ============ SEQUÊNCIA ============
# Teste 23: Múltiplos cd em sequência
cd /tmp
cd /home
cd /usr
pwd

# Teste 24: cd alternando com outros comandos
cd /tmp
ls
cd /home
echo "test"
pwd

# Teste 25: cd em pipeline (não deveria afetar)
echo test | cd /tmp
pwd  # deve estar em /tmp

# ============ COMPARAÇÃO PWD ============
# Teste 26: Verificar consistência
cd /tmp
pwd
echo $PWD
# Ambos devem mostrar /tmp

# Teste 27: cd - imprime diretório
cd /tmp
cd /home
cd -  # deve imprimir /tmp

# Teste 28: Caminho relativo complexo
cd src
cd ../includes
pwd

# Teste 29: Links simbólicos (se tiver)
ln -s /tmp linktest
cd linktest
pwd
cd ..
rm linktest