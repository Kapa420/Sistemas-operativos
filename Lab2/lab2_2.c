#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct thread_args
{
    int flag;
    char sym;
};

void *function1(void *arg)
{
    printf("Thread 1 identificator: %d \n", pthread_self());
    struct thread_args *arg1 = (struct thread_args *)arg;

    while (arg1->flag == 0)
    {
        sleep(1);

        if(!pthread_mutex_trylock(&mutex))
        {
            for (int i = 0; i < 3; i++)
            {
                putchar(arg1->sym);
                fflush(stdout);
                sleep(1);
            }
        pthread_mutex_unlock(&mutex);
        }
        else
        {
            sleep(3);
        }
    }
    pthread_exit((void *)1);
}

void *function2(void *arg)
{
    printf("Thread 2 identificator: %d \n",pthread_self());
    struct thread_args *arg2 = ( struct thread_args *)arg;

    while (arg2->flag == 0)
    {
        sleep(1);

        if(!pthread_mutex_trylock(&mutex))
        {
            for (int i = 0; i < 3; i++)
            {
                putchar(arg2->sym);
                fflush(stdout);
                sleep(1);
            }
            pthread_mutex_unlock(&mutex);
        }
        else 
        {
            sleep(3);
        }
    }
    pthread_exit((void *)2);
}

int main(int argc, char const *argv[])
{
    int *exitcode1, *exitcode2;

    pthread_t id1, id2;

    struct thread_args arg1 = {0, '1'};
    struct thread_args arg2 = {0, '2'};

    if (pthread_create(&id1, NULL, function1, &arg1) != 0)
        printf("The thread could not be created\n");


    if (pthread_create(&id2, NULL, function2, &arg2) != 0)
        printf("The thread could not be created");

    getchar();

    arg1.flag = arg2.flag = 1;

    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);

    printf("\nExit code of thread 1 is: %d \n", exitcode1);
    printf("Exit code of thread 2 is: %d \n", exitcode2);

    pthread_mutex_destroy(&mutex);
    return 0;
}