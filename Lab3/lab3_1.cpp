#include <sys/sysinfo.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

struct thread_args 
{
    int flag;
};

int filedes[2];
struct sysinfo so;

void *reader (void *arg){
    thread_args *arg1 = (thread_args *)arg;
    long buffer;
    while (arg1->flag == 0)
    {
        if (read(filedes[0], &buffer, 8) != -1)
        {
            std::cout << "Total RAM: " << buffer / (1024 * 1024) << std::endl;
        }
        else
        {
            std::cout << "Fail reading data" << std::endl;
        }
        sleep(1);
    }
    pthread_exit((void *)1);
};

void *writer (void *arg){
    sysinfo(&so);
    thread_args *arg2 = (thread_args *)arg;
    long buffer;
    while (arg2->flag == 0)
    {
        buffer = so.totalram;
        write(filedes[1], &buffer, 8);
        sleep(1);
    }
    pthread_exit((void *)2);
};

int main(int argc, char const *argv[])
{
    int *exitcode1, *exitcode2;

    pthread_t id1, id2;

    thread_args arg1 = {0};
    thread_args arg2 = {0};

    pipe(filedes);
    pipe2(filedes, O_NONBLOCK);

    if (pthread_create(&id1, NULL, writer, &arg1) != 0)
        std::cout << "The thread could not be created" << std::endl;

    if (pthread_create(&id2, NULL, reader, &arg2) != 0)
        std::cout << "The thread could not be created" << std::endl;

    getchar();

    arg1.flag = arg2.flag = 1;

    pthread_join(id1, (void **)&exitcode1);
    pthread_join(id2, (void **)&exitcode2);

    std::cout << "\nExit code of thread 1 is: " << exitcode1 << std::endl;
    std::cout << "Exit code of thread 2 is: " << exitcode2 << std::endl;

    close(*filedes);
    return 0;
}

