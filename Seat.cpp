#include "Seat.h"


Seat::Seat()
{
    this->assigned = false;
    this->customer = NULL;
}

bool Seat::getAssigned()
{
    return this->assigned;
}

bool Seat::setCustomer(Customer* cust)
{
    if(this->customer == NULL)
    {
        this->customer = cust;
        return true;
    }else
        throw std::runtime_error("Tried to sell same seat twice!");
}

Customer* Seat::getCustomer()
{
    return this->customer;
}

