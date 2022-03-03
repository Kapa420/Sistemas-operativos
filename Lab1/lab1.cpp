#include <pthread.h>
#include <iostream>
#include <unistd.h>

/*
    Code by Arevalo Parra Carlos Andres
*/

struct thread_args
{
    int flag;
    char sym;
};

void *function1(void *arg){
    std::cout << "Thread 1 identificator: " << pthread_self() << std::endl;
    sleep(1);
    thread_args *arg1 = (thread_args *) arg;
    while (arg1 -> flag == 0){
        putchar(arg1 -> sym);
        fflush(stdout);
        sleep(1);
    };
    pthread_exit((void *)1);
}

void *function2(void *arg){
    std::cout << "Thread 2 identificator: " << pthread_self() << std::endl;
    sleep(1);
    thread_args *arg2 = (thread_args *) arg;
    while (arg2 -> flag == 0){
        putchar(arg2 -> sym);
        fflush(stdout);
        sleep(1);
    }

    pthread_exit((void*)2);
}

int main()
{
    int *exitcode1, *exitcode2;

    std::cout << "The programme have started" << std::endl;

    pthread_t id1, id2;

    struct thread_args arg1 = {0, '1'};
    struct thread_args arg2 = {0, '2'};

    std::cout << "Was created the thread 1" << std::endl;
    pthread_create(&id1, NULL, function1, &arg1);
    std::cout << "Was created the thread 2" << std::endl;
    pthread_create(&id2, NULL, function2, &arg2);
    getchar();

    arg1.flag = arg2.flag = 1;
    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);
    std::cout << "Exit code of thread 1 is: " << exitcode1 << std::endl;
    std::cout << "Exit code of thread 2 is: " << exitcode2 << std::endl;

    std::cout << "The programme have finished" << std::endl;

    return 0;
}