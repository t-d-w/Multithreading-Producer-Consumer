# Makefile
#
# Author - Thomas Wilkinson
# CS Login: twilkinson
# Author - Na Li
# CS Login: na
#
# There is 1 main module and 4 helper modules.
# Here is a list of the .c and .h files:
# Main.c
# Queue.c Queue.h
# Reader.c Reader.h
# MunchAndWrite.c MunchAndWrite.h
# QueueStats.c QueueStats.h
# README
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC      = gcc
WARNING_FLAGS = -Wall -Wextra
OPTS = -pthread
EXE = prodcom
SCAN_BUILD_DIR = scan-build-out


all: Main.o Queue.o Reader.o MunchAndWrite.o QueueStats.o
	$(CC) $(WARNING_FLAGS) $(OPTS) -o $(EXE) Main.o Reader.o MunchAndWrite.o QueueStats.o Queue.o
Main.o: Main.c Reader.h Queue.h MunchAndWrite.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c Main.c
Queue.o: Queue.c
	$(CC) $(OPTS) $(WARNING_FLAGS) -c Queue.c
Reader.o: Reader.c Queue.h 
	$(CC) $(OPTS) $(WARNING_FLAGS) -c Reader.c
MunchAndWrite.o: MunchAndWrite.c Queue.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c MunchAndWrite.c
QueueStats.o: QueueStats.c 
	$(CC) $(OPTS) $(WARNING_FLAGS) -c QueueStats.c
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)
#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 



