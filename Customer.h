#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__ 

#include <assert.h>
#include <iostream> 

class Customer
{
    private:
        char seller_type;
        unsigned int seller_id;
        unsigned int customer_id;
        unsigned int arrival_time;
        
    public:

        // Constructor
        Customer(char seller_type, 
                 unsigned int seller_id,
                 unsigned int customer_id,
                 unsigned int arrival_time);

        // Getters
        char getSellerType(){return this->seller_type;}
        unsigned int getSellerId(){return this->seller_id;}
        unsigned int getCustomerId(){return this->customer_id;}
        unsigned int getArrivalTime(){return this->arrival_time;}

        // Helper functions
        void printCustomer();

};

// struct CompareArrivalTime {
//     bool operator()(Customer const &lhs, Customer const &rhs) {
//         // return "true" if "p1" is ordered before "p2", for example:
//         return lhs.getArrivalTime() < rhs.getArrivalTime();
//     }
// };

#endif 