#/bin/bash

echo "Laboratory work 4.1"

g++ lab4_1.cpp -o lab4_1
chmod a+x lab4_1
./lab4_1 1 2 3 4

rm lab4_1

echo "Laboratory work 4.2"

g++ -c lab4_2.cpp
g++ -o lab4_2 lab4_2.o -lpthread
chmod +x lab4_2
./lab4_2

rm lab4_2 lab4_2.o
