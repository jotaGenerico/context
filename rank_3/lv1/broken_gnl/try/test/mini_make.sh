# Buffer pequeno (stresstest)
gcc -D BUFFER_SIZE=1 main.c gnl.c -o test_gnl && ./test_gnl

# Buffer médio
gcc -D BUFFER_SIZE=10 main.c gnl.c -o test_gnl && ./test_gnl

# Buffer grande
gcc -D BUFFER_SIZE=1024 main.c gnl.c -o test_gnl && ./test_gnl
