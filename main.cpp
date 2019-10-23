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

//Function definitions
void printSeats();
bool is_full();
void fill_seats(char priority, int num_seats);
Seat * assign_next_seat(Customer * cust);

int global_counter;
bool ready_list[10];

Seat* seats[ROWS][COLS];

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seats_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
* Variables and data that is needed
*/
//Struct for passing args to pthreads
struct arg_struct {
    int seller_id;
    char seller_type;
    int thread_index;
};

// int value N that the user will pass in through the command line
int N;

void * sell(void * arguments)
{
    struct arg_struct *args = (struct arg_struct *)arguments;
    Seller * this_seller = new Seller(args->seller_type, args->seller_id, N);

    int count = 0;
    while(global_counter < RUNTIME)//this_seller->customers_left())
    {
        pthread_mutex_lock(&mutex);
        printf("%d:%d Waiting for main\n", global_counter, args->thread_index);
        ready_list[args->thread_index] = 1;

        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);

        printf("%d: Unlocked by main, doing work!\n", args->thread_index);

        // Moves people from waiting queue to ready queue
        // does one unit of work on whoever is in the front
        Customer* cust = this_seller->update(global_counter);
        if(cust != NULL)
        {
            assign_next_seat(cust);
            printSeats();
        }
            // printSeats();
            // printf("%d: Ticket sold\n", args->thread_index);
          

        if(global_counter >= RUNTIME || is_full())
        {
            printf("%d: about to purge\n", args->thread_index);
            unsigned int num_purged = this_seller->purge_queues();
        }
    }

    // ready_list[args->thread_index] = 1;
    printf("%d: Thread completed\n", args->thread_index);
    return NULL;
}

//Loops until all sellers are marked as ready
void wait_for_sellers()
{
  bool complete = false;
  while(complete == false)
  {
    complete = true;
    // pthread_mutex_lock(&mutex);
    for(int i = 0; i < 10; i++)
    {
      if(ready_list[i] == false)
        complete = false;
    }
    // pthread_mutex_unlock(&mutex);
  }

  //Reset all threads to not ready
  for(int i = 0; i < 10; i++)
  {
      ready_list[i] = false;
  }

  //Function won't complete until all entries are true
}

//TODO: Check mutex logic
//Check completed_list[i]¿
// bool threads_running()
// {
//     bool complete = false;
//     // pthread_mutex_lock(&mutex);
//     for(int i = 0; i < 10; i++)
//     {
//       if(completed_list[i] == false)
//         complete = true;
//     }
//     // pthread_mutex_unlock(&mutex);
//
//     return complete;
// }

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


  int i;
  pthread_t tids[10];
  char seller_type;

  // Create necessary data structures for the simulator.
  // Create buyers list for each seller ticket queue based on the
  // N value within an hour and have them in the seller queue.
  // Create 10 threads representing the 10 sellers.
  struct arg_struct *args;

  args = new arg_struct;
  args->seller_id = 0;
  args->seller_type = 'H';
  args->thread_index = 0;

  // Create thread for high priority seller
  pthread_create(&(tids[0]), NULL, &sell, args);

  // Create threads for medium priority seller
  for (i = 1; i < 4; i++)
  {
    args = new arg_struct;
    args->seller_id = i-1;
    args->seller_type = 'M';
    args->thread_index = i;
    pthread_create(&tids[i], NULL, &sell, args);
  }

  // Create threads for low priority seller
  for (i = 4; i < 10; i++)
  {
    args = new arg_struct;
    args->seller_id = i-4;
    args->seller_type = 'L';
    args->thread_index = i;
    pthread_create(&tids[i], NULL, &sell, args); // wakeup all seller threads
  }

  //Wake up all threads to begin their running
  // usleep(1000 * 1000);
  for(global_counter = 0; global_counter < RUNTIME; global_counter++)
  {
    wait_for_sellers();

    printf("\tAll threads ready, about to signal to begin\n");
    wakeup_all_seller_threads(); //Race condition if seller waits for mutex
  }
  wakeup_all_seller_threads();

  // wait for all seller threads to exit
  printf("\tMain waiting for threads to join!\n");
  for (i = 0 ; i < 10; i++)
    pthread_join(tids[i], NULL); //TODO: Add & back

  printf("\tAll threads joined\n");
}

/* ------ SEAT TABLE MANIPULATION FUNCTIONS -------- */
bool is_full()
{
  for(int i = 0; i < ROWS; ++i)
  {
      for(int j = 0; j < COLS; ++j)
      {
          if(seats[i][j]->getAssigned() == false)
            return false;
      }
  }

  return true; //Never found an unassigned seat
}

