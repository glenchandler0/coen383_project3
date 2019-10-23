#include "Seller.h"

Seller::Seller(char seller_type, unsigned int seller_id, unsigned int N)
{
    assert(seller_type == 'L' || seller_type == 'M' || seller_type =='H');

    this->N = N;
    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->tickets_sold = 0;
    this->waiting = new pq;
    this->ready = new q;

    // Add N customers to waiting queue
    for(int i = 0; i < this->N; ++i)
    {
        Customer* new_customer = new Customer(this->seller_type, 
                                              this->seller_id, 
                                              this->tickets_sold, 
                                              this->service_time);
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

void Seller::update(unsigned int current_minute)
{
    // Move people from the waiting queue to the ready queue
    while(this->waiting->size() != 0 && 
          current_minute > this->waiting->top()->getArrivalTime())
    {
        // Get first customer from waiting queue
        Customer* cust = this->waiting->top();
        
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
    if(this->ready->size() != 0)
    {
        // If someone has fully been served, remove them from the list and output a message
        if(this->waiting->top()->getWaitTime() == 0)
        {
            Customer* cust = this->waiting->top();
            this->waiting->pop();

            // Output when someone has been assigned a seat
            printf("Customer ");
            cust->printCustomer();
            printf(" was assigned a seat.");

            return;
        }

        // If someone at the front of the queue, perform one unit of work on them
        if(this->waiting->top()->getWaitTime() > 0)
        {
            Customer* cust = this->waiting->top();
            cust->decrementWaitTime();
            return;
        }

        //TODO: Should be done in main: Remove people if there are no more seats, and print 

    }


}