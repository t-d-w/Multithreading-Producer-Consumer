/**
 * Queue.h
 *
 *
 *
 *
 *
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>


struct Queue{
	
       // pthread_mutex_t *mutexLock;
	int queueID;
        char **array;
        int bufferSize;
	int capacity;
        //int currentSize;
        int front;
        int rear;

        // for Queue statistics
	struct QueueStats *myQueueStats;

	//initizlize the mutex & Condition Variables
        pthread_mutex_t lock;// Lock shared resources among theads
        pthread_cond_t full; // Condition indicating queue is full
        pthread_cond_t empty; // Condition indicating queue is empty

};


/**
 * CreateStringQueue
 *
 * Allocate a new Queue structure, initialize it with array of character pointers of length size.
 *
 * @param - int size - size of the char array
 * @return - *Queue - a pointer to the new queue structure
 */
struct Queue* CreateStringQueue(int capacity, int queueID);

/**
 * EnqueueString
 *
 * Places the pointer to the string at the end of the queue q. If queue is full, this function waits
 * until space available
 *
 * @param - Queue *q - the Queue that we wish to add to
 * @param - char *string - the char array we wish to add to the queue
 */
void EnqueueString(struct Queue *q, char *string);

/**
 * DequeueString
 *
 * Removes a pointer to a string from the beginning. If queue is empty, then function blocks until a string
 * is added to the queue. 
 *
 * @param - Queue *q - pointer to the queue that we remove the pointer from 
 * @return - char * - the string that was removed from the queue
 */
char* DequeueString(struct Queue *q);

/**
 * PrintQueueStats
 *
 * Prints statistics for Queue q
 *
 * @param - Queue *q - the queue to print stats for
 */
void PrintQueueStats(struct Queue *q);


#endif // QUEUE_H





