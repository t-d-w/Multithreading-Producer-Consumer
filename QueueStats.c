/**
 * QueueStats.c
 *
 * Author - Thomas Wilkinson
 * Author - Na Li
 *
 * Description: print out the stats of queues, such as enqueueCount, dequeueCount, enqueueTime and dequeueTime.
 *
 */
#include "QueueStats.h"
#include <stdlib.h>

/**
 * QueueStats.c
 *
 * Description: create a QueueStats structure
 */
struct QueueStats *CreateQueueStats(){
	struct QueueStats *myQueueStats = malloc(sizeof(struct QueueStats));
	myQueueStats->enqueueCount = 0;
	myQueueStats->dequeueCount = 0;
	myQueueStats->enqueueTime = 0;
	myQueueStats->dequeueTime = 0;
	return myQueueStats;
}


