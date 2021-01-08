/**
 * Main.c
 *
 * Author - Thomas Wilkinson
 * Author - Na Li
 *
 * Description: Main.c contains the main method, which handles the creation and interactions of the Reader, Munch1, Munch2,and Writer threads.
 *
 *
 */

#include "Reader.h"
#include "Queue.h"
#include "MunchAndWrite.h"
#include <pthread.h>
#define BUFFERSIZE 4096

/**
 *      main: handles the creation and interactions of the Reader, Munch1, Munch2,and Writer threads.
 *
 *      @return: int - successful returns 0
 */      

int main(){

	// create four threads
	pthread_t reader;
	pthread_t munch1;
	pthread_t munch2;
	pthread_t writer;
	
	// create three queues
	int thisCapacity = 10;
	struct Queue *q1 = CreateStringQueue(thisCapacity, 1); // reader feeds the stdin info into this queue. Munch1 uses this and then feeds into q2
        struct Queue *q2 = CreateStringQueue(thisCapacity, 2); // munch1 feeds into this, munch2 uses this and then feeds into writer
	struct Queue *q3 = CreateStringQueue(thisCapacity, 3); // munch uses q2 thne feeds into this queue. Which is then fed to writer to be 
	// dequeed and printed out


	// create the pointers to pointers for passing through munch1
	struct Queue **toMunch1 = malloc(sizeof(struct Queue *)*2);
	toMunch1[0] = q1;
	toMunch1[1] = q2;
	if(!toMunch1){
		printf("toMunch1 created unsuccessfully\n");
		exit(1);
	}
        
	// create the pointers to pointers for passing through munch2
	struct Queue **toMunch2 = malloc(sizeof(struct Queue *)*2);
	toMunch2[0] = q2;
	toMunch2[1] = q3;
	if(!toMunch2){
		printf("toMunch2 created unsuccessfully\n");
		exit(1);
	}

	// Create the four threads, make sure that they are created properly
	int read_p = pthread_create(&reader, NULL, &readLine, (void *)q1);
	if(read_p != 0){
        	printf("unsuccessful thread creation");
		exit(1);
	}

	int munch1_p = pthread_create(&munch1, NULL, &munch1Execute, (void *)toMunch1);

	if(munch1_p != 0){
        	printf("unsuccessful thread creation");
		exit(1);
	}

	int munch2_p = pthread_create(&munch2, NULL, &munch2Execute, (void *)toMunch2);
	if(munch2_p != 0){
		printf("unsuccessful thread creation\n");
		exit(1);
	}
	
	int writer_p = pthread_create(&writer, NULL, &writerExecute, (void *)q3);
	if(writer_p != 0){
		printf("unsuccessful thread creation\n");
		exit(1);
	}


	// now wait for those threads to terminate
	if(pthread_join(reader, NULL) != 0){
		printf("Error waiting for the reader thread to terminate\n");
		exit(1);
	} 
	if(pthread_join(munch1, NULL) != 0){
		printf("Error waiting for the munch1 thread to terminate\n");
		exit(1);
	}
	if(pthread_join(munch2, NULL) != 0){
		printf("Error waiting for the munch2 thread to terminate\n");
		exit(1);
	}
	if(pthread_join(writer, NULL) != 0){
		printf("Error waiting for the writer thread to terminate\n");
		exit(1);
	}


	// print all the stats
	printf("Queue 1 Stats: \n");
	PrintQueueStats(q1);
	printf("Queue 2 Stats: \n");
	PrintQueueStats(q2);
	printf("Queue 3 Stats: \n");
	PrintQueueStats(q3);
	
	
	// all the array of buffers have been freed, back in the MunchAndWrite methods. So free the queueStats,
	// the actual queues, and the arrays of queues
	free(q1->myQueueStats);
	free(q1);
	free(q2->myQueueStats);
	free(q2);
	free(q3->myQueueStats);
	free(q3);

	free(toMunch1);
	free(toMunch2);



}
