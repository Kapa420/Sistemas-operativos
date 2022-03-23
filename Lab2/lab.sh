#/bin/bash

echo "Laboratory work 2.1"

g++ -c lab2_1.cpp
g++ -o lab2_1 lab2_1.o -lpthread
chmod +x lab2_1
./lab2_1

rm lab2_1 lab2_1.o
echo "Laboratory work 2.2"

g++ -c lab2_2.c
g++ -o lab2_2 lab2_2.o -lpthread
chmod +x lab2_2
./lab2_2

rm lab2_2 lab2_2.o

echo "Laboratory work 2.3"

g++ -c lab2_3.cpp
g++ -o lab2_3 lab2_3.o -lpthread
chmod +x lab2_3
./lab2_3

rm lab2_3 lab2_3.o