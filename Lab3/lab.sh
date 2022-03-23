echo "Laboratory work 3.1"

g++ -c lab3_1.cpp
g++ -o lab3_1 lab3_1.o -lpthread
chmod +x lab3_1
./lab3_1

rm lab3_1 lab3_1.o