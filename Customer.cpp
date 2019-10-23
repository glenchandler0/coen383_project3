#include "Customer.h"

Customer::Customer(char seller_type, unsigned int seller_id, unsigned int customer_id)
{
    assert(seller_type == 'L' || seller_type == 'M' || seller_type =='H');

    this->seller_type = seller_type;
    this->seller_id = seller_id;
    this->customer_id = customer_id;
    this->arrival_time = rand() % 59; // Random number between 0-59

}

void Customer::printCustomer()
{
    printf("%c%d%02d ", this->seller_type, this->seller_id, this->customer_id);
}