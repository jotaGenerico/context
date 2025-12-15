#!/bin/bash

# Verificar se pelo menos um argumento foi passado
if [ $# -eq 0 ]; then
  echo "Você precisa fornecer pelo menos um nome para as pastas."
  exit 1
fi

# Loop através de todos os argumentos
for nome in "$@"; do
  # Adicionar "ex" ao início do nome da pasta
  novo_nome="ex$nome"

  # Criar a pasta
  mkdir "$novo_nome"

  # Informar que a pasta foi criada
  echo "A pasta '$novo_nome' foi criada com sucesso."
done
