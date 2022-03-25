echo "Laboratory work with pipe"

g++ -c lab3_1.cpp
g++ -o lab3_1 lab3_1.o -lpthread
chmod +x lab3_1
./lab3_1

rm lab3_1 lab3_1.o

echo "Laboratory work 3 with pipe2"

g++ -c lab3_2.cpp
g++ -o lab3_2 lab3_2.o -lpthread
chmod +x lab3_2
./lab3_2

rm lab3_2 lab3_2.o

echo "Laboratory work 3 with fcntl"

g++ -c lab3_3.cpp
g++ -o lab3_3 lab3_3.o -lpthread
chmod +x lab3_3
./lab3_3

rm lab3_3 lab3_3.o