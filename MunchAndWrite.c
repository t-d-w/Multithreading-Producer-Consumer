/**
 * MunchAndWrite.c
 *
 * Author - Thomas Wilkinson
 * Author - Na Li
 *
 * Description: handles the enqueue and dequeue actions in munch1 and munch2 thread.
 */
#include "Queue.h"
#include "MunchAndWrite.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#define BUFSIZE 4096


/**
 * munch1Execute
 *
 * munch1Execute is the function that the munch1 thread runs. This dequeues, changes spaces to * and
 * then enqueues into q2
 *
 * @param - void *inputQueues - the generic pointer which is to be casted to strcut Queue **, contains 
 * both of the queues needed for this method, q1 and q2
 * @return - void * - generic pointer return value is unused.
 */
void *munch1Execute(void *inputQueues){
	struct Queue **queues = (struct Queue **)inputQueues;
	struct Queue *q1 = queues[0];
	struct Queue *q2 = queues[1];

	char *buffer;
   	size_t bufsize = BUFSIZE;
    	//
	//size_t characters;
   	char *loc;

    	buffer = (char *)malloc(bufsize * sizeof(char));
    	if( buffer == NULL){
        	perror("Unable to allocate buffer");
        	exit(1);
    	}

    	//printf("Type something: ");
    	//characters = getline(&buffer,&bufsize,stdin);
    	//printf("%zu characters were read.\n",characters);
    	//printf("You typed: '%s'\n",buffer);
	
//	int capacity = q1->capacity;
	
	//bool threadFinished = false;
	while(1){
		//printf("about to dequeue. So for q1, value at rear q->array[q->rear] is: %s\n", q1->array[q1->rear]);
		buffer = DequeueString(q1);
		if(buffer == NULL){
			// reader has finished
			break;
		}
		//printf("the latest dequeue is: %s\n", buffer);
    		loc = index(buffer, ' ');
    		//printf("location %ld\n", loc-buffer);
    		while(loc != NULL){
       			buffer[loc-buffer] = '*';
       			loc = index(buffer, ' ');
    		}
		//printf("ADDING INTO THE SECOND QUEUE: %s\n", buffer);
		EnqueueString(q2, buffer);
	}
	EnqueueString(q2, NULL);
        pthread_exit(NULL);	
}	


/**
 * munch2Execute
 *
 * munch2Execute is the function that the munch2 thread runs. It dequeues from the first queue, sets the 
 * letters to capitals, and then enqueues into q3
 *
 * @param - void *inputQueues - the generic pointer that should be casted to a struct Queue ** which contains
 * both the queues that this function needs
 * @return - void * - generic pointer that is returned, but not used
 */
void *munch2Execute(void *inputQueues){
	struct Queue **queues = (struct Queue**)inputQueues;
	struct Queue *q2 = queues[0];
	struct Queue *q3 = queues[1];

	char *buffer;
    	size_t bufsize = BUFSIZE;
    	//size_t characters;

    	buffer = (char *)malloc(bufsize * sizeof(char));
    	if( buffer == NULL){
        	perror("Unable to allocate buffer");
        	exit(1);
    	}

    	//printf("Type something: ");

    	//getline(&buffer,&bufsize,stdin);
	while(1){
		buffer = DequeueString(q2);
    		if(buffer == NULL){
			break;
		}
		
		char *s = buffer;
    		while(*s){
	  		*s = toupper((unsigned char) *s);
	    		s++;
    		}
		EnqueueString(q3, buffer);
	}
    	//printf("Buffer after uppercase:  %s\n", buffer);
	EnqueueString(q3, NULL);
	pthread_exit(NULL);
}


/** 
 * writerExecute
 *
 */
void *writerExecute(void *inputQueue){
	struct Queue *q3 = (struct Queue *)inputQueue;
	
	char *buffer;
    	size_t bufsize = BUFSIZE;

   	buffer = (char *)malloc(bufsize * sizeof(char));
   	if( buffer == NULL){
       		perror("Unable to allocate buffer");
      		exit(1);
    	}

    	//printf("Type something: ");
	//for(int i = 0; i < q3->capacity; i++){
    	while(1){
		buffer = DequeueString(q3);
    		if(buffer == NULL){
			break;
		}
		printf("%s\n", buffer);
		free(buffer);
		//printf("after free the buffer is: %s\n", buffer);
	}
	
	// may need to consider to free buffer for other threads!!
   	//printf("After free %s\n", buffer);
	pthread_exit(NULL);
}
 
