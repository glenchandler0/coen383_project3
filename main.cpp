#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>

#include "Seller.h"
#include "Customer.h"
#include "Seat.h"

#define ROWS 10 
#define COLS 10
#define RUNTIME 60

Seat* seats[ROWS][COLS];

void printSeats()
{
    for(int i = 0; i < ROWS; ++i)
    {
        for(int j = 0; j < COLS; ++j)
        {
            Customer* cust = seats[i][j]->getCustomer();
            if(cust != NULL)
                cust->printCustomer();
            else
                printf("  -  ");
        }
        printf("\n\n");
    }
}

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/*
* Variables and data that is needed
*/
//Struct for passing args to pthreads
struct arg_struct {
    char seller_type;
    int thread_index;
};

// int value N that the user will pass in through the command line
int N;


//TODO: Create list of queues that can be referenced for a specific seller

// seller thread to serve one time slice (1 minute)
void * sell(void *arguments)
{
  //Fetch arguments from void * struct
  struct arg_struct *args = (struct arg_struct *)arguments;
  int local_time = 0;
  printf("0:%02d %c%d initiated\n", local_time, args->seller_type, args->thread_index);
  while(local_time < RUNTIME) // while local time is less than RUNTIME and both queues aren't empty
  {
    printf("0:%02d %c%d: waiting for main to release\n", local_time, args->seller_type, args->thread_index);
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
    // dequeue all valid customers from the waiting queue and queue them into the ready queue EVENT 1
    // if front customer is being helped
    //		decrement their timer
    //		if time is zero then give them seat and dequeue from ready queue EVENT 3
    // else
    //		Serve any buyer available in this seller queue that is ready (assign them random transaction time) EVENT 2
    
    ++local_time;

  }
  // if ready queue is not empty then remove all customers from queue until empty
  printf("0:%02d %c%d time slice work completed\n", local_time, args->seller_type, args->thread_index);

  return NULL; // thread exits
}

void wakeup_all_seller_threads() {
  pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}

//TODO: Command line argument for N
int main(int argc, char *argv[])
{
  if(argc != 2) {
    printf("Error: Input the program name followed by an integer N\n");
    return -1;
  }

  N = atoi(argv[1]);

  while(N <= 0 || N > 100) {
    printf("Error: Please enter a value between 1 and 100\n");
    std::cin >> N;
  }

    // Intialize 2D seating chart
    for(int i = 0; i < ROWS; ++i)
        for(int j = 0; j < COLS; ++j)
            seats[i][j] = new Seat();
 
    Customer *cust1 = new Customer('M', 1, 1, 4);


    Customer *cust2 = new Customer('H', 2, 9, 51);

    seats[1][1]->setCustomer(cust1);
    seats[8][6]->setCustomer(cust2);

    printSeats();

  int i;
  pthread_t tids[10];
  char seller_type;

  // Create necessary data structures for the simulator.
  // Create buyers list for each seller ticket queue based on the // N value within an hour and have them in the seller queue.
  // Create 10 threads representing the 10 sellers.
  struct arg_struct *args;

  args = new arg_struct;
  args->seller_type = 'H';
  args->thread_index = 0;
  pthread_create(&(tids[0]), NULL, &sell, args); //ERROR

  for (i = 1; i < 4; i++)
  {
    args = new arg_struct;
    args->seller_type = 'M';
    args->thread_index = i;
    pthread_create(&tids[i], NULL, &sell, args);
  }

  for (i = 4; i < 10; i++)
  {
    args = new arg_struct;
    args->seller_type = 'L';
    args->thread_index = i;
    pthread_create(&tids[i], NULL, &sell, args); // wakeup all seller threads
  }

  //Wake up all threads to begin their running
  printf("\tAll threads created, about to signal to begin\n");
  // usleep(1000 * 1000);
  for(int current = 0; current < RUNTIME; current++) {
  usleep(10000);
  wakeup_all_seller_threads(); //Race condition if seller waits for mutex
  }
  // wait for all seller threads to exit
  for (i = 0 ; i < 10; i++)
    pthread_join(tids[i], NULL); //TODO: Add & back

  printf("\tAll threads joined\n");

  // Printout simulation results
  // exit(0);
}
