#include "Seller.h"

Seller::Seller(char seller_type, unsigned int seller_id)
{
   
    if(seller_type == 'L')
        service_time = rand() % 7 +4;
    else if(seller_type == 'M')
        service_time = rand() % 4 + 2;
    else if(seller_type == 'H')
        service_time = rand() % 2 + 1;
    else{
        throw std::runtime_error("Incorrect seller type");
    }

    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->tickets_sold = 0;
    this->waiting = new pq;
    this->ready = new q;
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
}