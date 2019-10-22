#include <stdio.h>
#include <pthread.h>

#include <iostream> 
#include <vector> 
#include <stdlib.h>
#include <assert.h>

#define ROWS 10 
#define COLS 10


//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void printSeats();


class Seller
{
    private:
        unsigned int service_time;
        char seller_type;
        unsigned int seller_id;
        unsigned int tickets_sold;

    public:
        Seller(char seller_type, unsigned int seller_id)
        {
            this->seller_type = seller_type;
            this->seller_id = seller_id;
            this->tickets_sold = 0;

            if(seller_type == 'L')
                service_time = rand() % 7 +4;
            else if(seller_type == 'M')
                service_time = rand() % 4 + 2;
            else if(seller_type == 'H')
                service_time = rand() % 2 + 1;
            else
                throw seller_id;
        }

        void sellTicket()
        {
            this->tickets_sold++;
        }

        char getSellerType(){
            return seller_type;
        }

        unsigned int getSellerId()
        {
            return seller_id;
        }
        
        unsigned int getTicketsSold()
        {
            return this->tickets_sold;
        }
};

class Customer
{
    private:
        char seller_type;
        unsigned int seller_id;
        unsigned int customer_id;
    
    public:

        Customer(char seller_type, unsigned int seller_id, unsigned int customer_id)
        {
            assert(seller_type == 'L' || seller_type == 'M' || seller_type =='H');

            this->seller_type = seller_type;
            this->seller_id = seller_id;
            this->customer_id = customer_id;
        }

        void printCustomer()
        {
            printf("%c%d%02d ", this->seller_type, this->seller_id, this->customer_id);
        }

};

class Seat
{
    private: 
        bool assigned;
        Customer *customer;
    
    public:
        Seat()
        {
            this->assigned = false;
            this->customer = NULL;
        }

        bool getAssigned()
        {
            return this->assigned;
        }

        bool setCustomer(Customer* cust)
        {
            if(this->customer == NULL)
            {
                this->customer = cust;
                return true;
            }else
                return false;
        }

        Customer* getCustomer()
        {
            return this->customer;
        }

};




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

Seat* seats[ROWS][COLS];


int main(int argc, char *argv[]){

    for(int i = 0; i < ROWS; ++i)
    {
        for(int j = 0; j < COLS; ++j)
        {
            seats[i][j] = new Seat();
        }
    }


    Customer *cust1 = new Customer('M', 1, 1);

    seats[1][1]->setCustomer(cust1);

    printSeats();

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
                printf("-    ");
        }
        printf("\n\n");
    }
}
        





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

