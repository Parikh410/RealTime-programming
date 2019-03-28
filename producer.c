/* Program to create random sensor value and write it into a file. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "../Common/datatypes.h"

int main() {

	int fd, size,i;
	int num_of_entries = 10;
	struct temperature temp = {0.0, 'C', 0};
	struct timeval  tv1, tv2;
	double time = 0;
	
	fd = open("sensordata.txt", O_CREAT | O_RDWR, S_IRWXU); 
	// check if creation was successful
	if (fd == -1) {
		fprintf (stderr, "Error Number %d\n", errno);
		perror("Program");
		exit(1);
	}
	printf("Producer writing values into the file...\n");
	for(  i = 0 ; i < num_of_entries ; ++i)
	{
		temp.d_value  = (float)rand()/(float)(RAND_MAX/SENSOR_MAX);
		clock_gettime(CLOCK_MONOTONIC, &(temp.t));
		// write data to file 
		gettimeofday(&tv1, NULL);	
		size = write(fd, &temp , sizeof(struct temperature));
		gettimeofday(&tv2, NULL);
		time = time + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
		
	}
	
	// close file
	if(close(fd) < 0) {
		perror("sensordata.txt");
		exit(1);
	}
	printf("Average time for write is : %lf\n", time/num_of_entries);
	printf("Producer exited.\n\n");
	
	return 0;
}
