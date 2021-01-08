/**
 * QueueStats.h
 *
 *
 */
#ifndef QUEUE_STATS_H
#define QUEUE_STATS_H

#include <stdlib.h>

struct QueueStats{

	int enqueueCount;
	int dequeueCount;
	double enqueueTime;
	double dequeueTime;

};

/**
 * CreateQueueStats initializes the variables stored in the QueueStats struct
 */
struct QueueStats* CreateQueueStats();


#endif




