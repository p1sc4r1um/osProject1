// Compile as: gcc store_solution.c -lpthread -D_REENTRANT -Wall -o store

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_REQUESTS 100 
#define MAX_THREADS 4
#define N_CLIENTS 10

typedef struct request{
	int value;
	int client;
	} request;

request requests[N_REQUESTS];
int total_daily_requests=0;

int pos=0; // position in array

// threads id
pthread_t my_thread[N_CLIENTS];
int ids[N_CLIENTS]; // saves id from client threads

// sync resources
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t threads_limit;


void *generate_requests(void* id_ptr) {
	int id = *((int *)id_ptr);
	int new_request;

	while(1){
		// the maximum threads working at the same time is MAX_THREADS
		// control the access to the 'pos' variable
		
		sem_wait(&threads_limit);
		pthread_mutex_lock(&mutex);
		
		if(pos==N_REQUESTS){
			// exit thread
			
			sem_post(&threads_limit);
			pthread_mutex_unlock(&mutex);
			pthread_exit(NULL);

			
			}
	    new_request=rand()%100+1;
		requests[pos].value=new_request;
		requests[pos].client=id;
		pos++;
		pthread_mutex_unlock(&mutex);
		sem_post(&threads_limit);		

		printf("New request of %d products was generated by thread %d\n",new_request,id);
		usleep(10); //waits 10 us
		}
	}

int main(void) {
	int i;
  	sem_init(&threads_limit,0,MAX_THREADS);

  // create threads client
  
  	for (i = 0; i<N_CLIENTS; i++){
		ids[i] = i;
		if(pthread_create(&my_thread[i], NULL, generate_requests, &ids[i])!=0){
			perror("Error creating the thread!");
			exit(0);
		}
	}	
  
  // wait until all threads client finish

  	for (i = 0; i<N_CLIENTS; i++){
		pthread_join(my_thread[i], NULL);
	}


  // count items sold
  for(i=0;i<N_REQUESTS;i++) total_daily_requests+=requests[i].value;
  printf("Total items sold = %d\n",total_daily_requests); 
  exit(0);
  }



