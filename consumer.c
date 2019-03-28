/* Program to read sensor data. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include "../Common/datatypes.h"

int main(int argc, char** argv)
{
	
	int fd , size = 1, num_of_entries=0;
	struct temperature temp;
	struct timeval  tv1, tv2;
	double time = 0;
		
	// open "sensordata.txt" read only, make sure you first
	fd = open("sensordata.txt", O_RDONLY);

	// check whether file was opened correctly
	if (fd == -1) 
	{
		fprintf (stderr, "Error Number %d\n", errno);
		perror("Program");
	}
	
	printf("Value\t\tUnit\t%TimeStamp\n");
	while(size)
	{	
		gettimeofday(&tv1, NULL);
		size = read(fd, &temp, sizeof(struct temperature));
		gettimeofday(&tv2, NULL);
		time = time + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);                   
		// output the read characters, add '\0' to end string first!
		printf("%f\t%c\t%lu\n", temp.d_value, temp.c_unit, (temp.t.tv_nsec));
		++num_of_entries;
	}
	// close file 
	if(close(fd) < 0) 
	{
		perror("sensordata.txt");
		exit(1);
	}
	printf("Average time for read is : %lf\n", time/num_of_entries);
	printf("Consumer exited.\n\n");
	return 0;
}
