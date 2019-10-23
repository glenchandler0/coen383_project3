#include "Seller.h"

Seller::Seller(char seller_type, unsigned int seller_id, unsigned int N)
{
    assert(seller_type == 'L' || seller_type == 'M' || seller_type =='H');

    this->N = N;
    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->tickets_sold = 0;
    this->num_purged = 0;
    this->waiting = new pq;
    this->ready = new q;

    // Add N customers to waiting queue
    for(int i = 0; i < this->N; ++i)
    {
        Customer* new_customer = new Customer(this->seller_type, 
                                              this->seller_id);
        this->sellTicket();
        this->waiting->push(new_customer);
    }

}

void Seller::sellTicket()
{
    this->tickets_sold++;
}

char Seller::getSellerType(){
    return seller_type;
}

unsigned int Seller::getSellerId()
{
    return seller_id;
}

unsigned int Seller::getTicketsSold()
{
    return this->tickets_sold;
}

void Seller::addToWaitingQueue(Customer *new_customer)
{
    this->waiting->push(new_customer);
}

Customer* Seller::update(unsigned int current_minute)
{
    // Move people from the waiting queue to the ready queue
    while(!this->waiting->empty() && 
          current_minute > this->waiting->top()->getArrivalTime())
    {
        // Get first customer from waiting queue
        Customer* cust = this->waiting->top();
        
        // DEBUG
        // printf("Waiting Time: %d\n", cust->getWaitTime());

        // Output when customer arrived in 
        printf("Customer ");
        cust->printCustomer();
        printf("arrived at time 00:%02d\n", cust->getArrivalTime());        

        // Add customer to ready queue
        this->ready->push(cust);

        // Advance to next element in queue
        this->waiting->pop();
    }

    // Do one unit of work on a customer at the front of the ready queue
    if(!this->ready->empty())
    {
        // If someone has fully been served, remove them from the list and output a message
        if(this->ready->front()->getWaitTime() == 0)
        {
            Customer* cust = this->ready->front();
            
            // Output when someone has been assigned a seat
            printf("Customer ");
            cust->printCustomer();
            printf(" has finished purchasing a ticket.\n");
            
            this->ready->front();

            return cust;
        }

        // If the person is new to the front line, then print seat assignment
        if(!this->ready->front()->getHasBeenHelped())
        {
            Customer* cust = this->ready->front();
            cust->setHasBeenHelped();
            
            // Assign the customer an id based on order of the queue
            unsigned int cust_id = this->getTicketsSold();
            cust->setCustomerId(cust_id);
            this->sellTicket();

            printf("Customer ");
            cust->printCustomer();
            printf(" has been assigned a seat.\n");

        }

        // If someone at the front of the queue, perform one unit of work on them
        if(this->ready->front()->getWaitTime() > 0)
        {
            Customer* cust = this->ready->front();
            cust->decrementWaitTime();
            return NULL;
        }

        //TODO: Should be done in main: Remove people if there are no more seats, and print 

    }
    return NULL;
}

// Removes all unserved Customers after concert is sold out
unsigned int Seller::purge_queues()
{
    unsigned int num_left = 0;

    while(this->waiting->size() != 0)
    {
        this->waiting->pop();
        ++num_left;
    }

    while(this->ready->size() != 0)
    {
        this->waiting->pop();
        ++num_left;
    }

    this->num_purged = num_left;

    return num_left;
}

// Removes all unserved Customers after concert is sold out
bool Seller::customers_left()
{
    return (this->waiting->size() + this->ready->size()) > 0;
}