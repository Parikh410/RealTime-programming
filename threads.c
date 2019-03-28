/* Program to illustrate threads. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "../Common/datatypes.h"

void *produce();
void *consume();

struct temperature temp, shared[10];

struct timeval  tv1, tv2;
double tottime = 0;
int i,j;
const int num_of_entries = 10;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
	pthread_t thread1, thread2;

	//Create independent threads each of which will execute func
	if(pthread_create(&thread1, NULL, produce, NULL)) {
		printf("Error: Creating thread1 ...\n");
	}
	if(pthread_create(&thread2, NULL, consume, NULL)) {
		printf("Error: Creating thread2 ...\n");
	}

	//Wait till threads are complete before main continues.
	if (pthread_join(thread1, NULL)) {
		printf("Error: Joining thread1 ...\n");
		exit(-1);
	}
	if (pthread_join(thread2, NULL)) {
		printf("Error: Joining thread2 ...\n");
		exit(-1);
	}

	exit(0);
}

void *produce() {
	
	printf("Producer writing values into the file...\n");
	temp.c_unit = 'C';
	for(  i = 0 ; i < num_of_entries ; ++i)
	{
		
		temp.d_value  = (float)rand()/(float)(RAND_MAX/SENSOR_MAX);
		clock_gettime(CLOCK_MONOTONIC, &(temp.t));
		//pthread_mutex_lock(&mutex);
		gettimeofday(&tv1, NULL);	
		shared[i] = temp;
		gettimeofday(&tv2, NULL);
		//pthread_mutex_unlock(&mutex);
		tottime = tottime + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);
		
	}
	printf("Average time for write is : %lf\n", tottime/num_of_entries);
	printf("Producer exited.\n\n");
	return NULL;
}

void *consume() {
	
	for(  j = 0 ; j < num_of_entries ; ++j)
	{
		//pthread_mutex_lock(&mutex);
		gettimeofday(&tv1, NULL);
		temp = shared[j];
		gettimeofday(&tv2, NULL);
		//pthread_mutex_unlock(&mutex);
		tottime = tottime + (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double)(tv2.tv_sec - tv1.tv_sec);                   
		printf("%f\t%c\t%lu\n", temp.d_value, temp.c_unit, (temp.t.tv_nsec));
	}
	printf("Line : %d\n",__LINE__);
	printf("Average time for read is : %lf\n", tottime/num_of_entries);
	printf("Consumer exited.\n\n");
	return NULL;
}
