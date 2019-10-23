#ifndef __SEAT_H__
#define __SEAT_H__

#include "Customer.h"

class Seat
{
    private: 
        bool assigned;
        Customer *customer;
    
    public:
        // Constructor
        Seat();

        // Getters
        bool getAssigned();
        Customer* getCustomer();

        // Setters
        bool setCustomer(Customer* cust);

};

#endif