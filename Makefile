# Mitchell Van Braeckel (mvanbrae@uoguelph.ca) 1002297
# 31/03/2019
# CIS*3110: Operating Systems A4 - Synchronizing Threads with POSIX Semaphores
# --> Uses semaphores to synchronously increment a global variable being accessed by the same threads
 
CC = gcc
CFLAGS = -g -Wall -std=c99

all: ibadcnt igoodcnt

ibadcnt: ibadcnt.c
	$(CC) $(CFLAGS) -lpthread ibadcnt.c -o ibadcnt

igoodcnt: igoodcnt.c
	$(CC) $(CFLAGS) -lpthread -lrt igoodcnt.c -o igoodcnt

git: clean Makefile *.c *.txt *.pdf *.md
	git add Makefile
	git add *.md
	git add *.pdf
	git add *.txt
	git add *.c
	git commit -m "automatic backup via makefile"
	git remote rm origin
	git config credential.helper store
	git config --global credential.helper 'cache --timeout 3600'
	git remote add origin https://github.com/mvanbraeckel/semaphores_3110.git
	git push -u origin master

clean:
	rm -f *.o ibadcnt igoodcnt