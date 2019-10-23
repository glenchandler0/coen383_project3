#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__ 

#include <assert.h>
#include <iostream> 
#include <stdlib.h>


class Customer
{
    private:
        char seller_type;
        unsigned int seller_id;
        unsigned int customer_id;
        unsigned int arrival_time;
        unsigned int wait_time;
        bool has_been_helped;
        
    public:

        // Constructor
        Customer(char seller_type, 
                 unsigned int seller_id,
                 unsigned int customer_id,
                 unsigned int wait_time);

        // Getters
        char getSellerType(){return this->seller_type;}
        unsigned int getSellerId(){return this->seller_id;}
        unsigned int getCustomerId(){return this->customer_id;}
        unsigned int getArrivalTime(){return this->arrival_time;}
        unsigned int getWaitTime(){return this->wait_time;}
        bool getHasBeenHelped(){return this->has_been_helped;}

        // Setters
        void decrementWaitTime(){this->wait_time = this->wait_time - 1;}
        void setHasBeenHelped(){this->has_been_helped = true;}

        // Helper functions
        void printCustomer();

};

#endif 