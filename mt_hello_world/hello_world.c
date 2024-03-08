#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct mes_args_t
{
    char* str;
    int rank;
};

void *print_hello(void *ptr_args)
{
    struct mes_args_t *arg = (struct mes_args_t*) ptr_args;
    printf("%s %d\n", arg->str, arg->rank);
    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <nthreads>\n", argv[0]);
        return 1;
    }

    struct mes_args_t *args = (struct mes_args_t*) malloc(sizeof(struct mes_args_t));
    int nthreads = atoi(argv[1]);
    pthread_t *tid = (pthread_t*) malloc(nthreads * sizeof(pthread_t));
    for (int i = 0; i < nthreads; i ++)
    {
        args[i].str = "Hello World !";
        args[i].rank = i + 1;
        pthread_create(tid + i, NULL, print_hello, args + i);
    }

    for (int i = 0; i < nthreads; i ++)
    {
        pthread_join(tid[i], NULL);
    }
}