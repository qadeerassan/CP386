#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 	10
typedef struct Node
{
    int data;
    struct Node *next;
} StackNode;

typedef struct ThreadArgs {
    int id;
    pthread_mutex_t *mutex;
} ThreadArgs;

StackNode *top;
// function prototypes
void push(int v, StackNode **top, pthread_mutex_t *thread_mutex);
int pop(StackNode **top, pthread_mutex_t *thread_mutex);
int is_empty(StackNode *top);
// push function
void push(int v, StackNode **top, pthread_mutex_t *thread_mutex)
{
    pthread_mutex_lock(thread_mutex);

    StackNode *new_node;
    printf("Thread is running Push() operation for value: %d\n", v);
    new_node = (StackNode *)malloc(sizeof(StackNode));
    new_node->data = v;
    new_node->next = *top;
    *top = new_node;
    pthread_mutex_unlock(thread_mutex);
}
// pop function
int pop(StackNode **top, pthread_mutex_t *thread_mutex)
{
    pthread_mutex_lock(thread_mutex);

	StackNode *temp;
    if (is_empty(*top)) {
        printf("Stack empty \n");
        pthread_mutex_unlock(thread_mutex);
        return 0;
	}
    else {
        int data = (*top)->data;
        printf("Thread is running Pop() operation and value is: %d\n",data);
		temp = *top;
        *top = (*top)->next;
		free(temp);
        pthread_mutex_unlock(thread_mutex);
        return data;
    }

}
//Check if top is NULL
int is_empty(StackNode *top) {
    if (top == NULL)
        return 1;
    else
        return 0;
}
// Thread's push function
void* thread_push(void *args)
{

    ThreadArgs *threadArgs = (ThreadArgs *)args;

    push(threadArgs->id + 1,&top, threadArgs->mutex);
    return NULL;
}
// Thread's pop function 
void* thread_pop(void *args){
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    pop(&top, threadArgs->mutex);
    return NULL;
}
// main function 
int main(void)
{
    pthread_mutex_t thread_mutex;
    StackNode *top = NULL;
    pthread_t threads_push[NUM_THREADS];
    pthread_t threads_pop[NUM_THREADS];

    pthread_mutex_init(&thread_mutex, NULL);


    ThreadArgs thread_args[NUM_THREADS];
    int i, j;
    // Creating push threads
    for(i=0;i<NUM_THREADS;i++){
	    thread_args[i].id = i;
        thread_args[i].mutex = &thread_mutex;
	    pthread_create(&threads_push[i],NULL,thread_push, (void *)&thread_args[i]);
	}

	// Create Pop Threads
	for(i=0;i<NUM_THREADS;i++){
        thread_args[i].id = i;
        thread_args[i].mutex = &thread_mutex;
	    pthread_create(&threads_pop[i],NULL,thread_pop, (void *)&thread_args[i]);
	}
	// Join Push Threads
	for(j = 0; j < NUM_THREADS; j++)
	{
	pthread_join(threads_push[j],NULL);
	}
    // Join Pop Threads
	for(j = 0; j < NUM_THREADS; j++)
	{
	pthread_join(threads_pop[j],NULL);
	}
    pthread_exit(NULL);
	return 0;
}
