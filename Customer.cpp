#include "Customer.h"

Customer::Customer(char seller_type, unsigned int seller_id, unsigned int customer_id, unsigned int wait_time)
{
    assert(seller_type == 'L' || seller_type == 'M' || seller_type =='H');

    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->customer_id = customer_id;
    this->arrival_time = rand() % 59; // Random number between 0-59
    this->has_been_helped = false;

    if(seller_type == 'L')
        this->wait_time = rand() % 7 +4;
    else if(seller_type == 'M')
        this->wait_time = rand() % 4 + 2;
    else if(seller_type == 'H')
        this->wait_time = rand() % 2 + 1;
    
}

void Customer::printCustomer()
{
    printf("%c%d%02d ", this->seller_type, this->seller_id, this->customer_id);
}