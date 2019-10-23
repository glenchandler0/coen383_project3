#ifndef __SELLER_H__
#define __SELLER_H__

#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <queue> 

#include "Customer.h"

class Seller
{
    private:
        unsigned int service_time;
        char seller_type;
        unsigned int seller_id;
        unsigned int tickets_sold;
        std::priority_queue<Customer> *q;

    public:
        Seller(char seller_type, unsigned int seller_id);
        void sellTicket();
        char getSellerType();
        unsigned int getSellerId();
        unsigned int getTicketsSold();

    // struct CompareArrivalTime {
    //     bool operator()(Customer const & lhs, Customer const & rhs) {
    //         return lhs.getArrivalTime() < rhs.getArrivalTime();
    //     }
    // };
    
};
#endif