Seat * assign_next_seat(Customer * cust)
{
  char priority = cust->getSellerType();
  if(is_full() == true)
    return NULL;

  int i;
  int j;
  if(priority == 'H')
  {
  //nested for loop
  for(int i = 0; i < ROWS; i++)
  {
    for(int j = 0; j < COLS; j++)
    {
      if(seats[i][j]->getAssigned()==false)
      {
        //Assign seat
        seats[i][j]->setCustomer(cust);
        return seats[i][j];
      }
    }
  }
  } //end priority if
  else if(priority == 'M')
  {
  int row_array[] = {4,5,3,6,2,7,1,8,0,9};
  //nested for loop
  for(int i = 0; i < ROWS; i++)
  {
    for(int j = 0; j < COLS; j++)
    {
      if(seats[row_array[i]][j]->getAssigned()==false)
      {
        //Assign seat
        seats[row_array[i]][j]->setCustomer(cust);
        return seats[i][j];
      }
    }
  }
  } //end priority if
  else if(priority == 'L')
  {
  //nested for loop
  for(int i = ROWS-1; i >= 0; i--)
  {
    for(int j = COLS-1; j >= 0; j--)
    {
      if(seats[i][j]->getAssigned()==false)
      {
        //Assign seat
        seats[i][j]->setCustomer(cust);
        return seats[i][j];
      }
    }
  }
  } //end priority if


  return NULL;
}
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
//TODO: Delete, for testing only
// void fill_seats(char priority, int num_customers)
// {
//   for(int i = 0; i < num_customers; i++)
//   {
//     assign_next_seat(new Customer(priority, 1, 1));
//   }
// }

//-------------------- CODE DUMPSTER -------------------
//Main for testing priority queues
// int old_main(int argc, char *argv[]){
//
//     // Intialize 2D seating chart
//     for(int i = 0; i < ROWS; ++i)
//         for(int j = 0; j < COLS; ++j)
//             seats[i][j] = new Seat();
//
//     Seller *sell1 = new Seller('M', 1);
//     // pq* sell1_queue = sell1->getQueue();
//
//     Customer *cust2 = new Customer('H', 2, 9, 6);
//     Customer *cust1 = new Customer('M', 1, 1, 4);
//
//
//     sell1->addToWaitingQueue(cust1);
//     sell1->addToWaitingQueue(cust2);
//
//
//     // printSeats();
//
//
//     sell1->update(3);
//     sell1->update(4);
//     sell1->update(5);
//     sell1->update(6);
//     sell1->update(7);
//
//     q* dq = sell1->getReadyQueue();
//
//     while(dq->size() != 0)
//     {
//         Customer *c = dq->front();
//         dq->pop();
//         c->printCustomer();
//         printf("\n");
//     }
//
//     // sell1_queue->push(cust1);
//     // sell1_queue->push(cust2);
//
//     // seats[1][1]->setCustomer(sell1_queue->top());
//     // seats[8][6]->setCustomer(sell1_queue->pop());
// }




//TODO: Create list of queues that can be referenced for a specific seller

// // seller thread to serve one time slice (1 minute)
// void * sell(void *arguments)
// {
//   //Fetch arguments from void * struct
//   struct arg_struct *args = (struct arg_struct *)arguments;
//   int local_time = 0;
//   printf("0:%02d %c%d initiated\n", local_time, args->seller_type, args->thread_index);
//   while(local_time < RUNTIME) // while local time is less than RUNTIME and both queues aren't empty
//   {
//     printf("0:%02d %c%d: waiting for main to release\n", local_time, args->seller_type, args->thread_index);
//     pthread_mutex_lock(&mutex);
//     pthread_cond_wait(&cond, &mutex);
//     pthread_mutex_unlock(&mutex);
//     // dequeue all valid customers from the waiting queue and queue them into the ready queue EVENT 1
//     // if front customer is being helped
//     //		decrement their timer
//     //		if time is zero then give them seat and dequeue from ready queue EVENT 3
//     // else
//     //		Serve any buyer available in this seller queue that is ready (assign them random transaction time) EVENT 2

//     ++local_time;

//   }
//   // if ready queue is not empty then remove all customers from queue until empty
//   printf("0:%02d %c%d time slice work completed\n", local_time, args->seller_type, args->thread_index);

//   return NULL; // thread exits
// }
