#!/bin/bash

# Verifica se nenhum argumento foi fornecido
if [ $# -eq 0 ]; then
  echo "Nenhum argumento fornecido."
else
  # Imprime o primeiro argumento, se disponível
  if [ $# -ge 1 ]; then
    echo "$1"
  fi

  # Imprime o segundo argumento, se disponível
  if [ $# -ge 2 ]; then
    echo "$2"
  fi

  # Imprime o terceiro argumento, se disponível
  if [ $# -ge 3 ]; then
    echo "$3"
  fi
fi
