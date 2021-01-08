/**
 * Queue.c
 * 
 * Author - Thomas Wilkinson
 * Author - Na Li
 *
 *Description: Queue.c provide methods to create a string queue, enqueue, dequeue methods and print out the queue statistics
 */

#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "Queue.h"
#include "QueueStats.h"
#define BUFFERSIZE 4096



/**
 * CreateStringQueue
 *
 * Allocate a new Queue structure, initialize it with array of character pointers of length size.
 *
 * @param - int size - size of the char array
 * @return - *Queue - a pointer to the new queue structure
 */
struct Queue* CreateStringQueue(int capacity, int queueID){

	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue)); 
        queue->capacity = capacity; 
        queue->front = 0;
	queue->bufferSize = BUFFERSIZE; 
	queue->queueID = queueID;

	queue->myQueueStats = CreateQueueStats();

        // This is important, see the enqueue 
        queue->rear = 0; 
        queue->array = (char**)malloc(queue->capacity * sizeof(char*));
       	
	//initizlize the mutex & Condition Variables
	pthread_mutex_init( &queue -> lock, NULL);
        pthread_cond_init( &queue ->full, NULL);
        pthread_cond_init( &queue -> empty, NULL);	
        return queue;
}

/**
 * ModIncr
 * 
 * update the index of the queue to be enqued or dequeued at
 *
 * @param - index - the index in the queue to be updated at
 * @param - Queue *q - the Queue that we wish to work on
 * @return - return the updated index in the queue;
 *
 */
int ModIncr(int index, struct Queue *q){
        int thisCapacity = q->capacity;
        return (index+1)%thisCapacity;
}

/**
 * EnqueueString
 *
 * Places the pointer to the string at the end of the queue q. If queue is full, this function waits
 * until space available
 *
 * @param - Queue *q - the Queue that we wish to add to
 * @param - char *string - the char array we wish to add to the queue
 */
void EnqueueString(struct Queue *q, char *string){	

	// check start and end wallclock time
	struct timeval start, end;
        gettimeofday(&start, NULL);
	// use the mutual exclusion lock
	pthread_mutex_lock(&q->lock);
		
	int modRetVal = ModIncr(q->rear, q);
        while(modRetVal == q->front){
                // wait for an empty spot
		pthread_cond_wait(&q->full, &q->lock);//full, wait for dequeue
		
        }
	// set the spot in the queue, then incrememnt
	q->array[q->rear] = string;
        q->rear = ModIncr(q->rear, q);
	// signal that weve added, then unlock the mutual exclusion
        pthread_cond_signal(&q->empty);
	pthread_mutex_unlock(&q->lock);
	
	// do statistics stuff
	gettimeofday(&end, NULL);
        double elapsed = end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)/1000000 ;
 	
	q->myQueueStats->enqueueTime += elapsed;
	q->myQueueStats->enqueueCount++;
	printf("Enqueue time is: %f", q->myQueueStats->enqueueTime);
	
	
}

/**
 * DequeueString
 *
 * Removes a pointer to a string from the beginning. If queue is empty, then function blocks until a string
 * is added to the queue. 
 *
 * @param - Queue *q - pointer to the queue that we remove the pointer from 
 * @return - char * - the string that was removed from the queue
 */
char* DequeueString(struct Queue *q){
	//lock = q->lock;
	
	struct timeval start, end;
	gettimeofday(&start, NULL);

	pthread_mutex_lock(&q->lock);
	
	// check start and end wallclock time

	while(q->front == q->rear){
                //printf("waiting for a signal... Enqueue Count: %i\n", q->enqueueCount);
		pthread_cond_wait(&q->empty, &q->lock); // empty, wait to enqueue
		//printf("signal recieved...Enqueue count: %i\n", q->enqueueCount);
       	}
	
	//for(int i = 0; i < q->capacity; i++){
	//	printf("value at index %i is: %s\n", i, q->array[i]);
	//}
	char *removeString = q->array[q->front];
	//printf("the string that is being dequeued is: %s\n", removeString);
        q->front = ModIncr(q->front, q);
        //q->dequeueCount++;
        pthread_cond_signal(&q->full);
	
	pthread_mutex_unlock(&q->lock);

        gettimeofday(&end, NULL);
        double elapsed = end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)/1000000 ;
	q->myQueueStats->dequeueCount++;
        q->myQueueStats->dequeueTime += elapsed;
	printf("dequeue time is: %f\n", q->myQueueStats->dequeueTime);
	


	return removeString;
}

/**
 * PrintQueueStats
 *
 * Prints statistics for Queue q
 *
 * @param - Queue *q - the queue to print stats for
 */
void PrintQueueStats(struct Queue *q){

        printf("Enqueue Count: %i\n", q->myQueueStats->enqueueCount);
	printf("Dequeue Count: %i\n", q->myQueueStats->dequeueCount);
	printf("Enqueue Time: %f\n", q->myQueueStats->enqueueTime);
	printf("Dequeue Time: %f\n", q->myQueueStats->dequeueTime);
}
