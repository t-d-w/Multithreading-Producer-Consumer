/**
 * MunchAndWrite.h
 *
 *
 *
 */

#ifndef MUNCHANDWRITE_H
#define MUNCHANDWRITE_H

#include "Queue.h"
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFSIZE 4096

void *munch1Execute(void *inputQueues);

void *munch2Execute(void *inputQueues);

void *writerExecute(void *inputQueue);

#endif // MUNCHANDWRITE_H
