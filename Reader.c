/**
 * Reader.c
 *
 * Authors:
 * Na Li
 * Thomas Wilkinson
 *
 * Description: Thread Reader will read in each input line from stdin. You must check that the input line does not exceed the size of your buffer. If it does exceed the length, then you will reject that line by (1) printing out an error message to stderr and (2) throw away (flush to end of line) any remaining characters on that line.
 *
 */
#include "Queue.h"
#include <stdbool.h>
#define BUFFERSIZE 4096

/**
 * readLine
 *
 * readLine reads the stdin, and enqueues into the inputQueue.
 *
 * @param - void *inputQueue - the input Queue to put everything in. Should be immediately casted to a struct Queue pointer
 * @return - void * - generic pointer that is not used. nothing is returned thread exits
 */
void *readLine(void *inputQueue){
	// read the line
	// add to the queue
	struct Queue *q = (struct Queue *)inputQueue;

	bool endOfFileFound = false;	
	while(!endOfFileFound){
		char* buffer = malloc(sizeof(char) * BUFFERSIZE);
		// read the stdin into the buffer
		
		int j = 0;

		bool loopAgain = true;
		bool overfilled = false;
		//bool readingChars = true;
		bool storeChars = true;
		while(loopAgain){
			char thisChar = getc(stdin);
		
			if(j == BUFFERSIZE-1){
				// we have exceeded the buffer size
				overfilled = true;
				//readingChars = false;
				storeChars = false;
				
			} else if(thisChar == EOF){
				
				loopAgain = false;
				endOfFileFound = true;
			} else if(thisChar == '\n' || thisChar == '\0'){
				loopAgain = false;
			} else if (storeChars){
				buffer[j] = thisChar;
			}
			j++;
		}

		if(!overfilled){
			//char thisChar = buffer[0];
			// onyl goes in if the first line is not EOF or end of line
			if(buffer != NULL){
				buffer[j+1] = '\0';	
				EnqueueString(q, buffer);
				
			}

		} else {
			
			fprintf(stderr, "This line was skipped over because it was too long.\n");
			
		}
		// enqueue the buffer
			
	}
	// we went through the entire capacity
	
	EnqueueString(q, NULL);
	pthread_exit(NULL);
}
