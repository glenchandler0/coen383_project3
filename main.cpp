#include <stdio.h>
#include <pthread.h>

#include "Seller.h"
#include "Customer.h"
#include "Seat.h"

#define ROWS 10 
#define COLS 10

void printSeats();

Seat* seats[ROWS][COLS];


int main(int argc, char *argv[]){

    // Intialize 2D seating chart
    for(int i = 0; i < ROWS; ++i)
        for(int j = 0; j < COLS; ++j)
            seats[i][j] = new Seat();
        
    Seller *sell1 = new Seller('M', 1);
    // pq* sell1_queue = sell1->getQueue();
    
    Customer *cust1 = new Customer('M', 1, 1, 4);
    Customer *cust2 = new Customer('H', 2, 9, 6);

    sell1->addToWaitingQueue(cust1);
    sell1->addToWaitingQueue(cust2);


    printSeats();

    printf("====================================================\n");
    sell1->update(3);
    printSeats();
    
    printf("====================================================\n");
    sell1->update(4);
    printSeats();

    printf("====================================================\n");
    sell1->update(5);
    printSeats();

    printf("====================================================\n");
    sell1->update(6);
    printSeats();

    printf("====================================================\n");
    sell1->update(7);
    printSeats();
    // sell1_queue->push(cust1);
    // sell1_queue->push(cust2);
    
    // seats[1][1]->setCustomer(sell1_queue->top());
    // seats[8][6]->setCustomer(sell1_queue->pop());




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
        



//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// // seller thread to serve one time slice (1 minute)
// void *  sell(char *seller_type){
//     While (having more work todo){
//         pthread_mutex_lock(&mutex);
//         pthread_cond_wait(&cond, &mutex);
//         pthread_mutex_unlock(&mutex);
//         // Serve any buyer available in this seller queue that is ready 
//         // now to buy ticket till done with all relevant buyers in their queue
//         // ..................
//         }
//         return NULL;       // thread exits
//         }
        
// void wakeup_all_seller_threads(){
//     pthread_mutex_lock(&mutex);
//     pthread_cond_broadcast(&cond);
//     pthread_mutex_unlock(&mutex);
// }

    // for(int i = 0; i < ROWS; ++i)
    //     for(int j = 0; i < COLS; ++j)
    //         seats[i][j] = new Seat();


    
    // print_seats();
    
    // Seller x = Seller('L', 2);

    // printf("Seller: %c%d\n", x.getSellerType(), x.getSellerId());

    

    // std::cout << seats;

    // int i;
    // pthread_t tids[10];
    // char* Seller_type;
    // Create necessary data structures for the simulator. 

    // for(int i=0; i < ROWS; ++i)
    //     for(int j = 0; i < COLS; ++j)
    //         for 


    // // Create buyers list for each seller ticket queue based on the 
    // // N value within an hour and have them in the seller queue.
    // // Create 10 threads representing the 10 sellers.
    // Seller_type = "H";
    // pthread_create(&tids[0], NULL, sell, &seller-type);
    
    // Seller_type type = "M";
    // for (i = 1; i < 4; i++) 
    //     pthread_create(&tids[i], NULL, sell, &seller-type);
    
    // seller-type = “L”;
    // for (i = 4; i < 10; i++)
    //     pthread_create(&tids[i], NULL, sell, &seller-type);
    
    // // wakeup all seller threads
    // wakeup_all_seller_threads();
    
    // // wait for all seller threads to exit
    // for (i = 0 ; i < 10 ; i++)
    //     pthread_join(&tids[i], NULL);
    
    // // Printout simulation results............
    // exit(0);

