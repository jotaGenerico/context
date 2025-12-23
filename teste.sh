#!/bin/bash
# test.sh

echo "=== Testando mandatory ==="
cd philo
./philo 1 800 200 200
./philo 5 800 200 200
./philo 4 410 200 200

echo -e "\n=== Valgrind mandatory ==="
valgrind --leak-check=full ./philo 5 800 200 200

cd ..
