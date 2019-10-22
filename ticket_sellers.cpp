#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

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
//TODO: Create list of queues that can be referenced for a specific seller

// seller thread to serve one time slice (1 minute)
void * sell(void *arguments)
{
  //Fetch arguments from void * struct
  struct arg_struct *args = (struct arg_struct *)arguments;

  printf("%d initiated\n", args->thread_index);
  //while(list_of_queues[thread_index].empty() == false ???)
  {
    printf("%d: waiting for main to release\n", args->thread_index);
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);
    // Serve any buyer available in this seller queue that is ready
    // now to buy ticket till done with all relevant buyers in their queue ..................


  }
  printf("%d time slice work completed\n", args->thread_index);

  return NULL; // thread exits
}

void wakeup_all_seller_threads() {
  // pthread_mutex_lock(&mutex);
  pthread_cond_broadcast(&cond);
  // pthread_mutex_unlock(&mutex);
}

//TODO: Command line argument for N
int main()
{
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
  wakeup_all_seller_threads(); //Race condition if seller waits for mutex

  // wait for all seller threads to exit
  for (i = 0 ; i < 10 ; i++)
    pthread_join(tids[i], NULL); //TODO: Add & back

  printf("\tAll threads joined\n");

  // Printout simulation results
  // exit(0);
}
