#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

struct thread_args
{
    int flag;
    char sym;
};

void *function1(void *arg)
{
    std::cout << "Thread 1 identificator: " << pthread_self() << std::endl;
    thread_args *arg1 = (thread_args *)arg;

    while(arg1 -> flag == 0)
    {
        pthread_mutex_lock(&mutex);

        for (int i = 0; i < 2; i++)
        {
            putchar(arg1->sym);
            fflush(stdout);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit((void*)1);
}

void *function2(void *arg)
{
    std::cout << "Thread 2 identificator: " << pthread_self() << std::endl;
    thread_args *arg2 = (thread_args *)arg;

    while (arg2->flag == 0)
    {
        pthread_mutex_lock(&mutex);
        
        for (int i = 0; i < 2; i++)
        {
            putchar(arg2->sym);
            fflush(stdout);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit((void *)2);
}


int main(int argc, char const *argv[])
{
    mutex = PTHREAD_MUTEX_INITIALIZER;

    int *exitcode1, *exitcode2;
    
    pthread_t id1, id2;

    thread_args arg1 = {0, '1'};
    thread_args arg2 = {0, '2'};

    if(pthread_create(&id1, NULL, function1, &arg1) != 0)
        std::cout << "The thread could not be created" << std::endl;
        
    if(pthread_create(&id2, NULL, function2, &arg2) != 0)
        std::cout << "The thread could not be created" << std::endl;
    
    getchar();

    arg1.flag = arg2.flag = 1;

    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);

    std::cout << "\nExit code of thread 1 is: " << exitcode1 << std::endl;
    std::cout << "Exit code of thread 2 is: " << exitcode2 << std::endl;

    pthread_mutex_destroy(&mutex);
    return 0;
}

