
#define _GNU_SOURCE //This is required because asprintf is a GNU extension, not in C or POSIX
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "../Common/datatypes.h"
int main() {

	pid_t pid;
	char *buffer_string;
	int fd, size, i;
	int num_of_entries = 10;
	struct temperature *temp = malloc(sizeof(*temp));
	temp->c_unit = 'C';
	
	int segment_id;
	struct temperture *shared_memory;
	struct shmid_ds shmbuffer;
	int segment_size;
	const int shared_segment_size = 0x6400;
	
	struct timeval  tv1, tv2;
	double time = 0;
	
	/* Allocate a shared memory segment. */
	segment_id = shmget (IPC_PRIVATE, shared_segment_size,
			IPC_CREAT | IPC_EXCL | S_IWUSR | S_IRUSR);

	/* Attach the shared memory segment. */
	shared_memory = (struct temperture*) shmat (segment_id, 0, 0);
	printf ("shared memory attached at address %p\n", shared_memory);
	
	/* Determine segment size */
	shmctl(segment_id, IPC_STAT, &shmbuffer);
	segment_size = shmbuffer.shm_segsz;
	printf("Segment size : %d\n", segment_size );

	pid = fork();
	if (pid==-1) {
		printf("The fork() has failed.\n");
		exit(1);
	}
	
	//A new process has been created.
	if (pid==0) {
					////////////////In child - consume
		printf("Value\t\tUnit\t%TimeStamp\n");
		temp = (struct temperature*)shared_memory;
		for(i = 0 ; i < num_of_entries ; ++i)
		{	
				// output the read characters, add '\0' to end string first!
				gettimeofday(&tv1, NULL);
				printf("%f\t%c\t%lu\n", (temp->d_value), (temp->c_unit), (temp->t.tv_nsec));
				gettimeofday(&tv2, NULL);
				time = time + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
				temp += 1;
		}
		printf("Average time for read is : %lf\n", time/num_of_entries);
		printf("Consumer exited.\n\n");
	
	}
	else { 				/////////////////// In parent -  produce
								
		temp = (struct temperature*)shared_memory;
		for( i = 0 ; i < num_of_entries ; ++i)
		{	
			gettimeofday(&tv1, NULL);
			temp->c_unit = 'C';
			temp->d_value  = (float)rand()/(float)(RAND_MAX/SENSOR_MAX);
			clock_gettime(CLOCK_MONOTONIC,&(temp->t));	
			gettimeofday(&tv2, NULL);
			time = time + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
			temp += 1;
		}
		printf("Average time for write is : %lf\n", time/num_of_entries);
		printf("Producer exited.\n\n");
	}
	
		/* Detach the shared memory segment. */
	shmdt (shared_memory);

	/* Deallocate the shared memory segment. */
	shmctl (segment_id, IPC_RMID, 0);
	return 0;
}